#ifndef BNODE_H
#define BNODE_H

/***********************************************
 * BNODE
 **********************************************/
template <class T>
class BNode
{
    public:
        T data;

        BNode * pLeft;
        BNode * pRight;
        BNode * pParent;

        BNode();
        BNode(const T & t);

};

#include "bnode.cpp"

#endif // BNODE_H