#pragma once

#include "bst.hpp"
#include "counters.hpp"
#include <algorithm>

class Avl : public Bst {
private:
    mutable Counters c;

    int height(Node *node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(Node *node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node *node) {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node *rotateRight(Node *y) {

        c.structural_ops++;

        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x) {

        c.structural_ops++;

        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *rebalance(Node *node) {

        c.structural_ops++;

        updateHeight(node);

        int bf = balanceFactor(node);

        // Left heavy
        c.comparisons++;
        if (bf > 1) {

            c.comparisons++;
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left); // LR case
            }
            return rotateRight(node); // LL case
        }

        // Right heavy

        c.comparisons++;
        if (bf < -1) {

            c.comparisons++;
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right); // RL case
            }
            return rotateLeft(node); // RR case
        }

        return node;
    }

    Node *insert(Node *node, int value, bool &inserted) {

        c.comparisons++;
        if (!node) {
            inserted = true;
            return new Node(value);
        }

        c.comparisons++;
        if (value < node->data) {
            node->left = insert(node->left, value, inserted);
        } 

        else if (value > node->data) {
            node->right = insert(node->right, value, inserted);
        } else {
            inserted = false; // duplicate
            return node;
        }

        return rebalance(node);
    }

    Node *erase(Node *node, int value, bool &erased) {

        c.comparisons++;
        if (!node) {
            erased = false;
            return nullptr;
        }

        c.comparisons++;
        if (value < node->data) {
            node->left = erase(node->left, value, erased);
        } else if (value > node->data) {
            node->right = erase(node->right, value, erased);
        } else {
            erased = true;

            // 0 or 1 child
            c.comparisons++;
            if (!node->left || !node->right) {
                Node *child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            // 2 children
            Node *successor = findMin(node->right);
            node->data = successor->data;
            node->right = erase(node->right, successor->data, erased);
        }

        return rebalance(node);
    }

public:
    Avl() : Bst() {}

    bool insert(int value) {

        c.inserts++;

        bool inserted = false;
        root = insert(root, value, inserted);
        return inserted;
    }

    bool erase(int value) {

        c.deletes++;

        bool erased = false;
        root = erase(root, value, erased);
        return erased;
    }

    const char *name() const {
        return "AVL";
    }

    int height() const {
        return height(root);
    }

    Counters get_counters() const {
        return c;
    }
};