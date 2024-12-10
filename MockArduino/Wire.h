#ifndef _MOCK_ARDUINO_WIRE_H_
#define _MOCK_ARDUINO_WIRE_H_

#include <Arduino.h>
#include <RingBuffer.h>

namespace MockArduino {
    class FakeTWI 
    {
        public:
            FakeTWI(): txAddress_(0x0), didBegin_(false){};

            void begin() {
                didBegin_ = true;
                dataTransmitted_.clear();
            }

            void begin(uint8_t address) {
                didBegin_ = true;
                txAddress_ = address;
                dataTransmitted_.clear();
            }
            void beginTransmission(uint8_t address) {
                txAddress_ = address;
                dataTransmitted_.clear();
            }

            size_t write(uint8_t dataByte) {
                return dataTransmitted_.write(dataByte);
            }

            size_t write(const uint8_t* data, size_t dataSize) {
                return dataTransmitted_.write(data, dataSize);
            }

            int available() {
                return dataToMockRead_.available();
            }

            int read() {
                return dataToMockRead_.read();
            }

            uint8_t requestFrom(uint8_t address, uint8_t noBytes) {
                dataToMockRead_.clear();
                while(noBytes--) {
                    uint8_t c;
                    if (dataQueuedForRead_.pop(c)) {
                        dataToMockRead_.push(c);
                    } else {
                        c = 0;
                        dataToMockRead_.push(c);
                    }
                }
            }
        
            uint8_t endTransmission() {
                return endTransmission(1);
            }

            uint8_t endTransmission(uint8_t sendStop){
                return 0;
            }

            uint8_t lastTxAddress() const {
                return txAddress_;
            }

            bool hasBegun() const {
                return didBegin_;
            }

            ByteBuffer<1024>& TransmittedData() {
                return dataTransmitted_;
            }
        protected:
            uint8_t txAddress_;
            bool didBegin_;
            ByteBuffer<1024> dataTransmitted_;
            ByteBuffer<1024> dataToMockRead_;
            ByteBuffer<1024> dataQueuedForRead_;
    };
}

using TwoWire = MockArduino::FakeTWI;
extern TwoWire Wire;

#endif /* _MOCK_ARDUINO_WIRE_H_ */
