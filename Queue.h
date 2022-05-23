//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

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
    Queue<T> *newNode = (new Queue<T>);//changed syntax (*)
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
    //Queue<T> tmp = *this->m_next;
    this->m_data = this->m_next->m_data;
    this->m_next = this->m_next->m_next;
    this->m_length--;
    delete this->m_next;
}

template <class T>
int Queue<T>::size() const
{
    return this->m_length;
    /*
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
     */
}





#endif //EX3_QUEUE_H
