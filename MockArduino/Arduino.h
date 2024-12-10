#ifndef _MOCK_ARDUINO_H_
#define _MOCK_ARDUINO_H_

#include <stdint.h>
#include <cmath>

// #ifndef abs
//   #define abs(x) ((x)>0?(x):-(x))
// #endif
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
// #ifndef round
//     #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
// #endif
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts()
#define noInterrupts()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

#define LOW 0
#define HIGH 1 

#include <Print.h>
#include <Printable.h>
#include <Stream.h>
#include <FakeTiming.h>
#include <StreamStdOut.h>
#endif /* _MOCK_ARDUINO_H_ */
