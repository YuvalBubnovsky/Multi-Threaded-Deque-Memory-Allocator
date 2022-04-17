#pragma once
#include <iostream>
#include "node.hpp"

namespace ex4
{
    class Deque
    {
    private:
        size_t size;
        Node<char*> *head;
        Node<char*> *tail;

        /*
        void _setHead(Node<string> *new_head);
        void _setTail(Node<string> *new_tail);
        void _setSize(size_t new_size);
        */

    public:
        Deque();
        ~Deque();

        Node<char*>* _getHead() const;
        Node<char*>* _getTail() const;
        size_t _getSize() const;
        

        void PUSH(char* text);
        void ENQUEUE(char* text);
        char* POP();
        char* TOP() const;
        char* DEQUEUE();
        void _ToString() const;
        void _Clear();
    };
}