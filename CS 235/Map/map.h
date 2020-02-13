#ifndef MAP_H
#define MAP_H

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

#include "bst.h"


namespace custom
{
    /***********************************************
     * MAP
     **********************************************/
    template <class K, class V>
    class map
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            class pair;
            class iterator;

            map();
            map(const map<K, V> & rhs);

            map <K, V> & operator = (const map<K, V> & rhs);
            V & operator [] (const K & k);

            int size() const;
            bool empty() const;
            void clear();

            void insert(const K & k, const V & v);
            //void insert(const pair <K, V> & input);  don't need for unit test

            iterator find(const K & k);
            iterator begin();
            iterator end();

        private:
            BST<pair> bst;
    };

    template<class K, class V>
    class map<K, V>::pair
    {
        public:
            pair();
            pair(const K & first, const V & second);

            pair& operator = (const pair & rhs);

            const K & getFirst() const;
            const V & getSecond() const;

            bool operator >  (const pair & rhs) const;
            bool operator >= (const pair & rhs) const;
            bool operator <  (const pair & rhs) const;
            bool operator <= (const pair & rhs) const;
            bool operator == (const pair & rhs) const;
            bool operator != (const pair & rhs) const;

            K first;
            V second;
    };

    template<class K, class V>
    class map<K, V>::iterator
    {
        public:

            #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
            #endif

            iterator();
            iterator(const typename BST<pair>::iterator& rhs);
            iterator(const iterator& rhs);

            iterator& operator = (const iterator& rhs);
            bool operator == (const iterator& rhs) const;
            bool operator != (const iterator& rhs) const;
            pair& operator * ();
            iterator& operator ++ ();
            iterator operator ++ (int postfix);
            iterator& operator -- ();
            iterator operator -- (int postfix);

        private:
            typename BST<pair>::iterator it;
    };
}

    #include "map.cpp"

    #endif // MAP_H