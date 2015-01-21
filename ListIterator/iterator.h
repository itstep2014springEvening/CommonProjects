#ifndef ITERATOR_H
#define ITERATOR_H

#include "list.h"

template<typename T>
class List;

template <typename T>
class IteratorImpl final
{
public:
    IteratorImpl():owner(nullptr),current(nullptr){}
    IteratorImpl(const IteratorImpl<T> &other)=default;
    IteratorImpl &operator=(const IteratorImpl<T> &rhs)=default;
    IteratorImpl(IteratorImpl<T> &&victim)=default;
    IteratorImpl &operator=(IteratorImpl<T> &&rhs)=default;
    ~IteratorImpl()=default;

    friend List<T>;
    T &operator*() const;
    T *operator->() const;
    IteratorImpl operator++();
    IteratorImpl operator++(int);
    IteratorImpl operator--();
    IteratorImpl operator--(int);
    bool operator==(const IteratorImpl &other);
    bool operator!=(const IteratorImpl &other);
private:
    const List<T> *owner;
    typename List<T>::Node *current;

    IteratorImpl(const List<T> *owner,
             typename List<T>::Node *current) :
        owner(owner),
        current(current)
    {

    }
};

template<typename T>
T &IteratorImpl<T>::operator*() const
{

}

template<typename T>
T *IteratorImpl<T>::operator->() const
{

}

template<typename T>
IteratorImpl<T> IteratorImpl<T>::operator++()
{

}

template<typename T>
IteratorImpl<T> IteratorImpl<T>::operator++(int)
{

}

template<typename T>
IteratorImpl<T> IteratorImpl<T>::operator--()
{

}

template<typename T>
IteratorImpl<T> IteratorImpl<T>::operator--(int)
{

}

template<typename T>
bool IteratorImpl<T>::operator==(const IteratorImpl &other)
{

}

template<typename T>
bool IteratorImpl<T>::operator!=(const IteratorImpl &other)
{

}


#endif // IteratorImpl_H
