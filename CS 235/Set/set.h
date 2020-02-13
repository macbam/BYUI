#ifndef SET_H
#define SET_H

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
     * set
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class set
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            set();
            set(int numCapacity);
            set(const set <T> & rhs);
            ~set();


            set <T> & operator = (const set <T> & rhs);  //  = operator
            set <T> operator || (const set <T> & rhs); //  union operator
            set <T> operator && (const set <T> & rhs); //  intersection operator
            set <T> operator - (const set <T> & rhs);  //  difference operator

            int size() const;
            bool empty();
            void clear();

            void insert(const T & t);

            


            class iterator;

            iterator find(const T & t);
            iterator erase(iterator & it);

            iterator begin();
            iterator end();

        private:

            int findIndex(const T & t);
            void resize(int newCapacity);
            void init();

            T * buffer;
            int numElements;
            int numCapacity;          


    };

    /*
    * Read-write iterator for set
    */
   template <class T>
   class set <T> :: iterator
   {
      public:
         
         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif
         
         iterator();
         iterator(T * p);
         iterator(const iterator & rhs);
         iterator & operator = (const iterator & rhs);
         bool operator != (const iterator & rhs) const;
         bool operator == (const iterator & rhs) const;
         T & operator * ();
         iterator & operator ++ ();
         iterator operator ++ (int postfix);
         iterator & operator -- ();
         iterator operator -- (int postfix);

         
      private:

         T * ptr;
   
   };

}

#include "set.cpp"

#endif // SET_H