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

    class Iterator
    {
    protected:
        Node *node;

    public:
        Iterator(Node *n) : node(n){};
        ~Iterator() = default;

        Iterator &operator++()
        {
            if (node)
            {
                node = node->next;
            }

            return *this;
        }

        bool operator!=(const Iterator &iterator)
        {
            return node != iterator.node;
        }

        T &operator*()
        {
            return node->value;
        }
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

    Iterator begin()
    {
        return Iterator{head};
    }

    Iterator end()
    {
        return Iterator{nullptr};
    }

    // Indexes past the end of the list are ignored,
    // and new values are inserted at the end
    void insert(T value, size_t index = 0)
    {
        Node *node = new Node(value);

        // Insert into empty list
        if (is_empty())
        {
            head = tail = node;
            length++;

            return;
        }

        // Insert at the begining
        if (index == 0)
        {
            node->next = head;
            head = node;
            length++;

            return;
        }

        // Insert at the end
        if (index >= length)
        {
            tail->next = node;
            tail = node;
            length++;

            return;
        }

        Node *current = head;
        Node *previous = head;

        // Find the node at index - 1
        for (size_t i = 0; i < index; i++)
        {
            previous = current;
            current = current->next;
        }

        auto next = previous->next;
        previous->next = node;
        node->next = next;

        length++;
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

    std::optional<T> shift()
    {
        if (is_empty())
        {
            return std::nullopt;
        }

        if (head == tail)
        {
            return pop();
        }

        Node *next = head->next;
        T old_value = head->value;
        delete head;
        head = next;
        length--;

        return std::optional<T>{old_value};
    }

    void reverse()
    {
        Node *previous = nullptr;
        Node *current = head;
        tail = head;
        Node *next;

        while (current)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }
};

#endif
