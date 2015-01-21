#ifndef ITERATOR_H
#define ITERATOR_H

#include "list.h"

template <typename T>
class Iterator final
{
public:
    Iterator(); //Конструктор
    Iterator(const Iterator<T> &other); //Конструктор копирования
    Iterator &operator=(const Iterator<T> &rhs);  //Оператор присваивания
    Iterator(Iterator<T> &&victim); //Конструктор перемещения
    Iterator &operator=(Iterator<T> &&rhs); //Оператор переместительного присваивания
    ~Iterator(); //Деструктор

    friend class List<T>;
    T &operator*() const;
    T *operator->() const;
    Iterator operator++();
    Iterator operator++(int);
    bool operator==(const Iterator &other);
    bool operator!=(const Iterator &other);
private:
    const List<T> *owner;
    List<T>::Node<T> *current;
    Iterator(const List<T> *owner, List<T>::Node<T> *current) :
        owner(owner),
        current(current)
    {

    }
};

#endif // ITERATOR_H
//shared_ptr умный указатель, библиотека memory
