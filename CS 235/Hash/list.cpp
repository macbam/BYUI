#include "list.h"

using namespace custom;

// list implementation
//*****************************************************************************
template <class T>
list<T>::list()
{
   init();
}
 
template <class T> 
list<T>::list(const list<T>& rhs)
{
   init();
   *this = rhs; 
} 

template <class T>
list<T>::~list()
{
   clear();
}

template <class T>
list<T>& list<T>::operator = (const list<T>& rhs)
{
   clear();
   for (node* p = rhs.pHead; p; p = p->pNext)
      insertAt(pTail, p->data, true);
   return *this;
}

template <class T>
int list<T>::size()
{
   return numElements;
}

template <class T>
bool list<T>::empty()
{
   return (numElements == 0);
}

template <class T>
void list<T>::clear()
{
   node* pCurrent = pHead;
	while(pCurrent)
	{
      node* pTarget = pCurrent;
      pCurrent = pCurrent->pNext;
      delete [] pTarget;
		numElements--;
	}
   pHead = NULL;
   pTail = NULL;
}

template <class T>
T& list<T>::front()
{
   if(empty())
   {
      throw "Error: Calling front on empty list.";
   }
   return pHead->data;
}

template <class T>
T& list<T>::back()
{
   if(empty())
   {
      throw "Error: Calling back on empty list.";
   }
   return pTail->data;
}

template <class T>
void list<T>::push_front(T element)
{
   insertAt(pHead, element, false);
}

template <class T>
void list<T>::push_back(T element)
{
   insertAt(pTail, element, true);
}

template <class T>
void list<T>::pop_front()
{
   if (!empty())
   {
      pHead = pHead->pNext;
      pHead->pPrev = NULL;
      numElements--;
   }
}

template <class T>
void list<T>::pop_back()
{
   if (!empty())
   {
      pTail = pTail->pPrev;
      pTail->pNext = NULL;
      numElements--;
   }
}

template <class T>
void list<T>::insert(iterator it, T element)
{
   insertAt(it.ptr, element, false); // before is the default behavior
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator it)
{
   node* pTarget = it.ptr;
   
   if (pTarget == NULL)
      return iterator(NULL);

   node* pResult = (pTarget->pPrev) ? pTarget->pPrev : pTarget->pNext;
   
	if (pTarget->pPrev)
		pTarget->pPrev->pNext = pTarget->pNext;

	if (pTarget->pNext)
		pTarget->pNext->pPrev = pTarget->pPrev;

   if (pTarget == pHead)
      pHead = pTarget->pNext;

	delete [] pTarget;
   pTarget = NULL;

	return iterator(pResult);
}

template <class T>
typename list<T>::iterator list<T>::find(T element)
{
   iterator result;
   for (node* p = pHead; p; p = p->pNext)
		if (p->data == element)
      {
			result = iterator(p);
         break;
      }
	return result;
}

template <class T>
typename list<T>::iterator list<T>::begin()
{
   return iterator(pHead);
}

template <class T>
typename list<T>::iterator list<T>::end()
{
   return iterator(pTail);
}

template <class T>
void list<T>::insertAt(node* pCurrent, T element, bool after)
{
   node* pNew = new node(element);
   
   if(empty())
	{
		pHead = pNew;
		pTail = pNew;
      numElements++;
      return;
	}

   if (after == false) // before 
   {
      if (pHead == pCurrent) // the head
         pHead = pNew; // we have a new head

      pNew->pNext = pCurrent;
      pNew->pPrev = pCurrent->pPrev;
      pCurrent->pPrev = pNew;
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;
      
      numElements++;
   }
   else
   {

      if (pTail == pCurrent)
         pTail = pNew;

      pNew->pPrev = pCurrent;
      pNew->pNext = pCurrent->pNext;
      pCurrent->pNext = pNew;
      if (pNew->pNext)
         pNew->pNext->pPrev = pNew;

      numElements++;
   }

   
}

template <class T>
void list<T>::init()
{
   pHead = NULL;
   pTail = NULL;
   numElements = 0;
}

// node implementation
//*****************************************************************************
template <class T>
list<T>::node::node()
{
   data = T();
   pPrev = NULL;
   pNext = NULL;
}

template <class T>
list<T>::node::node(T t)
{
   data = t;
   pPrev = NULL;
   pNext = NULL;
}

template <class T>
list<T>::node::~node()
{
   // TODO
}

// iterator implementation
//*****************************************************************************
template <class T>
list<T>::iterator::iterator()
{
   ptr = NULL;
}

template <class T>
list<T>::iterator::iterator(node* aNode)
{
   ptr = aNode;
}

template <class T>
list<T>::iterator::iterator(const iterator& rhs)
{
   *this = rhs;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator = (const iterator& rhs)
{
   ptr = rhs.ptr;
   return *this;
} 

template <class T>
bool list<T>::iterator::operator != (const iterator& rhs) const
{
   return ptr != rhs.ptr;
}

template <class T>
bool list<T>::iterator::operator == (const iterator& rhs) const
{
   return ptr == rhs.ptr;
}

template <class T>
T& list<T>::iterator::operator * ()
{
   if (ptr == NULL)
      throw "Error: Dereferencing null node.";
   return ptr->data;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator ++ ()
{
   if (ptr == NULL)
      throw "Error: Incrementing null node.";
   if (ptr->pNext)
      ptr = ptr->pNext;
   return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator ++ (int postfix)
{
   iterator tmp = *this;
   ++(*this);
   return tmp;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator -- ()
{
   if (ptr == NULL)
      throw "Error: Decrementing null node.";
   if (ptr->pPrev)
      ptr = ptr->pPrev;
   return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator -- (int postfix)
{
   iterator tmp = *this;
   --(*this);
   return tmp;
}
