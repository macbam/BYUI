#ifndef NODE_H
#define NODE_H

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

#include<string>
using namespace std;

/***********************************************
 * NODE
 **********************************************/
template <class T>
class node
{
    public:
        node();
        node(T t);

        T data;
        node<T> * pNext;
        node<T> * pPrev;
};

#include "linked_list.cpp"

#endif // NODE_H