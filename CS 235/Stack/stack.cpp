#include "stack.h"

using namespace custom;

/* custom stack implementation 
 ******************************************************************************/

template <class T>
stack<T>::stack()
{
    numCapacity = 0;
    numElements = 0;
    buffer = NULL;
}

//FINISH
template <class T>
stack<T>::stack(int numCapacity)
{
    if (numCapacity <= 0)
    {
        this->numCapacity = 0;
        this->numElements = 0;
        this->buffer = NULL;
        return;
    }

    this->numCapacity = numCapacity;
    this->numElements = 0;

    
    this->buffer = new T[numCapacity];
    for (int i = 0; i < numCapacity; i++)
      this->buffer[i] = T();

}

template <class T>
stack<T>::stack(const stack <T> & rhs)
{
    *this = rhs;
}

template <class T>
stack<T>::~stack()
{
    delete [] buffer;
}

template <class T>
stack<T> & stack<T>::operator = (const stack <T> & rhs)
{
    numCapacity = rhs.numElements;
    numElements = rhs.numElements;
    buffer = new T[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++)
        buffer[i] = rhs.buffer[i];
    return *this;
}

template <class T>
int stack<T>::size() const
{
    return numElements;
}

template <class T>
int stack<T>::capacity() const
{
    return numCapacity;
}

template <class T>
bool stack<T>::empty() const
{
    if (size() == 0)
        return true;
    else
        return false;    
}

template <class T>
void stack<T>::clear()
{
    numElements = 0;
}

template <class T>
void stack<T>::push(const T & t)
{
    if (numElements == numCapacity)
        resize((numCapacity == 0) ? 1 : numCapacity * 2);
    buffer[numElements++] = t;
}

template <class T>
void stack<T>::pop()
{
    if (!empty())
        --numElements;
}

template <class T>
T & stack<T>::top() //throw (const char *)
{
    if (numElements == 0 || numCapacity == 0)
        throw "Error: asking for top of empty stack.";
    if(!empty())
        return buffer[size() - 1];
}

template <class T>
T stack<T>::top() const //throw (const char *)
{
    if (numElements == 0 || numCapacity == 0)
        throw "Error: asking for top of empty stack.";
    if(!empty())
        return buffer[size() - 1];
}

template <class T>
void stack<T>::resize(int newCapacity)
{
    if (newCapacity == 0)
    {
        numCapacity = 0;
        numElements = 0;
        buffer = NULL;
    }

    if (newCapacity > 0)
    {
        T* newBuffer = new T[newCapacity];
        for (int i = 0; i < numElements; i++)
            newBuffer[i] = buffer[i];
        delete [] buffer;
        buffer = newBuffer;
        numCapacity = newCapacity;
        if (newCapacity < numElements)
            numElements = newCapacity;
    }
}