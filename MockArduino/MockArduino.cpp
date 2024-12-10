#include <Arduino.h>
#include <Wire.h>
#include <RingBuffer.h>

TwoWire Wire;

MockArduino::FakeTime* MockArduino::FakeTime::_instance = nullptr;
std::mutex MockArduino::FakeTime::_createMutex;

MockArduino::FakeTime* MockArduino::FakeTime::GetInstance()
{
    if (_instance == nullptr) 
    {
        std::lock_guard<std::mutex> lock(_createMutex);
        if(_instance == nullptr) {
            _instance = new FakeTime();
        }
    }
    return _instance;
}

MockArduino::StreamStdOut Serial;