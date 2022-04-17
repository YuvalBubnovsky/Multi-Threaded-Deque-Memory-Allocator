#pragma once

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
        T _getValue();
        T *_getNext();
        T *_getPrev();
        void _setValue(T &new_val);
        void _setNext(T *new_next);
        void _setPrev(T *new_prev);
    };
}