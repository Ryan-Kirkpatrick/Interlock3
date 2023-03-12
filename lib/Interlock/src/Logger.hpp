#pragma once
#include <string>
#include "Core.hpp"

class Logger {
    public:
        Logger(bool useSerial = true);

        // Add an entry into the log. ALso prints to Serial.

        /**
         * @brief Add an entry to the log. Appends newline to string.
         * Will print to serial if set up to do so. 
         * 
         * @param logText 
         */
        void log(std::string logText);

        /**
         * @brief Obtain a NULL terminated string of saved log entries.
         * As more things are logged old log entries will be pushed out of the buffer and lost.
         * Logging additional items will invalidate the pointer returned by this function.
         * 
         * @return const char* The logs.
         */
        const char *getLogs();

    private:
        template<size_t size>
    class CircularBuffer {
        public:
            CircularBuffer();

            /**
             * @brief Will insert up to `size`-1 characters into the buffer.
             * 
             * @param str The string to be put into the buffer. Strings that are too long will be chopped off.
             * @return size_t The number of characters placed into the buffer (excluding NULL terminator).
             */
            void insert(const char *str);

            /**
             * @brief Obtain the contents of the ring buffer as a NULL terminated string.
             * This function returns a pointer to the start of the underlying (non-circular) buffer.
             * Inserting anything after calling this function will invalidate the pointer.
             * 
             * @return const char* The contents of the buffer as a NULL terminated string.
             */
            const char *getContents();

        private:

            /**
             * @brief Shifts all the elements in the buffer to the (true) start of the buffer.
             * Allows the underlying contents to be accessed as a normal buffer / null terminated string.
             * 
             */
            void shiftToStart();

            template<size_t bufferSize>
            class CyclicIndex {
                public:
                    CyclicIndex(size_t startIndex) : index{startIndex} {}
                    void operator++(int) {
                        if (index == (bufferSize - 1)) {
                            index = 0;
                            return;
                        }
                        index++;
                    }
                    void operator--(int) {
                        if (index == 0) {
                            index = bufferSize - 1;
                            return;
                        }
                        index--;
                    }
                    size_t value() const {
                        return index;
                    }
                private:
                    size_t index;
            };

            char buffer[size] = {'\0'};
            CyclicIndex<size> startOfBuffer;
            CyclicIndex<size> endOfBuffer; // Should be placed at a null terminator
        };

        CircularBuffer<Core::LOG_SIZE> buffer;
        const bool useSerial = true;

};