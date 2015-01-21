#ifndef LIST_H
#define LIST_H

#include <exception>
#include <utility>
#include <cassert>
#include "iterator.h"

class AlienIteratorException : std::exception
{
    const char *what() const noexcept override
    {
        return "Alien Iterator Exception!";
    }
};

class DifferentListException : std::exception
{
    const char *what() const noexcept override
    {
        return "Different List Exception! Finish and start belong to the different list!";
    }
};

class SelfIntersectionException : std::exception
{
    const char *what() const noexcept override
    {
        return "Self Intersection Exception!";
    }
};

template <typename T>
class List
{
public:
    List();
    List(const List<T> &other);
    List &operator=(const List<T> &rhs);
    List(List<T> &&victim);
    List &operator=(List<T> &&rhs);
    ~List() noexcept;

    friend class IteratorImpl<T>;
    typedef IteratorImpl<T> Iterator;

    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    void pushDatumToTheEnd(T datum);
    void pushDatumToTheBegin(T datum);
    void insertDatum(Iterator to, T datum);
    void insertList(Iterator to, List<T> &other);
    List<T> cutList(Iterator start, Iterator finish);
    bool isEmpty() const noexcept;
    //void sort(Iterator start, Iterator finish);

    void clear() noexcept;

private:
    struct Node
    {
        T data;
        Node *previous, *next;
        Node(T data);
    } *head, *tail;
    static void copy(const Node *node, Node *&head, Node *&tail);


};

template<typename T>
List<T>::List() :
    head(nullptr),
    tail(nullptr)
{

}

template<typename T>
List<T>::List(const List<T> &other):
    head(nullptr),
    tail(nullptr)
{
    copy(other.head, head, tail);
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &rhs)
{
    if (this != &rhs)
    {
        clear();
        copy(rhs.head, head, tail);
    }

    return *this;
}

template<typename T>
List<T>::List(List<T> &&victim):
    head(nullptr),
    tail(nullptr)
{
    std::swap(head, victim.head);
    std::swap(tail, victim.tail);
}

template<typename T>
List<T> &List<T>::operator=(List<T> &&rhs)
{
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
}

template<typename T>
List<T>::~List() noexcept
{
    clear();
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const noexcept
{
    return Iterator(this, head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const noexcept
{
    return Iterator(this, nullptr);
}

template<typename T>
void List<T>::pushDatumToTheEnd(T datum)
{
    Node *p = nullptr;
    p = new Node (datum);

    if (isEmpty())
    {
        head = p;
    }
    else
    {
        tail->next = p;
        p->previous = tail;
    }

    tail = p;
}

template<typename T>
void List<T>::pushDatumToTheBegin(T datum)
{
    Node *p = nullptr;
    p = new Node (datum);

    if (isEmpty())
    {
        tail = p;
    }
    else
    {
        head->next = p;
        p->previous = tail;
    }

    head = p;
}

template<typename T>
void List<T>::insertDatum(List<T>::Iterator to, T datum)
{
    if (to.owner != this)
    {
        throw AlienIteratorException();
    }

    if (to.current == nullptr)
    {
        pushDatumToTheEnd(datum);
    }
    else if (to.current->previous == nullptr)
    {
        pushDatumToTheBegin(datum);
    }
    else
    {
        Node *p = nullptr;
        p = new Node(datum);
        p->previous = to.current->previous;
        p->next = to.current;
        p->previous->next = p;
        to.current->previous = p;
    }
}

template<typename T>
void List<T>::insertList(List<T>::Iterator to, List<T> &other)
{
    if (to.owner != this)
    {
        throw AlienIteratorException();
    }

    if (this == &other)
    {
        throw SelfIntersectionException();
    }

    if (to.current == nullptr)
    {
        other.head->previous = tail;
        tail->next = other.head;
        tail = other.tail;
    }
    else if (to.current->previous == nullptr)
    {
        other.tail->next = head;
        head->previous = other.tail;
        head = other.head;
    }
    else
    {
        other.head->previous = to.current->previous;
        other.tail->next = to.current;
        other.head->previous->next = other.head;
        to.current->previous = other.tail;
    }

    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T>
List<T> List<T>::cutList(List<T>::Iterator start, List<T>::Iterator finish)
{
    if (start.owner != finish.owner
            || this != start.owner)
    {
        throw DifferentListException();
    }

    List<T> result;
    result.head = start.current;

    if (finish.current == nullptr)
    {
        result.tail = finish.owner->head;
        tail = result.head->previous;
    }
    else
    {
        result = finish.current->previous;
    }

    if (result.head->previous == nullptr)
    {
        head = result.tail->next;
    }

    if (result.tail->next)
    {
        result.tail->next->previous = result.head->previous;
    }

    if (result.head->previous)
    {
        result.head->previous->next = result.tail->next;
    }

    result.tail->next = nullptr;
    result.head->previous = nullptr;
    return result;
}

template<typename T>
bool List<T>::isEmpty() const noexcept
{
    return head == nullptr && tail == nullptr;
}

/*
template<typename T>
void List<T>::sort(List<T>::Iterator start, List<T>::Iterator finish)
{

}*/

template<typename T>
void List<T>::clear()noexcept
{
    while (head)
    {
        Node *p = head;
        head = head->next;
        delete p;
    }

    tail = nullptr;
}

template<typename T>
void List<T>::copy(const List<T>::Node *node,
                   Node *&head,
                   Node *&tail)
{
    assert(head == nullptr);
    assert(tail == nullptr);
    Node *p = nullptr;

    if (node)
    {
        head = new Node(node->data);
        p = head;
        node = node->next;
    }

    while (node)
    {
        Node *q = nullptr;
        q = new Node(node->data);
        p->next = q;
        q->previous = p;
        p = q;
        node = node->next;
    }

    tail = p;
}



template<typename T>
List<T>::Node::Node(T data) :
    data(data),
    previous(nullptr),
    next(nullptr)
{
}


#endif // LIST_H
