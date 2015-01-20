#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
public:
    List(); //Конструктор
    List(const List<T> &other); //Конструктор копирования
    List &operator=(const List<T> &rhs);  //Оператор присваивания
    List(List<T> &&victim); //Конструктор перемещения
    List &operator=(List<T> &&rhs); //Оператор переместительного присваивания
    ~List(); //Деструктор

    friend class Iterator<T>;
    typedef Iterator<T> Iterator;

private:
    struct Node
    {
        T data;
        Node *previous, *next;
    } *head, *tail;
    static Node *copy(const Node *node);
    static void output(Node *node);
};

#endif // LIST_H
