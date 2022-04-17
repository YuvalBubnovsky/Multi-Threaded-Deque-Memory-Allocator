#include "node.hpp"

namespace ex4
{

    template <class T>
    T *Node<T>::_getNext()
    {
        return this->next;
    }

    template <class T>
    T *Node<T>::_getPrev()
    {
        return this->prev;
    }

    template <class T>
    T Node<T>::_getValue()
    {
        return this->value;
    }

    template <class T>
    void Node<T>::_setValue(T &new_val){
        this->value = new_val;
    }
    template <class T>
    void Node<T>::_setNext(T *new_next){
        this->next = new_next;
    }
    template <class T>
    void Node<T>::_setPrev(T *new_prev){
        this->prev = new_prev;
    }
}