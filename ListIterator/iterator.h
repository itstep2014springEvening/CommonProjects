#ifndef ITERATOR_H
#define ITERATOR_H

#include "list.h"

template <typename T>
class Iterator final
{
public:
    Iterator(); //ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ
    Iterator(const Iterator<T> &other); //ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ ÐºÐ¾Ð¿Ð¸ÑÐ¾Ð²Ð°Ð½Ð¸Ñ
    Iterator &operator=(const Iterator<T> &rhs);  //ÐÐ¿ÐµÑÐ°ÑÐ¾Ñ Ð¿ÑÐ¸ÑÐ²Ð°Ð¸Ð²Ð°Ð½Ð¸Ñ
    Iterator(Iterator<T> &&victim); //ÐÐ¾Ð½ÑÑÑÑÐºÑÐ¾Ñ Ð¿ÐµÑÐµÐ¼ÐµÑÐµÐ½Ð¸Ñ
    Iterator &operator=(Iterator<T> &&rhs); //ÐÐ¿ÐµÑÐ°ÑÐ¾Ñ Ð¿ÐµÑÐµÐ¼ÐµÑÑÐ¸ÑÐµÐ»ÑÐ½Ð¾Ð³Ð¾ Ð¿ÑÐ¸ÑÐ²Ð°Ð¸Ð²Ð°Ð½Ð¸Ñ
    ~Iterator(); //ÐÐµÑÑÑÑÐºÑÐ¾Ñ

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
//shared_ptr ÑÐ¼Ð½ÑÐ¹ ÑÐºÐ°Ð·Ð°ÑÐµÐ»Ñ, Ð±Ð¸Ð±Ð»Ð¸Ð¾ÑÐµÐºÐ° memory
