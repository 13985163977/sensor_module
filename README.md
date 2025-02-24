# sensor
核心功能；串口接收数据，处理后iic发送给上位机

开发工具；STM32CUBEIDE(CUBEMX) 

开发系统；FreeRRTOS 

开发板；STM32F407VET6 

板载设备；LED_BLUE(PB2),LED_ERD(PC5),KEY_1(PA0),8MHz高速晶振（PH0,PH1），无低速晶振（PC14,PC15），USART1(USB接口PA9,PA10)，调试引脚（PB13,PB14）
 
外接设备；

IMU惯导模块（瑞芬68协议，长度不定），usart2

RC遥控器接收机；（数据已解码）,usart3

超声波测距模块a（距离数据），uart4

超声波测距模块b（距离数据），uart5

上位机树莓派5，IIC1
