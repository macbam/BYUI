#ifndef DEQUE_H
#define DEQUE_H

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
     * deque
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class deque
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            //constructors and destructors
            deque();
            deque(int numCapacity);
            deque(const deque <T> & rhs);
            ~deque();

            deque <T> & operator = (const deque <T> & rhs);

            int size() const;
            bool empty() const;
            void clear();

            void push_front(const T & t);
            void push_back(const T & t);

            void pop_front();
            void pop_back();

            T & front();

            T & back();


        private:

            void resize(int newCapacity);
            int capacity();
            int iFrontNormalize();
            int iBackNormalize();
            int iNormalize(int normalize);

            T * buffer;
            int iFront;
            int iBack;
            int numCapacity;
    };
}

#include "deque.cpp"

#endif // DEQUE_H