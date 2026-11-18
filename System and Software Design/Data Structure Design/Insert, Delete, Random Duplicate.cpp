/*
Problem statement: Insert Delete GetRandom O(1) - Duplicates allowed

RandomizedCollection is a data structure that contains a collection of numbers,
possibly duplicates (i.e., a multiset of numbers). It should support a collection
of operations with average O(1) time complexity.

Implement the RandomizedCollection class:
- RandomizedCollection(): Initializes the empty RandomizedCollection object.
- bool insert(int val): Inserts an item val into the multiset, even if the item
  is already present. Returns true if the item was not present, false otherwise.
- bool remove(int val): Removes an item val from the multiset if present.
  Returns true if the item was present, false otherwise. Note that if val has
  multiple occurrences in the multiset, we only remove one of them.
- int getRandom(): Returns a random element from the current multiset of elements.
  The probability of each element being returned is linearly related to the number
  of same values the multiset contains.

Both insert, remove, and getRandom must run in O(1) average time.

Example:
RandomizedCollection collection;
collection.insert(1);   // return true (1 was not present)
collection.insert(1);   // return false (1 was already present)
collection.insert(2);   // return true (2 was not present)
collection.getRandom(); // returns 1 with prob 2/3, and 2 with prob 1/3
collection.remove(1);   // return true (1 was present)
collection.getRandom(); // returns 1 and 2 with equal prob 1/2
*/

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class RandomizedCollection {
public:
    vector<int> arr;
    unordered_map<int, unordered_set<int>> index;

    RandomizedCollection() {}

    bool insert(int val) {
        bool notPresent = (index.find(val) == index.end() || index[val].empty());
        index[val].insert(static_cast<int>(arr.size()));
        arr.push_back(val);
        return notPresent;
    }

    bool remove(int val) {
        auto it = index.find(val);
        if (it == index.end() || it->second.empty()) {
            return false;
        }

        int removeIndex = *it->second.begin();
        it->second.erase(removeIndex);

        int lastIndex = static_cast<int>(arr.size()) - 1;
        if (removeIndex != lastIndex) {
            int lastVal = arr[lastIndex];
            arr[removeIndex] = lastVal;
            index[lastVal].erase(lastIndex);
            index[lastVal].insert(removeIndex);
        }

        arr.pop_back();
        if (index[val].empty()) {
            index.erase(val);
        }
        return true;
    }

    int getRandom() {
        int i = rand() % arr.size();
        return arr[i];
    }
};

using RandomizedSet = RandomizedCollection;

int main() {
    RandomizedCollection collection;

    cout << boolalpha;
    cout << collection.insert(1) << endl;   // true: 1 is inserted, not previously present
    cout << collection.insert(1) << endl;   // false: 1 is inserted again, already present
    cout << collection.insert(2) << endl;   // true: 2 is inserted, not previously present
    cout << collection.getRandom() << endl; // returns 1 with prob 2/3, or 2 with prob 1/3
    cout << collection.remove(1) << endl;   // true: one 1 is removed
    cout << collection.getRandom() << endl; // returns 1 or 2 with equal probability 1/2

    return 0;
}

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
