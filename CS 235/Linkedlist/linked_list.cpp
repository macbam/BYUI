#include "linked_list.h"


/* linked list implementation 
 ******************************************************************************/
template <class T>
node<T>::node()
{
    data = 0;
    pPrev = NULL;
    pNext = NULL;
}

template <class T>
node<T>::node(T t)
{
    data = t;
    pPrev = NULL;
    pNext = NULL;
}

template <class T>
node<T>* copy(node<T>* pSource)
{
    if (pSource == NULL)
        return NULL;

    node<T>* pDestination = new node<T>(pSource->data);
    node<T>* pDes = pDestination;

    if (pSource->pNext)
        for (node<T>* p = pSource->pNext; p; p = p->pNext)
            pDes = insert(pDes, p->data, true);

    return pDestination;
}

template <class T>
node<T>* insert(node<T>* pCurrent, T value, bool after = false)
{
    if (pCurrent == NULL)
        throw "Error: inserting into NULL list.";

    node<T>* pNew = new node<T>(value);
    if (pCurrent != NULL && after == false)
    {
        pNew->pNext = pCurrent;
        pNew->pPrev = pCurrent->pPrev;
        pCurrent->pPrev = pNew;
        if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
    }
    if (pCurrent != NULL && after == true)
    {
        pNew->pNext = pCurrent->pNext;
        pNew->pPrev = pCurrent;
        pCurrent->pNext = pNew;
        if (pNew->pNext)
            pNew->pNext->pPrev = pNew;
    }
    return pNew;

}

template <class T>
node<T>* find(node<T>* pHead, T value)
{
    for (node<T>* p = pHead; p; p = p->pNext)
        if (p->data == value)
            return p;
    return NULL;
}

template <class T>
void clear(node<T>*& pHead)
{
    if (pHead == NULL)
        throw "Error: freeing NULL list.";

    while (pHead != NULL)
    {
        node<T> * p = pHead->pNext;
        delete [] pHead;
        pHead = p;
    }
    
    // for (node<T>* p = pHead; p; p = p->pNext)
    //     delete p;
    pHead = NULL;
}

template <class T>
node<T>* remove(node<T>*& pRemove)
{
    node<T>* pReturn = NULL;

    if (pRemove == NULL)
        return NULL;

    if (pRemove->pPrev == NULL && pRemove->pNext == NULL)
    {
        delete [] pRemove;
        pRemove = NULL;
        return NULL;
    }

    if (pRemove->pPrev)
        pRemove->pPrev->pNext = pRemove->pNext;
    if (pRemove->pNext)
        pRemove->pNext->pPrev = pRemove->pPrev;

    if (pRemove->pPrev)
        pReturn = pRemove->pPrev;
    else
        pReturn = pRemove->pNext;

    delete [] pRemove;
    pRemove = NULL;

    return pReturn;
}


