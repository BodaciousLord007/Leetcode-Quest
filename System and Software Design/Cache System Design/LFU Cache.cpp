/*
Problem statement: LFU Cache

Design a data structure that implements a Least Frequently Used (LFU) cache.

Implement the LFUCache class:
- LFUCache(int capacity): Initialize the cache with the given capacity.
- int get(int key): Return the value associated with key if it exists;
  otherwise, return -1. A successful access increases its frequency by one.
- void put(int key, int value): Update an existing key's value and increase
  its frequency, or insert a new key with frequency one. If the cache is
  full, evict the key with the lowest frequency. If frequencies tie, evict
  the least recently used key among them. A zero-capacity cache stores nothing.

Both get and put must run in O(1) average time.
*/

#include <iostream>
#include <unordered_map>
#include <utility>

using namespace std;

class LFUCache
{
private:
    struct Node
    {
        Node *next;
        Node *prev; // Fixed
        int key;
        int val; // Fixed
        int freq;

        Node(int key, int val)
        {
            next = nullptr;
            prev = nullptr;

            this->key = key; // Fixed
            this->val = val;

            freq = 1;
        }
    };

    int capacity;
    int minFreq;
    int size;

    unordered_map<int, Node *> position;
    unordered_map<int, pair<Node *, Node *>> freqList;

public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;
        minFreq = 0;
        size = 0;
    }

    void deleteNode(Node *node)
    {
        Node *p = node->prev;
        Node *n = node->next;

        p->next = n;
        n->prev = p;
    }

    void insertNode(Node *node)
    {
        int freq = node->freq;

        if (freqList.count(freq) == 0)
        {
            Node *head = new Node(-1, -1);
            Node *tail = new Node(-1, -1);

            head->next = tail;
            tail->prev = head;

            freqList[freq] = {head, tail};
        }

        Node *head = freqList[freq].first;
        Node *n = head->next;

        node->prev = head;
        node->next = n;

        head->next = node;
        n->prev = node;
    }

    void updateFreq(Node *node)
    {
        deleteNode(node);

        int freq = node->freq;

        Node *head = freqList[freq].first;
        Node *tail = freqList[freq].second;

        if (freq == minFreq && head->next == tail)
        {
            minFreq++;
        }

        node->freq++;
        insertNode(node);
    }

    int get(int key)
    {
        if (position.count(key) == 0)
            return -1;

        Node *node = position[key];

        updateFreq(node);
        return node->val;
    }

    void put(int key, int value)
    {
        if (capacity == 0)
            return;

        if (position.count(key) != 0)
        {
            Node *node = position[key];
            node->val = value;
            updateFreq(node);
            return;
        }

        if (size == capacity)
        {
            size--;

            Node *tail = freqList[minFreq].second;
            Node *node = tail->prev;

            position.erase(node->key);
            deleteNode(node);
            delete node;
        }

        Node *node = new Node(key, value);
        minFreq = 1;

        insertNode(node);
        position[key] = node;
        size++;
    }

    ~LFUCache()
    {
        for (auto &entry : position)
            delete entry.second;

        for (auto &entry : freqList)
        {
            delete entry.second.first;
            delete entry.second.second;
        }
    }
};

int main() {
    LFUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl; // 10: key 1 now has frequency 2.

    cache.put(3, 30); // Evicts key 2, which has frequency 1.
    cout << cache.get(2) << endl; // -1
    cout << cache.get(3) << endl; // 30: keys 1 and 3 now have frequency 2.

    cache.put(4, 40); // Evicts key 1, the least recently used tied key.
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 30
    cout << cache.get(4) << endl; // 40

    return 0;
}

