#pragma once
#include <Arduino.h>

class UWParser {
public:
    typedef void (*DistanceCallback)(int); // 回调类型
    
    // 修改构造函数
    UWParser(HardwareSerial* ser, HardwareSerial* out, DistanceCallback cb)
        : _serial(ser), _output(out), _callback(cb) {}

private:
    DistanceCallback _callback; // 回调成员
    HardwareSerial* _serial;
    HardwareSerial* _output;
    uint8_t _buffer[4];
    uint8_t _index = 0;
    enum State { SYNC_HEADER, DATA_H, DATA_L, CHECKSUM };
    State _state = SYNC_HEADER;

public:
    UWParser(HardwareSerial* ser, HardwareSerial* out) 
        : _serial(ser), _output(out) {}

    void begin() {
        _serial->begin(115200, SERIAL_8N1);
    }

    void processData() {
        while (_serial->available()) {
            uint8_t byte = _serial->read();
            
            switch(_state) {
                case SYNC_HEADER:
                    if(byte == 0xFF) {
                        _buffer[0] = byte;
                        _state = DATA_H;
                    }
                    break;
                    
                case DATA_H:
                    _buffer[1] = byte;
                    _state = DATA_L;
                    break;
                    
                case DATA_L:
                    _buffer[2] = byte;
                    _state = CHECKSUM;
                    break;
                    
                case CHECKSUM:
                    _buffer[3] = byte;
                    if(validateChecksum()) {
                        uint16_t distance = (_buffer[1] << 8) | _buffer[2];
                        sendDistance(distance); //参数传递
                    }
                    _state = SYNC_HEADER;
                    break;
            }
        }
    }

private:
    bool validateChecksum() {
        uint8_t sum = (_buffer[0] + _buffer[1] + _buffer[2]) & 0xFF;
        return sum == _buffer[3];
    }
    // 在UWParser类中修改输出逻辑
    void sendDistance(int distance) {
        if(_callback) _callback(distance); // 保持回调
        
        // 仅在输出串口有效时发送数据
        if(_output) {
            _output->print(_serial == &Serial4 ? "UW1:" : "UW2:");
            _output->println(distance);
        }
    }
};
