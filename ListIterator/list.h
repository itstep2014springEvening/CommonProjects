#ifndef LIST_H
#define LIST_H

#include <exception>
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
    List(); //Конструктор
    List(const List<T> &other); //Конструктор копирования
    List &operator=(const List<T> &rhs);  //Оператор присваивания
    List(List<T> &&victim); //Конструктор перемещения
    List &operator=(List<T> &&rhs); //Оператор переместительного присваивания
    ~List() noexcept; //Деструктор

    friend class Iterator<T>;
    typedef Iterator<T> Iterator;

    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    void pushDatumToTheEnd(T datum);
    void pushDatumToTheBegin(T datum);
    void insertDatum(Iterator to, T datum);
    void insertList(Iterator to, List<T> &other);
    List<T> cutList(Iterator start, Iterator finish);
    bool isEmpty() const noexcept;
    void sort(Iterator start, Iterator finish);

    void clear() noexcept;

private:
    struct Node
    {
        T data;
        Node *previous, *next;
        Node(T data);
    } *head, *tail;
    static Node *copy(const Node *node);


};

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr)
{

}

template<typename T>
List<T>::List(const List<T> &other)
{

}

template<typename T>
List &List<T>::operator=(const List<T> &rhs)
{

}

template<typename T>
List<T>::List(List<T> &&victim)
{

}

template<typename T>
List &List<T>::operator=(List<T> &&rhs)
{

}

template<typename T>
List<T>::~List() noexcept
{
    clear();
}

template<typename T>
List<T>::Iterator List<T>::begin() const
{

}

template<typename T>
List<T>::Iterator List<T>::end() const
{

}

template<typename T>
void List<T>::pushDatumToTheEnd(T datum)
{
    Node *p=nullptr;
    p = new Node (datum);
    if(isEmty())
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
    if(isEmty())
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
    if(to.owner != this)
    {
        throw AlienIteratorException;
    }
    if(to.current == nullptr)
    {
        pushDatumToTheEnd(data);
    }
    else if(to.current->previous == nullptr)
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
    if(to.owner != this)
    {
        throw AlienIteratorException;
    }
    if(this == &other)
    {
        throw SelfIntersectionException;
    }
    if(to.current == nullptr)
    {
        other.head->previous = tail;
        tail->next = other.head;
        tail = other.tail;
    }
    else if(to.current->previous == nullptr)
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
    if(otherList.owner!=finish.owner)
    {
        throw DifferentListException;
    }
    List<T> result;
    result.head = start.current;
    if(finish.current == nullptr)
    {
        result.tail = finish.owner->head;
        tail = result.head->previous;
    }
    else
    {
        result = finish.current->previous;
    }
    if(result.head->previous == nullptr)
    {
        head = result.tail->next;
    }
    if(result.tail->next)
    {
        result.tail->next->previous = result.head->previous;
    }
    if(result.head->previous)
    {
        result.head->previous->next = result.tail->next;
    }
    result.tail->next = nullptr;
    result.head->previous = nullptr;
    return result;
}

template<typename T>
bool List<T>::isEmpty() const
{

}

template<typename T>
void List<T>::sort(List<T>::Iterator start, List<T>::Iterator finish)
{

}

template<typename T>
void List<T>::clear()
{

}

template<typename T>
typename List<T>::Node *List<T>::copy(const List<T>::Node *node)
{

}



template<typename T>
List<T>::Node<T>::Node(T data) :
    data(data),
    previous(nullptr),
    next(nullptr)
{

}


#endif // LIST_H
