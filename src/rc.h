#pragma once
#include <Arduino.h>

class RCParser {
private:
    HardwareSerial* _serial;
    enum { HEADER, DATA, FLAG, XOR } _state = HEADER;
    uint8_t _buffer[34]; // 32字节通道数据 + flag + xor
    uint8_t _index = 0;
    
public:
    // 存储提取的通道数据 (1,3,6,8)
    int channels[4] = {0};  // 修改数组大小为4

    RCParser(HardwareSerial* serial) : _serial(serial) {}

    void begin(uint32_t baud) {
        _serial->begin(baud, SERIAL_8N1);
    }

    void processData() {
        while (_serial->available()) {
            uint8_t byte = _serial->read();
            
            switch (_state) {
                case HEADER:
                    if (byte == 0x0F) {
                        _state = DATA;
                        _index = 0;
                    }
                    break;
                    
                case DATA:
                    _buffer[_index++] = byte;
                    if (_index >= 32) _state = FLAG;
                    break;
                    
                case FLAG:
                    _buffer[32] = byte; // 存储flag
                    _state = XOR;
                    break;
                    
                case XOR: {
                    uint8_t calc_xor = 0;
                    for(int i=0; i<33; i++) calc_xor ^= _buffer[i];
                    
                    if(calc_xor == byte) {
                        // 提取通道1,3,6,8 (对应数组索引0,1,2,3)
                        channels[0] = (_buffer[0]<<8) | _buffer[1];   // ch1
                        channels[1] = (_buffer[4]<<8) | _buffer[5];   // ch3
                        channels[2] = (_buffer[10]<<8)| _buffer[11];  // ch6
                        channels[3] = (_buffer[14]<<8)| _buffer[15];  // ch8
                        
                        sendRCData();
                    }
                    _state = HEADER;
                    break;
                }
            }
        }
    }

private:
    void sendRCData() {
        char buffer[60];
        snprintf(buffer, sizeof(buffer),
            "RC:%d,%d,%d,%d\r\n",  // 修改为4个参数
            channels[0], channels[1], 
            channels[2], channels[3]);
        Serial1.print(buffer);
    }
};
