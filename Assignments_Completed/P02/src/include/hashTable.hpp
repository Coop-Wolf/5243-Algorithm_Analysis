#pragma once

#include <cstddef>
#include <vector>
#include "counters.hpp"

class HashTable {
private:
    std::vector<std::vector<int>> table;
    std::size_t capacity;
    std::vector<int> resize_values;
    std::size_t size;

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

    // Resize hash to prime number close to double current size
    void resize()
    {
        // Hold new size of hash
        int new_size = 0;

        for(int i=0; i < resize_values.size(); i++)
        {
            c.comparisons++; // For loop comparison

            c.comparisons++;
            if (resize_values[i] > (int)capacity)
            {
                new_size = resize_values[i];
                break;
            }
        }

        // Create new table with new capacity
        std::vector<std::vector<int>> temp_table(new_size);

        // Rehash all existing elements into temp table
        capacity = new_size;
        for(auto &bucket : table)
        {
            for(int key : bucket)
            {
                c.structural_ops++;
                temp_table[indexFor(key)].push_back(key);
            }
        }

        // point table to new resized table
        table = std::move(temp_table);

    }

public:
    explicit HashTable(std::size_t cap = 7)
        : table(cap), capacity(cap), size(0), resize_values({11, 23, 47, 97, 197, 397, 797, 1597,
    3203, 6421, 12853, 25717, 51437, 102877, 205759}) {}

    bool insert(int key) {

        c.inserts++;

        // Check load factor and resize if needed
        c.comparisons++;
        if (size >= capacity * .75)
        {
            c.resize_events++;
            resize();
        }

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

        // Insert new key into vector (chaining) and increment size of hash
        bucket.push_back(key);
        size++;
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