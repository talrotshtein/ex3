//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <iostream>

template <class T>
class Queue{
    T m_data;
    Queue<T>* m_next;
    int m_length;
public:
    Queue();
    Queue(const Queue<T>&);
    Queue& operator=(const Queue<T>&);
    ~Queue();
    void pushBack(const T& t);
    T& front();
    const T& front() const;
    void popFront();
    int size() const;
    class Iterator;
    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
    class EmptyQueue{};
};

template<class T>
class Queue<T>::ConstIterator{
    const Queue<T>* queue;
    int index;
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    const T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator!=(const ConstIterator& constIterator) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    class InvalidOperation{};
};

template<class T>
class Queue<T>::Iterator{
    Queue<T>* queue;
    int index;
    Iterator(Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    T& operator*();
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator);
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    class InvalidOperation{};
};

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition c);

template <class T, class Transformer>
void transform(Queue<T>& queue, Transformer t);


/*implementation*/

template <class T>
Queue<T>::Queue()
{
    this->m_next = nullptr;
    this->m_length = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T> &t)
{

    this->m_next=nullptr;
    this->m_length = 0;
    *this =t;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& t)
{
    if(this == &t){
        return *this;
    }
    Queue<T> newQueue;
    for (typename Queue<T>::ConstIterator i = t.begin(); i != t.end(); ++i) {
        newQueue.pushBack(*i);
    }
    while (this->m_next != nullptr)
    {
        this->popFront();
    }
    this->m_data = newQueue.m_data;
    this->m_next = newQueue.m_next;
    this->m_length = newQueue.m_length;
    newQueue.m_next = nullptr;
    return *this;
}

template <class T>
Queue<T>::~Queue<T>()
{
    delete this->m_next;
    this->m_next = nullptr;
}


template <class T>
void Queue<T>::pushBack(const T& t)
{
    if(this->m_length == 0)
    {
        this->m_data = t;
        this->m_length++;
        return;
    }
    Queue<T>* temp = this;
    Queue<T>* newNode=  new Queue;
    while (temp->m_next != nullptr)
    {
        temp = temp->m_next;
    }
    try
    {
        newNode->m_data = t;
    }
    catch(std::bad_alloc e){
        delete newNode;
        throw e;
    };
    temp->m_next = newNode;
    this->m_length++;

}

template <class T>
T& Queue<T>::front()
{
    if(this->m_length==0)
    {
        throw EmptyQueue();
    }
    return this->m_data;
}

template <class T>
const T& Queue<T>::front() const
{
    if(this->m_length==0)
    {
        throw EmptyQueue();
    }
    return this->m_data;
}

template <class T>
void Queue<T>::popFront()
{
    if(this->m_length==0)
    {
        throw EmptyQueue();
    }
    if(this->m_length==1)
    {
        this->m_length = 0;
        this->m_next = nullptr;
        return;
    }
    m_length--;
    this->m_data = this->m_next->m_data;
    Queue<T>* temp = this->m_next;
    this->m_next=this->m_next->m_next;
    temp->m_next= nullptr;
    delete temp;
}

template <class T>
int Queue<T>::size() const
{
    return this->m_length;
}

template<class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition c)
{
    Queue<T> newQueue;
    if(queue.size() == 0)
    {
        return newQueue;
    }
    for (typename Queue<T>::ConstIterator i = queue.begin(); i != queue.end(); ++i) {
        if(c(*i) == true)
        {
            try {
                newQueue.pushBack(*i);
            }
            catch (std::bad_alloc& e){
                while (newQueue.size()>0){
                    newQueue.popFront();
                }
                throw e;
            }
        }
    }
    return newQueue;
}

template<class T, class Transformer>
void transform(Queue<T>& queue, Transformer t)
{
    if(queue.size() == 0)
    {
        return;
    }
    for (typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        t(*i);
    }
}


/*ConstIterator implementation*/

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *queue, int index)
{
    this->index = index;
    this->queue = queue;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if(this->index >= this->queue->size())
    {
        throw InvalidOperation();
    }
    const Queue<T>* temp = this->queue;
    for (int i = 0; i < index; ++i) {
        temp = temp->m_next;
    }
    return temp->m_data;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(this->index == this->queue->size())
    {
        throw InvalidOperation();
    }
    this->index++;
    return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    if(this->index == this->queue->size())
    {
        throw InvalidOperation();
    }
    ConstIterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator) const
{
    return this->index != constIterator.index;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, 0);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, this->size());
}

/*Iterator implementation*/

template <class T>
Queue<T>::Iterator::Iterator(Queue<T> *queue, int index)
{
    this->index = index;
    this->queue = queue;
}

template<class T>
 T& Queue<T>::Iterator::operator*()
{
    if(this->index == this->queue->size())
    {
        throw InvalidOperation();
    }
    assert(this->index >= 0 && this->index < this->queue->size());
    Queue<T>* temp = this->queue;
    for (int i = 0; i < index; ++i) {
        temp = temp->m_next;
    }
    return temp->m_data;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(this->index == this->queue->size())
    {
        throw InvalidOperation();
    }
    this->index++;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    if(this->index == this->queue->size())
    {
        throw InvalidOperation();
    }
    Iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)
{
    return this->index != iterator.index;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, 0);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, this->size());
}

#endif //EX3_QUEUE_H
