#ifndef STACK_H
#define STACK_H

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
     * stack
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class stack
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            //constructors and destructors
            stack();
            stack(int numCapacity);
            stack(const stack <T> & rhs);
            ~stack();

            //
            stack <T> & operator = (const stack <T> & rhs);

            int size() const;
            int capacity() const;
            bool empty() const;
            void clear();

            void push(const T & t);
            void pop();
            T & top();
            T top() const;

        private:

            void resize(int newCapacity);

            T * buffer;
            int numElements;
            int numCapacity;
    };


}

#include "stack.cpp"

#endif // STACK_H