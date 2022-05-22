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
Queue<T>::Queue(const Queue<T> &){

}



template <class T>
void Queue<T>::pushBack(const T &t) {
    Iterator temp = this->begin();
    for (int i = 0; i < this->size(); ++i) {
        temp++;
    }
    try{
        Queue<T> newNode = new Queue<T>;
        newNode.m_data = t;
        temp.opera
    }
    catch{

    }


}





#endif //EX3_QUEUE_H
