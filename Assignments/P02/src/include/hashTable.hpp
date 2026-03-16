#pragma once

#include <cstddef>
#include <vector>
#include "counters.hpp"

class HashTable {
private:
    std::vector<std::vector<int>> table;
    std::size_t capacity;
    mutable Counters c;

    // Integer hash function
    std::size_t hash(int key) const {

        c.structural_ops++;
        return static_cast<std::size_t>(key) * 2654435761u;
    }

    // Compress hash value into a valid bucket index
    std::size_t indexFor(int key) const {
        c.structural_ops++;
        return hash(key) % capacity;
    }

public:
    explicit HashTable(std::size_t cap = 101)
        : table(cap), capacity(cap) {}

    bool insert(int key) {

        c.inserts++;

        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        // Ignore duplicates
        for (int value : bucket) {
            c.comparisons++;

            c.comparisons++;
            if (value == key) {
                return false;
            }
        }

        bucket.push_back(key);
        return true;
    }

    bool contains(int key) const {

        c.lookups++;

        std::size_t idx = indexFor(key);
        const auto &bucket = table[idx];

        for (int value : bucket) {
            c.comparisons++;

            c.comparisons++;
            if (value == key) {
                return true;
            }
        }

        return false;
    }

    bool erase(int key) {

        c.deletes++;

        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            c.comparisons++;

            c.comparisons++;
            if (bucket[i] == key) {
                // swap-pop delete: fast, order not preserved
                bucket[i] = bucket.back();
                bucket.pop_back();
                return true;
            }
        }

        return false;
    }

    const char *name() const {
        return "HashTable";
    }

    Counters get_counters() const {
        return c;
    }
};