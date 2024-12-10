#ifndef TEST_ARDUINOLIBTESTING_MOCKARDUINO_STREAMSTDOUT
#define TEST_ARDUINOLIBTESTING_MOCKARDUINO_STREAMSTDOUT

#include <Stream.h>
#include <iostream>
namespace MockArduino {
    class StreamStdOut: public Stream {
        public:
            int available() override {
                return 0;
            }
            int read() override {
                return EOF;
            }

            int peek() override {
                return EOF;
            }

            size_t write(uint8_t c) {
                std::cout.put(c);
                if (std::cout.good()) return 1;
                else return 0;
            }
    };
}

extern MockArduino::StreamStdOut Serial;

#endif /* TEST_ARDUINOLIBTESTING_MOCKARDUINO_STREAMSTDOUT */
