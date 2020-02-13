#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{

    /************************************************
     * queue
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class queue
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            //constructors and destructors
            queue();
            queue(int numCapacity);
            queue(const queue <T> & rhs);
            ~queue();

            queue <T> & operator = (const queue <T> & rhs);

            int size() const;
            int capacity() const;
            bool empty() const;
            void clear();

            void push(const T & t);
            void pop();
            
            T & front();
            T & front() const;

            T & back();
            T & back() const;

        private:

            void resize(int newCapacity);
            int iHead();
            int iTail();

            T * buffer;
            int numPush;
            int numPop;
            int numCapacity;
    };
}

#include "queue.cpp"

#endif // QUEUE_H