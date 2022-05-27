//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <cassert>

template <class T>
class Queue{
    T m_data;
    Queue* m_next;
    int m_length;
public:
    Queue();
    Queue(const Queue<T>&);
    Queue& operator=(const Queue<T>&);
    ~Queue();
    void pushBack(const T& t);
    T& front();
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
void transform(Queue<T> queue, Transformer t);


/*implementation*/

template <class T>
Queue<T>::Queue() {
    this->m_next = nullptr;
    this->m_length = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T> &t){
        this->m_data = t.m_data;
        this->m_length = t.m_length;
        if(t.size() == 1 || t.size() == 0)
        {
            this->m_next = nullptr;
            return;
        }
        Queue<T>* newNode = new Queue<T>();
        this->m_next = newNode;
        Queue<T> *tempSource = t.m_next;//changed syntax
        Queue<T> *tempAdded = this->m_next;
        for (int i = 0; i < this->size()-1; ++i) {
            tempAdded->m_data = tempSource->m_data;
            if(tempSource->m_next == nullptr)
            {
                tempAdded->m_next = nullptr;
                return;
            }
            newNode = new Queue<T>();
            tempAdded->m_next = newNode;
            tempAdded = tempAdded->m_next;
            tempSource = tempSource->m_next;
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& t) {
    if(this == &t){
        return *this;
    }
    if(this->size() >= t.size())
    {
        this->m_length = t.m_length;
        Queue<T>* tempThis = this, tempSource=t;
        for (int i = 0; i < t.size(); ++i) {
            tempThis->m_data = tempSource.m_data;
            tempSource = *tempSource.m_next;
            if(i != t.size()-1){
                tempThis = *tempThis->m_next;
            }
        }
        //Queue<T> toDelete = *tempThis.m_next;
        while (tempThis->m_next != nullptr)
        {
            tempThis->m_next->popFront();
        }
        delete tempThis->m_next;
        return *this;
    }
    if(this->size() < t.size())
    {
        Queue<T> tempThis = *this, tempSource=t;
        for (int i = 0; i < this->size(); ++i) {
            tempThis.m_data = tempSource.m_data;
            tempSource = *tempSource.m_next;
            if(tempThis.m_next != nullptr){
                tempThis = *tempThis.m_next;
            }
        }
        Queue<T> newNode(tempSource);
        tempThis.m_next = &newNode;
    }
    return *this;
}

template <class T>
Queue<T>::~Queue<T>() {
    if(this->m_next != nullptr)
    {
        delete this->m_next;
    }
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
    Queue<T> *newNode = new Queue<T>;
    while (temp->m_next != nullptr)
    {
        temp = temp->m_next;
    }
    temp->m_next = newNode;
    newNode->m_data = t;
    newNode->m_next = nullptr;
    this->m_length++;
}

template <class T>
T& Queue<T>::front()
{
    if(this->m_length==0)
    {
        //throw
    }
    return this->m_data;
}

template <class T>
void Queue<T>::popFront()
{
    if(this->m_length==0)
    {
        return;//add throw
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
    Queue<T>* newQueue = new Queue<T>;
    for (typename Queue<T>::ConstIterator i = queue.begin(); i != queue.end(); ++i) {
        if(c(*i) == true)
        {
            newQueue->pushBack(*i);
        }
    }
    return *newQueue;
}

template<class T, class Transformer>
void transform(Queue<T> queue, Transformer t){
    for (typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        t(*i);
    }
}


/*ConstIterator implementation*/

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *queue, int index) {
    this->index = index;
    this->queue = queue;
}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
    assert(this->index >= 0 && this->index < this->queue->size());
    const Queue<T>* temp = this->queue;
    for (int i = 0; i < index; ++i) {
        temp = temp->m_next;
    }
    return temp->m_data;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
    this->index++;
    return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
    ConstIterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator) const {
    //assert(this->queue == constIterator.queue);
    return this->index != constIterator.index;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(this, 0);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
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
    assert(this->index >= 0 && this->index < this->queue->size());
    Queue<T>* temp = this->queue;
    for (int i = 0; i < index; ++i) {
        temp = temp->m_next;
    }
    return temp->m_data;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    this->index++;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
    Iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) {
    assert(this->queue == iterator.queue);
    return this->index == iterator.index;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(this, 0);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(this, this->size());
}

#endif //EX3_QUEUE_H
