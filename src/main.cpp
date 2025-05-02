// 保留唯一初始化部分
#include <Arduino.h>
#include "imu.h"
#include "uw.h"
#include <HardwareSerial.h>
#include "rc.h"

// 宏定义
#define UW1_ID 1
#define UW2_ID 2
#define ZERO_CMD "ZERO"
#define CLEAR_YAW_PACKET {0x68, 0x04, 0x00, 0x28, 0x2C}

// 添加硬件串口定义
HardwareSerial Serial3(USART3);  // RX=PB11, TX=PB10
RCParser rc(&Serial3);

HardwareSerial Serial2(USART2); // PA3(RX), PA2(TX)
HardwareSerial Serial4(PA1, PC10);  // RX=PA1, TX=PC10
HardwareSerial Serial5(PD2, PC12);  // RX=PD2, TX=PC12

// 提前声明回调函数
void updateUW(int id, int distance);

// 声明 checkSerialCommand 函数
void checkSerialCommand();

// UW初始化（带回调参数的版本）
UWParser uw1(&Serial4, &Serial1, [](int distance) { updateUW(UW1_ID, distance); }, "UW1:");
UWParser uw2(&Serial5, &Serial1, [](int distance) { updateUW(UW2_ID, distance); }, "UW2:");

// IMU初始化
IMUParser imu(&Serial2, &Serial1);

// 全局变量和阈值定义
const int DISTANCE_THRESHOLD = 100; // 距离阈值
const int TIME_DIFF_THRESHOLD = 100; // 时间差阈值

// UW数据存储
volatile int uw1_distance = -1;
volatile int uw2_distance = -1;

// 回调函数实现
void updateUW(int id, int distance) {
    if (id == UW1_ID) {
        uw1_distance = distance;
    } else if (id == UW2_ID) {
        uw2_distance = distance;
    }
}

// 新增清零指令相关
bool zeroFlag = false;           // 清零触发标志
unsigned long lastSendTime = 0;  // 时间间隔控制
byte zeroCounter = 0;            // 发送次数计数

// 清零命令帧
const byte zeroPacket[5] = CLEAR_YAW_PACKET;

// 方位角清零执行函数
void zeroYaw() {
    if (zeroFlag && (millis() - lastSendTime >= 50)) {
        if (zeroCounter < 3) {
            Serial2.write(zeroPacket, sizeof(zeroPacket));  // 通过USART2发送
            zeroCounter++;
            lastSendTime = millis();
        } else {
            zeroFlag = false;
        }
    }
}

// loop函数
void loop() {
    checkSerialCommand();  // 指令检测
    zeroYaw();             // 清零执行
    
    imu.processData();
    uw1.processData();
    uw2.processData();
    
    rc.processData();  // RC数据处理
}

// 定时器初始化用于PWM输出
void initPWM() {
    // 开启GPIOC和TIM3时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // 配置PC8和PC9为复用功能 (AF2 for TIM3_CH3 and TIM3_CH4)
    GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOC->MODER |= (GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);
    GPIOC->AFR[1] |= (2 << (4 * 0)) | (2 << (4 * 1));  // AF2

    // 配置TIM3
    TIM3->PSC = 71;  // 分频系数: 72MHz / (PSC+1) = 1MHz
    TIM3->ARR = 19999;  // 自动重装载值: 1MHz / (ARR+1) = 50Hz
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;  // PWM模式1
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC4PE;  // 预装载使能
    TIM3->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;  // 捕获/比较使能

    // 设置占空比 (5% 和 10%)
    TIM3->CCR3 = 1000;  // 5% 占空比: ARR * 0.05
    TIM3->CCR4 = 2000;  // 10% 占空比: ARR * 0.10

    // 启动计数器
    TIM3->CR1 |= TIM_CR1_CEN;
}

// 设置初始占空比 (0 度)
void setServoAngle(int servo, float angle) {
    if (angle < -180) angle = -180;
    if (angle > 180) angle = 180;

    // 将角度转换为占空比 (5% ~ 10%)
    float dutyCycle = 5.0 + ((angle + 180) / 360.0) * 5.0;
    uint32_t ccrValue = (uint32_t)(dutyCycle / 100.0 * 20000);

    if (servo == 1) {
        TIM3->CCR3 = ccrValue;
    } else if (servo == 2) {
        TIM3->CCR4 = ccrValue;
    }
}

// 初始化舵机为 0 度
void initServos() {
    setServoAngle(1, 0);
    setServoAngle(2, 0);
}

// 解析舵机控制指令
void parseServoCommand(const String& command) {
    if (command.startsWith("servo:")) {
        int servo = command.substring(6, 7).toInt();
        int angle = command.substring(8).toInt();
        setServoAngle(servo, angle);
    }
}

// 修改checkSerialCommand函数以支持舵机指令
void checkSerialCommand() {
    static String inputBuffer;
    while (Serial1.available()) {
        char c = Serial1.read();
        if (c == '\n' || c == '\r') {
            if (inputBuffer.startsWith(ZERO_CMD)) {
                zeroFlag = true;
                zeroCounter = 0;
            } else {
                parseServoCommand(inputBuffer);
            }
            inputBuffer = "";
        } else {
            inputBuffer += c;
        }
    }
}

// setup函数添加Serial1初始化
void setup() {
    Serial1.begin(115200);  // 上位机通信串口
    initPWM();  // 初始化PWM
    initServos();  // 初始化舵机
    imu.begin(115200);
    uw1.begin();
    uw2.begin();
    rc.begin(115200);  // 波特率设置
}

// sendCombinedData实现
void sendCombinedData(float yaw) {
    // 支持 JSON 格式输出
    char buffer[80];
    snprintf(buffer, sizeof(buffer), 
        "{\"yaw\":%.3f,\"uw1\":%d,\"uw2\":%d,\"rc\":[%d,%d,%d]}\r\n",  
        yaw, uw1_distance, uw2_distance, rc.channels[0], rc.channels[1], rc.channels[2]);
    Serial1.print(buffer);
}
