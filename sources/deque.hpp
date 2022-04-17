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
        Deque(const Deque &orig);
        ~Deque();

        Node<string>* _getHead() const;
        Node<string>* _getTail() const;
        size_t _getSize() const;
        void _setHead(Node<string> *new_head);
        void _setTail(Node<string> *new_tail);
        void _setSize(size_t new_size);

        void PUSH(string text);
        void ENQUEUE(string text);
        string POP();
        string TOP() const;
        string DEQUEUE();
        void _ToString() const;
        void _Clear();
    };
}