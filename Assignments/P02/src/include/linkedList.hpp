#include <iostream>
#include "counters.hpp"

class LinkedList {
private:
    struct Node {
        int data;
        Node *next;

        Node(int v) : data(v), next(nullptr) {}
    };

    mutable Counters c;
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node *curr = head;

        while (curr) {

            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    bool insert(int value) {

        c.inserts++;

        c.comparisons++;
        if (contains(value))
            return false;

        c.structural_ops++;
        Node *n = new Node(value);

        n->next = head;
        head = n;

        return true;
    }

    bool contains(int value) const {
        Node *curr = head;
        c.lookups++;

        while (curr) {
            c.comparisons++; // comparison for while loop

            c.comparisons++;
            if (curr->data == value)
                return true;

            curr = curr->next;
        }

        return false;
    }

    bool erase(int value) {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            c.comparisons++; // comparison for while loop

            c.comparisons++;
            if (curr->data == value) {

                c.comparisons++;
                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                c.structural_ops++;
                delete curr;
                return true;
            }

            c.deletes++;
            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    void print() const {
        Node *curr = head;

        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }

        std::cout << "\n";
    }

    const char *name() const {
        return "LinkedList";
    }

    Counters get_counters() const {
        return c;
    }
};