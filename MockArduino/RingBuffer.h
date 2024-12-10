#ifndef _ARDUINO_LIB_TESTING_RING_BUFFER_H_
#define _ARDUINO_LIB_TESTING_RING_BUFFER_H_

#include <Stream.h>
#include <stdint.h>

namespace MockArduino {
    template<bool size_greater_255> struct RingBufferIndexHelper
    {
        using Type = uint16_t;
        using CalcType = uint32_t;
    };

    template<> struct RingBufferIndexHelper<false>
    {
        using Type = uint8_t;
        using CalcType = uint16_t;
    };


    template<typename StoredElement,
             size_t BufferSize,
             typename IndexType = typename RingBufferIndexHelper<(BufferSize > 255)>::Type,
             typename IndexCalcType = typename RingBufferIndexHelper<(BufferSize > 255)>::CalcType>
    class RingBuffer
    {
        static_assert(BufferSize > 0, "RingBuffer must have a BufferSize greater than 0");

        static_assert(BufferSize <= UINT16_MAX, "Maximum BufferSize is 65535 elements");
        public:
            RingBuffer();

            bool push(const StoredElement in);

            bool pop(StoredElement& out);

            void clear();

            IndexType size() const {return storedSize_; };

            IndexType maxSize() const {return BufferSize; }; 

            StoredElement& operator[](IndexType i);

            bool peek(StoredElement& out, const IndexCalcType index = 0) const;

            bool isFull() const { return storedSize_ == BufferSize ;};

            bool isEmpty() const { return storedSize_ == 0; };
        protected:
            StoredElement dataBuffer_[BufferSize];
            IndexType readIndex_;
            IndexType storedSize_;

            IndexType writeIndex();
            void incrementReadIndex();
    };

    template<typename E, size_t S, typename I, typename C>
    RingBuffer<E, S, I, C>::RingBuffer(): readIndex_(0), storedSize_(0){};



    template<typename E, size_t S, typename I, typename C>
    I RingBuffer<E, S, I, C>::writeIndex() {
        C i = (C)readIndex_ + (C)storedSize_;
        if (i >= (C)S)
        {
            i -= (C)S;
        }
        return (I)i;
    }

    template<typename E, size_t S, typename I, typename C>
    void RingBuffer<E, S, I, C>::incrementReadIndex() {
        C i = readIndex_;
        i++;
        if (i >= (C)S)
        {
            i -= (C)S;
        }
        readIndex_ = i;
    }

    template<typename E, size_t S, typename I, typename C>
    void RingBuffer<E, S, I, C>::clear() {
        readIndex_ = 0;
        storedSize_ = 0;
        memset(dataBuffer_, 0, sizeof(dataBuffer_));
    }

    template<typename E, size_t S, typename I, typename C>
    bool RingBuffer<E, S, I, C>::push(const E in) {
        if (isFull()) return false;
        auto i = writeIndex();
        dataBuffer_[i] = in;
        storedSize_++;
        return true;
    }

    template<typename E, size_t S, typename I, typename C>
    bool RingBuffer<E, S, I, C>::pop(E& out) {
        if (isEmpty()) return false;
        auto i = readIndex_;
        out = dataBuffer_[i];
        incrementReadIndex();
        storedSize_--;
        return true;
    }

    template<typename E, size_t S, typename I, typename C>
    bool RingBuffer<E, S, I, C>::peek(E& out, const C index /* = 0*/) const {
        if (isEmpty() || size() < index) return false;
        C i = (C)readIndex_ + index;
        if (i >= (C)S) {
            i -= (C)S;
        }
        out = dataBuffer_[i];
        return true;
    }

    template<typename E, size_t S, typename I, typename C>
    E& RingBuffer<E, S, I, C>::operator[](I index) {
        if (index >= storedSize_) return dataBuffer_[0];
        C i = (C)readIndex_ + (C)index;
        if (i >= (C)S) {
            i -= (C)S;
        }
        return dataBuffer_[i];
    }

    template<size_t SIZE>
    class ByteBuffer: public RingBuffer<uint8_t, SIZE>, public Stream {
        public:
            using Base = RingBuffer<uint8_t, SIZE>;
            ByteBuffer(): RingBuffer<uint8_t, SIZE>(){};

            virtual int available() override {
                return Base::size();
            }

            virtual int read() override {
                uint8_t c;
                if(Base::pop(c)) return c;
                else return -1;
            }

            virtual int peek() override {
                uint8_t c;
                if(Base::peek(c)) return c;
                else return -1;
            }

            using Print::write;

            virtual size_t write(uint8_t c) override {
                if (Base::push(c)) return 1;
                else return 0;
            }


    };
}
#endif /* _ARDUINO_LIB_TESTING_RING_BUFFER_H_ */
