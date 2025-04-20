// 保留唯一初始化部分
#include <Arduino.h>
#include "imu.h"
#include "uw.h"
#include <HardwareSerial.h>
#include "rc.h"
// 添加硬件串口定义
HardwareSerial Serial3(USART3);  // RX=PB11, TX=PB10
RCParser rc(&Serial3);

// 串口初始化
HardwareSerial Serial2(USART2); // PA3(RX), PA2(TX)
HardwareSerial Serial4(PA1, PC10);  // RX=PA1, TX=PC10
HardwareSerial Serial5(PD2, PC12);  // RX=PD2, TX=PC12

// 提前声明回调函数
void updateUW1(int distance);
void updateUW2(int distance);
// UW初始化（带回调参数的版本）
UWParser uw1(&Serial4, &Serial1, updateUW1);  
UWParser uw2(&Serial5, &Serial1, updateUW2);  



// IMU初始化
IMUParser imu(&Serial2, &Serial1);

// 全局变量和阈值定义
const int DISTANCE_THRESHOLD = 100; //距离阈值
const int TIME_DIFF_THRESHOLD = 100; //时间差阈值

// UW数据存储
volatile int uw1_distance = -1;
volatile int uw2_distance = -1;

// 回调函数实现
void updateUW1(int distance) { uw1_distance = distance; }
void updateUW2(int distance) { uw2_distance = distance; }

// 新增清零指令相关
const char ZERO_CMD[] = "ZERO";  // 上位机指令
bool zeroFlag = false;           // 清零触发标志
unsigned long lastSendTime = 0;  // 时间间隔控制
byte zeroCounter = 0;            // 发送次数计数

// 清零命令帧：68 04 00 28 2C
const byte zeroPacket[5] = {0x68, 0x04, 0x00, 0x28, 0x2C};

// 新增清零指令处理函数
void checkSerialCommand() {
    static String inputBuffer;
    while (Serial1.available()) {
        char c = Serial1.read();
        if (c == '\n' || c == '\r') {
            if (inputBuffer == ZERO_CMD) {
                zeroFlag = true;
                zeroCounter = 0;
            }
            inputBuffer = "";
        } else {
            inputBuffer += c;
        }
    }
}

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
// setup函数添加Serial1初始化
void setup() {
    Serial1.begin(115200);  // 上位机通信串口
    imu.begin(115200);
    uw1.begin();
    uw2.begin();
    rc.begin(115200);  // 波特率设置
}

// sendCombinedData实现
void sendCombinedData(float yaw) {
    char buffer[40];
    snprintf(buffer, sizeof(buffer), 
        "YAW:%.3f\r\n",  
        yaw);              //移除boundary参数
    Serial1.print(buffer);
}
