#pragma once
#include <iostream>

namespace ex4
{
    template <class T>
    class Node
    {
    private:
        T *prev;
        T *next;
        T value;

    public:
        Node(T &value);
        ~Node();

        T _getValue() const;
        T *_getNext() const;
        T *_getPrev() const;
        void _setValue(T &new_val);
        void _setNext(T *new_next);
        void _setPrev(T *new_prev);
    };
}