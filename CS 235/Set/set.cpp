#include "set.h"

using namespace custom;

/* custom set implementation 
 ******************************************************************************/

template <class T>
set<T>::set()
{
    init();
}

template <class T>
set<T>::set(int numCapacity)
{
    if (numCapacity < 0)
        throw "Error: set sizes must be greater than or equal to 0.";
    else
    {
        this->numCapacity = numCapacity;
        numElements = 0;

        buffer = new T[numCapacity];
    }
}

template <class T>
set<T>::set(const set<T> & rhs)
{
    *this = rhs;
}

template <class T>
set<T>::~set()
{
    delete [] buffer;
}

template <class T>
set<T> & set <T>::operator = (const set <T> & rhs)
{
    init();
    
    resize(rhs.size());

    for (int i = 0; i < rhs.size(); i++)
        insert(rhs.buffer[i]);

    return *this;
}

template <class T>
set<T> set <T>::operator || (const set <T> & rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        if (iLhs == numElements)
            result.buffer[result.numElements++] = rhs.buffer[iRhs++];
        else if (iRhs == rhs.numElements)
            result.buffer[result.numElements++] = buffer[iLhs++];
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            result.buffer[result.numElements++] = buffer[iLhs++];
            iRhs++;
        }
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            result.buffer[result.numElements++] = buffer[iLhs++];
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            result.buffer[result.numElements++] = rhs.buffer[iRhs++];
    }

    if (result.numElements == 0)
        result.buffer = NULL;
    result.numCapacity = result.numElements;

    return result;
}

template <class T>
set<T> set <T>::operator && (const set <T> & rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        if (iLhs == numElements)
        {
            if (result.numElements == 0)
                result.buffer = NULL;
            result.numCapacity = result.numElements;
            return result;
        }
        else if (iRhs == rhs.numElements)
        {
            if (result.numElements == 0)
                result.buffer = NULL;
            result.numCapacity = result.numElements;
            return result;
        }
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            result.buffer[result.numElements++] = buffer[iLhs++];
            iRhs++;
        }
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            iLhs++;
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            iRhs++;
    }

    if (result.numElements == 0)
        result.buffer = NULL;
    result.numCapacity = result.numElements;

    return result;
}

template <class T>
set<T> set <T>::operator - (const set <T> & rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        if (iLhs == numElements)
        {
            if (result.numElements == 0)
                result.buffer = NULL;
            result.numCapacity = result.numElements;
            return result;
        }
        else if (iRhs == rhs.numElements)
        {
            result.buffer[result.numElements++] = buffer[iLhs++];
        }
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            iLhs++;
            iRhs++;           
        }
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            result.buffer[result.numElements++] = buffer[iLhs++];
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            iRhs++;
    }

    if (result.numElements == 0)
        result.buffer = NULL;
    result.numCapacity = result.numElements;

    return result;
}

template <class T>
int set<T>::size() const
{
    return numElements;
}

template <class T>
bool set<T>::empty()
{
    return numElements == 0;
}

template <class T>
void set<T>::clear()
{
    numElements = 0;
}

template <class T>
void set<T>::insert(const T & t)   
{
    int iInsert = findIndex(t);    
    if (iInsert == numElements || buffer[iInsert] != t)
    {
        if (numElements == numCapacity)
            resize((numCapacity == 0) ? 1 : numCapacity * 2);
        
        for (int i = numElements; i > iInsert; i--)

            buffer[i] = buffer[i - 1];
        buffer[iInsert] = t;
        numElements++;
    }
}

template <class T>
typename set<T>::iterator set<T>::find(const T & t)
{
    iterator result;
    int index = findIndex(t);
    if (index != numElements && buffer[index] == t)
        result = iterator(buffer + index);
    return result;
}

template <class T>
typename set<T>::iterator set<T>::erase(iterator & it) 
{
    iterator empty;
    if (it != empty)
    {
        T t = *it;
        int iErase = findIndex(t);
        if (iErase != numElements && buffer[iErase] == t)
        {
            for (int i = iErase; i < numElements; i++)
                buffer[i] = buffer[i + 1];
            numElements--;
        }
    }
}

template <class T>
typename set<T>::iterator set<T>::begin()
{
    return iterator(buffer);
}

template <class T>
typename set<T>::iterator set<T>::end()
{
    return iterator(buffer + numElements);
}

template <class T>
int set<T>::findIndex(const T & t)
{
    int iBegin = 0;
    int iEnd = numElements - 1;

    while (iBegin <= iEnd)
    {
        int iMiddle = (iBegin + iEnd) / 2;

        if (buffer[iMiddle] >= t)
            iEnd = iMiddle - 1;
        else
            iBegin = iMiddle + 1;
    }
    return iBegin;
}

template <class T>
void set<T>::resize(int newCapacity)
{
    if (newCapacity == 0)
        init();
    if (newCapacity > 0)
    {
        T* newBuffer = new T[newCapacity];
        int items = (newCapacity < numElements) ? newCapacity : numElements;
        for (int i = 0; i < items; i++)
            newBuffer[i] = buffer[i];
        delete [] buffer;
        buffer = newBuffer;
        numCapacity = newCapacity;
        numElements = items;
    }
}

template <class T>
void set<T>::init()
{
    numCapacity = 0;
    numElements = 0;
    buffer = NULL;
}





/* custom set::iterator implementation 
 ******************************************************************************/

template <class T>
set<T>::iterator::iterator()
{
   ptr = NULL;
}

template <class T>
set<T>::iterator::iterator(T * p)
{
   ptr = p;
}

template <class T>
set<T>::iterator::iterator(const iterator & rhs)
{
   *this = rhs;
}

template <class T>
typename set<T>::iterator& set<T>::iterator::operator = (const iterator & rhs)
{
   ptr = rhs.ptr;
   return *this;
}

template <class T>
bool set<T>::iterator::operator != (const iterator & rhs) const 
{ 
   return rhs.ptr != this->ptr;
}

template <class T>
bool set<T>::iterator::operator == (const iterator & rhs) const 
{ 
   return rhs.ptr == this->ptr;
}

template <class T>
T& set<T>::iterator::operator * ()
{
   return *ptr;
}

template <class T>
typename set<T>::iterator& set<T>::iterator::operator ++ ()
{
   if (ptr != NULL) 
      ptr++;
   return *this;
}

template <class T>
typename set<T>::iterator set<T>::iterator::operator ++ (int postfix)
{
   iterator tmp(*this);
   if (ptr != NULL) 
      ptr++;
   return tmp;
}

template <class T>
typename set<T>::iterator& set<T>::iterator::operator -- ()
{
   if (ptr != NULL)
      ptr--;
   return *this;
}

template <class T>
typename set<T>::iterator set<T>::iterator::operator -- (int postfix)
{
   iterator tmp(*this);
   ptr--;
   return tmp;
}
