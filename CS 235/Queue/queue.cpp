#include "queue.h"

using namespace custom;

/* custom queue implementation 
 ******************************************************************************/

template <class T>
queue<T>::queue()
{
    numCapacity = 0;
    numPush = 0;
    numPop = 0;
    buffer = NULL;
}

template <class T>
queue<T>::queue(int numCapacity)
{
    if (numCapacity <= 0)
    {
        this->numCapacity = 0;
        numPush = 0;
        numPop = 0;
        buffer = NULL;
    }

    this->numCapacity = numCapacity;
    numPush = 0;
    numPop = 0;

    buffer = new T[numCapacity];
}

template <class T>
queue<T>::queue(const queue <T> & rhs)
{
    *this = rhs;
}

template <class T>
queue<T>::~queue()
{
    delete [] buffer;
}

template <class T>
queue<T> & queue<T>::operator = (const queue <T> & rhs)
{
    numCapacity = rhs.numPush - rhs.numPop;
    numPush = rhs.numPush - rhs.numPop;
    numPop = 0;
    buffer = new T[rhs.numPush - rhs.numPop];
    for (int i = 0; i < rhs.numPush - rhs.numPop; i++)
        buffer[i] = rhs.buffer[rhs.numPop + i];
    return *this;
}

template <class T>
int queue<T>::size() const
{
     if (numCapacity == 0)
        return 0;
    
    return numPush - numPop;
}

template <class T>
int queue<T>::capacity() const
{
    return numCapacity;
}

template <class T>
bool queue<T>::empty() const
{
    if (numCapacity == 0)
        return true;

    return numPush == numPop;
}

template <class T>
void queue<T>::clear()
{
    numPush = numPop;
}

template <class T>
void queue<T>::push(const T & t)
{
    if (size() == capacity())
        resize((numCapacity == 0) ? 1 : numCapacity * 2);

    numPush++;
    buffer[iTail()] = t;
}

template <class T>
void queue<T>::pop()
{
    if (!empty())
        numPop++;
    
}

template <class T>
T & queue<T>::front()
{
    if (empty())
        throw "Error: asking for front of empty queue.";
    else
        return buffer[iHead()];
}

template <class T>
T & queue<T>::front() const
{
    if (empty())
        throw "Error: asking for front of empty queue.";
    else
        return buffer[iHead()];
}

template <class T>
T & queue<T>::back()
{
    if (empty())
        throw "Error: asking for back of empty queue.";
    else
        return buffer[iTail()];
}

template <class T>
T & queue<T>::back() const
{
    if (empty())
        throw "Error: asking for back of empty queue.";
    else
        return buffer[iTail()];
}

template <class T>
void queue<T>::resize(int newCapacity)
{
    if (newCapacity <= 0)
    {
        numCapacity = 0;
        numPush = 0;
        numPop = 0;
        buffer = NULL;
    }

    if (newCapacity > 0)
    {
        T* newBuffer = new T[newCapacity];
        int numElements = (newCapacity < size()) ? newCapacity : size();
        for (int i = 0; i < numElements; i++, numPop++)
        {
            newBuffer[i] = buffer[iHead()];
        }
        
        delete [] buffer;
        buffer = newBuffer;
        numCapacity = newCapacity;

        numPush = numElements;
        numPop = 0;
    }

}

template <class T>
int queue<T>::iHead()
{
    return numPop % numCapacity;    
}

template <class T>
int queue<T>::iTail()
{
    return (numPush - 1) % numCapacity;
}