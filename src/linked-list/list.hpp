#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <optional>

template <typename T>
class LinkedList
{
    struct Node
    {
        Node(T v) : value(v)
        {
            std::cout << "Node, constructing: " << value << '\n';
        };
        ~Node()
        {
            std::cout << "Node, destructing: " << value << '\n';
        }
        T value;
        Node *next = nullptr;
    };

public:
    Node *head = nullptr;

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
            head = node;
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
        Node *last = head;

        if (is_empty())
        {
            head = node;
        }
        else
        {
            while (last->next != nullptr)
            {
                last = last->next;
            }

            last->next = node;
        }

        length++;
    }

    std::optional<T> pop()
    {
        if (is_empty())
        {
            return std::nullopt;
        }

        if (length == 1)
        {
            T last_value = head->value;
            delete head;
            head = nullptr;
            length--;

            return std::optional<T>{last_value};
        }

        Node *last = head;
        Node *second_last = last;

        while (last->next != nullptr)
        {
            second_last = last;
            last = last->next;
        }

        T old_value = last->value;
        delete last;
        second_last->next = nullptr;
        length--;

        return std::optional<T>{old_value};
    }
};

#endif