#include "bnode.h"


/* Binary Tree implementation 
 ******************************************************************************/
template <class T>
BNode<T>::BNode()
{
    pParent = NULL;
    pLeft = NULL;
    pRight = NULL;

    data = 0;
}

template <class T>
BNode<T>::BNode(const T & t)
{
    pParent = NULL;
    pLeft = NULL;
    pRight = NULL;

    data = t;
}

template <class T>
void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pNode)
    {
        pNode->pLeft = pAdd;
        if (pAdd)
            pAdd->pParent = pNode;
    }
}

template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pNode)
    {
        pNode->pRight = pAdd;
        if (pAdd)
            pAdd->pParent = pNode;
    }
}

template <class T>
void addLeft(BNode <T> * pNode, const T & t)
{
    addLeft(pNode, new BNode<T>(t));
}

template <class T>
void addRight(BNode <T> * pNode, const T & t)
{
    addRight(pNode, new BNode<T>(t));
}

template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
    if (pRoot == NULL)
        return 0;
    return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
}

template <class T>
void deleteBTree(BNode <T> * & pNode)
{
    if (pNode == NULL)
        return;
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);
    delete pNode;
    pNode = NULL;
}

template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc)
{
    if (pSrc == NULL)
        return NULL;

    BNode<T> * pDestination = new BNode<T> (pSrc->data);

    pDestination->pLeft = copyBTree(pSrc->pLeft);
    if (pDestination->pLeft)
        pDestination->pLeft->pParent = pDestination;

    pDestination->pLeft = copyBTree(pSrc->pRight);
    if (pDestination->pRight)
        pDestination->pRight->pParent = pDestination;

    return pDestination;    
}

template <class T>
std::ostream& operator << (std::ostream & out, const BNode<T> * rhs)
{
    displayLVR(out, rhs);

    return out;
}

template <class T>
void displayLVR(std::ostream & out, const BNode <T> * pHead)
{
    if (pHead == NULL)
        return;
    
    displayLVR(out, pHead->pLeft);  // L
    out << pHead->data << " ";      // V
    displayLVR(out, pHead->pRight); // R
}