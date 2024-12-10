#ifndef TEST_ARDUINOLIBTESTING_MOCKARDUINO_FAKETIMING
#define TEST_ARDUINOLIBTESTING_MOCKARDUINO_FAKETIMING

#include <stdint.h>
#include <atomic>
#include <mutex>

namespace MockArduino {
    class FakeTime {
        public:
            FakeTime(FakeTime& other) = delete;
            void operator=(const FakeTime& other) = delete;
            static FakeTime* GetInstance();

            uint32_t millis() {
                return timestamp_ / 1000;
            }

            uint32_t micros() {
                return timestamp_ / 1000;
            }

            void advanceMillis(uint32_t millis)
            {
                timestamp_ += ((uint64_t)millis * 1000);
            }

            void advanceMicros(uint32_t micros)
            {
                timestamp_ += ((uint64_t)micros);
            }
        protected:
            static FakeTime* _instance;
            static std::mutex _createMutex;
            static void CreateInstance();
            FakeTime(): timestamp_(0){}
            std::atomic<uint64_t> timestamp_;
    };
}

inline uint32_t millis() {
    return MockArduino::FakeTime::GetInstance()->millis();
}

inline uint32_t micros() {
    return MockArduino::FakeTime::GetInstance()->micros();
}

inline void delay(uint32_t amount) 
{
    return;
}

inline void yield() {
    return;
}
#endif /* TEST_ARDUINOLIBTESTING_MOCKARDUINO_FAKETIMING */
