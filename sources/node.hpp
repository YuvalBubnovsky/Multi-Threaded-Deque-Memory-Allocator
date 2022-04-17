#pragma once
#include <iostream>

namespace ex4
{
    template <class T>
    class Node
    {
    private:
        Node<T> *prev;
        Node<T> *next;
        T value;

    public:
        Node(T &value);
        ~Node();

        T _getValue() const;
        Node<T> *_getNext() const;
        Node<T> *_getPrev() const;
        void _setValue(T &new_val);
        void _setNext(Node<T> *new_next);
        void _setPrev(Node<T> *new_prev);
    };
}