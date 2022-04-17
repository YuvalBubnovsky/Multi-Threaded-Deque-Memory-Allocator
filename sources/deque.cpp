#include "deque.hpp"
using namespace ex4;

namespace ex4
{
    Deque::Deque()
    {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }
    Deque::~Deque()
    {
    }

    Node<char *> *Deque::_getHead() const
    {
        return this->head;
    }
    Node<char *> *Deque::_getTail() const
    {
        return this->tail;
    }
    size_t Deque::_getSize() const
    {
        return this->size;
    }
    
    /*
    void Deque::_setHead(Node<string> *new_head){
        this->head = new_head;
    }
    void Deque::_setTail(Node<string> *new_tail){
        this->tail = new_tail;
    }
    void Deque::_setSize(size_t new_size){
        this->size = new_size;
    }*/

    void Deque::PUSH(char *text)
    {
        /**
         * @brief inserts the value as the head
         *
         */

        Node<char *> *node = new Node<char *>(text); // 'new' is a memory allocation!
        if (this->size == 0)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->_setNext(this->head);
            this->head->_setPrev(node);
            this->head = node;
        }
        this->size += 1;
    }
    void Deque::ENQUEUE(char *text)
    {
        /**
         * @brief inserts the value as the tail
         *
         */

        Node<char *> *node = new Node<char *>(text); // 'new' is a memory allocation!
        if (this->size == 0)
        {
            this->head = node;
            this->tail = node;
        }
        else
        {
            node->_setPrev(this->tail);
            this->tail->_setNext(node);
            this->tail = node;
        }
        this->size += 1;
    }
    char *Deque::POP()
    {
        if (this->size == 0)
        {
            std::cout << "ERROR: "
                      << "Empty stack" << std::endl;
            return "ERROR: Empty stack\n";
        }
        Node<char *> *node = this->head;
        Node<char *> *new_head = this->head->_getNext();
        new_head->_setPrev(NULL);
        this->head = new_head;
        return node->_getValue();
    }

    char *Deque::DEQUEUE()
    {
        Node<char *> *node = this->tail;
        Node<char *> *new_tail = this->tail->_getPrev();
        new_tail->_setNext(NULL);
        this->tail = new_tail;
        return node->_getValue();
    }
    char *Deque::TOP() const
    {
        if (this->size == 0)
        {
            std::cout << "ERROR: "
                      << "Empty stack" << std::endl;
            return "ERROR: Empty stack\n";
        }
        std::cout << "OUTPUT: " << this->head->_getValue() << std::endl;
        return this->head->_getValue();
    }

    void Deque::_ToString() const
    {
        // TODO: for debugging
    }
    void Deque::_Clear()
    {
        // TODO: for debugging
    }
}