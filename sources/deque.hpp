#pragma once
#include <iostream>
#include <string>
#include "node.hpp"
using std::string;

namespace ex4
{
    class Deque
    {
    private:
        size_t size;
        Node<string> *head;
        Node<string> *tail;

    public:
        Deque();
        ~Deque();

        Node<string>* _getHead();
        Node<string>* _getTail();
        size_t _getSize();
        void _setHead(Node<string> *new_head);
        void _setTail(Node<string> *new_tail);
        void _setSize(size_t new_size);

        void _PUSH(string text);
        void _ENQUEUE(string text);
        string _POP();
        string _TOP();
        string _DEQUEUE();
        void _ToString();
    };
}