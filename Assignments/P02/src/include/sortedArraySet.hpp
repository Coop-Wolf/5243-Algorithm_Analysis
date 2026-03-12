#pragma once

#include <cstddef>
#include <iostream>
#include "counters.hpp"

class SortedArraySet {
private:
    int *data;
    std::size_t count;
    std::size_t capacity;

    void resize(std::size_t newCapacity) {

        c.resize_events++;

        c.structural_ops++;
        int *newData = new int[newCapacity];

        for (std::size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        c.structural_ops++;
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    mutable Counters c;

    // Returns the index where value is found,
    // or where it should be inserted to maintain sorted order.
    std::size_t lowerBound(int value) const {
        std::size_t left = 0;
        std::size_t right = count;

        while (left < right) {
            c.comparisons++;

            std::size_t mid = left + (right - left) / 2;

            c.comparisons++;
            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

public:
    explicit SortedArraySet(std::size_t initialCapacity = 8)
        : data(new int[initialCapacity]), count(0), capacity(initialCapacity) {}

    ~SortedArraySet() {
        delete[] data;
    }

    std::size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    bool contains(int value) const {
        c.lookups++;

        c.comparisons++;
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);

        return pos < count && data[pos] == value;
    }

    bool insert(int value) {

        c.inserts++;

        std::size_t pos = lowerBound(value);

        // Duplicate guard: do not insert if already present
        c.comparisons++;
        if (pos < count && data[pos] == value) {
            return false;
        }

        // Grow array if full
        c.comparisons++;
        if (count == capacity) {
            resize(capacity * 2);
        }

        // Shift elements right to make room
        for (std::size_t i = count; i > pos; i--) {
            c.comparisons++;
            data[i] = data[i - 1];
        }

        data[pos] = value;
        count++;

        return true;
    }

    bool erase(int value) {

        c.deletes++;

        c.comparisons++;
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);

        c.comparisons++;
        if (pos >= count || data[pos] != value) {
            return false;
        }

        // Eager delete:
        // shift everything left immediately to close the gap
        for (std::size_t i = pos; i + 1 < count; i++) {
            c.comparisons++;
            data[i] = data[i + 1];
        }

        count--;
        return true;
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < count; i++) {
            c.comparisons++;

            std::cout << data[i];
            c.comparisons++;
            if (i + 1 < count) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
};