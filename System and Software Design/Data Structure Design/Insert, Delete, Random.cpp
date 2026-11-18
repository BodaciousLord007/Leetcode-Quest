/*
Problem: Insert Delete GetRandom O(1)

Design a set with average O(1) insertion and removal, and uniform random
selection from its current values. getRandom() is called only when non-empty.
*/

#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

class RandomizedSet {
    std::vector<int> values;
    std::unordered_map<int, std::size_t> indices;
    std::mt19937 randomEngine;

public:
    RandomizedSet() : randomEngine(std::random_device{}()) {}

    bool insert(int value) {
        if (indices.find(value) != indices.end()) {
            return false;
        }

        indices.emplace(value, values.size());
        values.push_back(value);
        return true;
    }

    bool remove(int value) {
        const auto found = indices.find(value);
        if (found == indices.end()) {
            return false;
        }

        const std::size_t position = found->second;
        const int lastValue = values.back();
        if (position != values.size() - 1) {
            values[position] = lastValue;
            indices[lastValue] = position;
        }
        values.pop_back();
        indices.erase(found);
        return true;
    }

    int getRandom() {
        std::uniform_int_distribution<std::size_t> distribution(0, values.size() - 1);
        return values[distribution(randomEngine)];
    }
};

int main() {
    RandomizedSet set;

    std::cout << std::boolalpha;
    std::cout << set.insert(1) << '\n'; // true
    std::cout << set.remove(2) << '\n'; // false
    std::cout << set.insert(2) << '\n'; // true
    std::cout << set.remove(1) << '\n'; // true
    std::cout << set.insert(2) << '\n'; // false
    std::cout << set.getRandom() << '\n'; // 2

    return 0;
}
