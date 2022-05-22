//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

template <class T>
class Queue{
    T m_data;
    Queue* m_next;
public:
    Queue();
    Queue(const Queue<T>&);
    Queue& operator=(const Queue<T>&);
    ~Queue();
    void pushBack(const T& t);
    const T& front() const;
    void popFront();
    int size() const;
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    class EmptyQueue{};
};

template<class T>
class Queue<T>::Iterator{
    const Queue<T>* queue;
    int index;
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    class InvalidOperation{};
};

template <class T, class Condition>
Queue<T> filter(const Queue<T>& t, Condition c);

template <class T, class Transformer>
void transform(Queue<T>(), Transformer t);


/*implementation*/

template <class T>
Queue<T>::Queue() {
    this->m_next = nullptr;
    this->m_data = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue<T> &t){
    try{
        this->m_data = t.m_data;
        if(t.size() == 1)
        {
            this->m_next = nullptr;
            return;
        }
        Queue<T> newNode = new Queue<T>();
        this->m_next = &newNode;
        Queue<T> tempSource = t.m_next, tempAdded = this->m_next;
        for (int i = 0; i < this->size()-1 && tempSource != nullptr; ++i) {
            tempAdded.m_data = tempSource.m_data;
            if(tempSource.m_next == nullptr)
            {
                tempAdded.m_next = nullptr;
                return;
            }
            newNode = new Queue<T>();
            tempAdded.m_next = &newNode;
            tempAdded = tempAdded.m_next;
            tempSource = tempSource.m_next;
        }
    }
    catch(){

    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& t) {
    if(this == &t){
        return *this;
    }
    if(this->size() >= t.size())
    {
        Queue<T> tempThis = this, tempSource=t;
        for (int i = 0; i < t->size(); ++i) {
            tempThis.m_data = tempSource.m_data;
            tempSource = tempSource.m_next;
            tempThis = tempThis.m_next;
        }
        delete tempThis;
        return *this;
    }
    if(this->size() < t.size())
    {
        Queue<T> tempThis = this, tempSource=t;
        for (int i = 0; i < this->size(); ++i) {
            tempThis.m_data = tempSource.m_data;
            tempSource = tempSource.m_next;
            if(tempThis.m_next != nullptr){
                tempThis = tempThis.m_next;
            }
        }
        Queue<T> newNode(tempSource);
        tempThis.m_next = &newNode;
    }
}

template <class T>
Queue<T>::~Queue<T>() {
    delete this->m_data;
    if(this->m_next != nullptr)
    {
        delete *this->m_next;
    }
}

template <class T>
void Queue<T>::pushBack(const T& t)
{
    Queue<T> tmp = this;
    Queue<T> newNode = new Queue<T>;
    while (tmp.m_next != nullptr)
    {
        tmp = tmp.m_next;
    }
    tmp.m_next = &newNode;
    newNode.m_data = t;
    newNode.m_next = nullptr;
}

template <class T>
const T& Queue<T>::front() const
{
    return this->m_data;
}

template <class T>
void Queue<T>::popFront()
{
    if(this->size()==0)
    {
        return;
    }
    Queue<T> tmp = this->m_next;
    this->m_data = tmp.m_data;
    this->m_next = tmp.m_next;
    tmp.m_next = nullptr;
    delete tmp;
}

template <class T>
int Queue<T>::size() const
{
    int counter = 0;
    Queue<T> tmp = this;
    if(tmp.m_data!= nullptr)
    {
        counter++;
    }
    while (tmp.m_next != nullptr)
    {
        tmp = tmp.m_next;
        counter++;
    }
    return counter;
}





#endif //EX3_QUEUE_H
