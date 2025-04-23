#pragma once
#include <Arduino.h>

// 前置声明
void sendCombinedData(float yaw);

class IMUParser {
private:
    // 修正状态枚举定义
    enum ParseState { 
        SYNC_HEADER,   // 帧头同步
        SYNC_LENGTH,   // 数据长度验证
        SYNC_ADDRESS,  // 地址码验证
        SYNC_CMD,      // 命令字验证
        DATA_COLLECT   // 数据收集
    };
    
    ParseState _state = SYNC_HEADER;
    HardwareSerial* _recvSerial;
    HardwareSerial* _sendSerial;
    uint8_t _buffer[20];  // 数据接收缓冲区
    uint8_t _index = 0;   // 缓冲区索引
    bool _sync = false;   // 同步标志

public:
    IMUParser(HardwareSerial* recvSer, HardwareSerial* sendSer)
        : _recvSerial(recvSer), _sendSerial(sendSer) {}

    void begin(unsigned long baud) {
        _recvSerial->begin(baud, SERIAL_8N1);
        _sendSerial->begin(baud, SERIAL_8N1);
    }
    uint8_t _dataLength = 0;

    void processData() {
        while (_recvSerial->available()) {
            uint8_t byte = _recvSerial->read();
            
            // 状态机解析
            switch(_state) {
#define FRAME_HEADER 0x68

                case SYNC_HEADER:
                    if(byte == FRAME_HEADER) {
                        _state = SYNC_LENGTH;
                    }
                    break;
                    
                case SYNC_LENGTH:
#define DATA_LENGTH 0x0D

                    if(byte == DATA_LENGTH) {
                        _state = SYNC_ADDRESS;
                    } else {
                        _state = SYNC_HEADER;
                    }
                    break;
                    
                case SYNC_ADDRESS:
#define ADDRESS_CODE 0x00

                    if(byte == ADDRESS_CODE) {
                        _state = SYNC_CMD;
                    } else {
                        _state = SYNC_HEADER;
                    }
                    break;
                    
                case SYNC_CMD:
#define COMMAND_BYTE 0x84

                    if(byte == COMMAND_BYTE) {
                        _index = 0;
                        _dataLength = 9;  // 数据域9字节
                        _state = DATA_COLLECT;
                    } else {
                        _state = SYNC_HEADER;
                    }
                    break;
                    
                case DATA_COLLECT:
                    _buffer[_index++] = byte;
                    if(_index >= _dataLength) {
                        parseYaw();
                        _state = SYNC_HEADER;
                    }
                    break;
            }
        }
    }
    void parseYaw() {
        // 提取数据域中的YAW信息（数据域共9字节）
        uint8_t signByte = _buffer[6];   // 数据域第7字节
        uint8_t highByte = _buffer[7];   // 数据域第8字节
        uint8_t lowByte = _buffer[8];    // 数据域第9字节
        
        // 解析符号位（00为正，非00为负）
        bool isNegative = (signByte != 0x00);
        
        // 解析BCD数值（四位数）
        int value = ((highByte >> 4) & 0x0F) * 1000 
                  + ((highByte & 0x0F) * 100)
                  + ((lowByte >> 4) & 0x0F) * 10
                  + (lowByte & 0x0F);
        
        // 补零并计算最终值
        float yaw = value * 10.0f / 1000.0f;
        if(isNegative) yaw *= -1;
        
        // 发送格式化数据
        // 修改输出格式
        char buffer[20];
        // 使用安全格式化并添加等号
        snprintf(buffer, sizeof(buffer), "yaw=%.3f\r\n", yaw);
        // 改为调用组合输出
        sendCombinedData(yaw);
    }
};
