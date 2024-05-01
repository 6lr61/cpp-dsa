#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <optional>

template <typename T>
class LinkedList
{
    struct Node
    {
        Node(T v) : value(v){};
        ~Node() = default;
        T value;
        Node *next = nullptr;
    };

public:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    size_t length = 0;

    LinkedList() = default;

    ~LinkedList()
    {
        Node *next = this->head;
        Node *old = next;

        while (next != nullptr)
        {
            old = next;
            next = next->next;
            delete old;
        }
    };

    bool is_empty()
    {
        return head == nullptr;
    }

    void insert(T value)
    {
        Node *node = new Node(value);
        length++;

        if (is_empty())
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
    }

    void push(T value)
    {
        Node *node = new Node(value);

        if (is_empty())
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }

        length++;
    }

    std::optional<T> pop()
    {
        if (is_empty())
        {
            return std::nullopt;
        }

        if (head == tail)
        {
            T old_value = tail->value;
            delete tail;
            head = tail = nullptr;
            length--;

            return std::optional<T>{old_value};
        }

        Node *current = head;

        while (current->next != tail)
        {
            current = current->next;
        }

        T old_value = tail->value;
        delete tail;
        tail = current;
        tail->next = nullptr;
        length--;

        return std::optional<T>{old_value};
    }
};

#endif