#include "deque.h"

using namespace custom;

/* custom deque implementation 
 ******************************************************************************/

template <class T>
deque<T>::deque()
{
    iFront = 0;
    iBack = -1;
    numCapacity = 0;
    buffer = NULL;
}

template <class T>
deque<T>::deque(int numCapacity)
{
    if (numCapacity <= 0)
        throw "Error: deque sizes must be greater than or equal to 0.";
    else
    {
        iFront = 0;
        iBack = -1;
        this->numCapacity = numCapacity;

        buffer = new T[numCapacity];
    }
    
}

template <class T>
deque<T>::deque(const deque <T> & rhs)
{
    *this = rhs;
}

template <class T>
deque<T>::~deque()
{
    delete [] buffer;
}

template <class T>
deque<T> & deque<T>::operator = (const deque <T> & rhs)
{
    iFront = 0;
    iBack = -1;
    numCapacity = 0;
    buffer = NULL;

    resize(rhs.size());

    for (int i =  rhs.iFront; i <= rhs.iBack; i++)
        push_back(rhs.buffer[i % rhs.numCapacity]);

    return *this;
}

template <class T>
int deque<T>::size() const
{
    return iBack - iFront + 1;
}

template <class T>
bool deque<T>::empty() const
{
    return iFront == (iBack + 1);
}

template <class T>
void deque<T>::clear()
{
    iFront = 0;
    iBack = -1;
}

template <class T>
void deque<T>::push_front(const T & t)
{
    if (size() == capacity())
        resize((numCapacity == 0) ? 1 : numCapacity * 2);

    iFront--;
    buffer[iFrontNormalize()] = t;
}

template <class T>
void deque<T>::push_back(const T & t)
{
    if (size() == capacity())
        resize((numCapacity == 0) ? 1 : numCapacity * 2);

    iBack++;
    buffer[iBackNormalize()] = t;
}

template <class T>
void deque<T>::pop_front()
{
    if (empty())
        throw "Error: Can not pop an empty deque.";
    if (!empty())
        iFront++;
}

template <class T>
void deque<T>::pop_back()
{
    if (empty())
        throw "Error: Can not pop an empty deque.";
    if (!empty())
        iBack--;
}

template <class T>
T & deque<T>::front()
{
    if (empty())
        throw "Error: deque is empty.";
    else
        return buffer[iFrontNormalize()];
}

template <class T>
T & deque<T>::back()
{
    if (empty())
        throw "Error: deque is empty.";
    else
        return buffer[iBackNormalize()];
}

template <class T>
void deque<T>::resize(int newCapacity)
{
    //FINISH
    if (newCapacity <= 0)
    {
        iFront = 0;
        iBack = -1;
        numCapacity = 0;
        buffer = NULL;
    }
    if (newCapacity > 0)
    {
        T* newBuffer = new T[newCapacity];
        int numElements = (newCapacity < size()) ? newCapacity : size();
        for (int i = 0; i < numElements; i++, iFront ++)
            newBuffer[i] = buffer[iFrontNormalize()];
        delete [] buffer;
        buffer = newBuffer;
        numCapacity = newCapacity;

        iBack = size() - 1;
        iFront = 0;
        iBack = numElements - 1;
    }
}

template <class T>
int deque<T>::capacity()
{
    return numCapacity;
}

template <class T>
int deque<T>::iFrontNormalize()
{
    return iNormalize(iFront);
}

template <class T>
int deque<T>::iBackNormalize()
{
    return iNormalize(iBack);
}

template <class T>
int deque<T>::iNormalize(int normalize)
{
    if (numCapacity == 0)
        throw "Error: uninitialized deque.";

    return (normalize % numCapacity + numCapacity) % numCapacity;
}