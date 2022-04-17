#include "node.hpp"

namespace ex4
{
    template <class T>
    Node<T>::Node(T &value)
    {
        this->next = NULL;
        this->prev = NULL;
        this->value = value;
        /* 
         * behind the scenes malloc - https://stackoverflow.com/questions/18312658/how-do-strings-allocate-memory-in-c
         */
    }

    template <class T>
    Node<T>::~Node()
    {
        
    }

    template <class T>
    T *Node<T>::_getNext() const
    {
        return this->next;
    }

    template <class T>
    T *Node<T>::_getPrev() const
    {
        return this->prev;
    }

    template <class T>
    T Node<T>::_getValue() const
    {
        return this->value;
    }

    template <class T>
    void Node<T>::_setValue(T &new_val)
    {
        this->value = new_val;
    }
    template <class T>
    void Node<T>::_setNext(T *new_next)
    {
        this->next = new_next;
    }
    template <class T>
    void Node<T>::_setPrev(T *new_prev)
    {
        this->prev = new_prev;
    }
}