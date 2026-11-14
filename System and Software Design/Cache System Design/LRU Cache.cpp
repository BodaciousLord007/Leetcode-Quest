/*
Problem statement: LRU Cache

Design a data structure that implements a Least Recently Used (LRU) cache.

Implement the LRUCache class:
- LRUCache(int capacity): Initialize the cache with a positive capacity.
- int get(int key): Return the value associated with key if it exists;
  otherwise, return -1. A successful access makes the key most recently used.
- void put(int key, int value): Update the value if key already exists, or
  insert a new key-value pair. The key becomes most recently used. If an
  insertion exceeds capacity, evict the least recently used key.

Both get and put must run in O(1) average time.

Example:
LRUCache cache(2);
cache.put(1, 10);
cache.put(2, 20);
cache.get(1);     // Returns 10.
cache.put(3, 30); // Evicts key 2.
cache.get(2);     // Returns -1.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
    struct Node {
        int key;
        int val;
        Node* next;
        Node* prev;

        Node(int key, int val) {
            this->key = key;
            this->val = val;
            next = nullptr;
            prev = nullptr;
        }
    };

public:
    Node* head;
    Node* tail;
    int capacity;
    int size;
    unordered_map<int, Node*> position;

    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;

        size = 0;
    }

    void deleteNode(Node* node) {
        Node* p = node->prev;
        Node* n = node->next;

        p->next = n;
        n->prev = p;
    }

    void insertNode(Node* node) {
        Node* p = head;
        Node* n = head->next;

        node->prev = p;
        node->next = n;

        p->next = node;
        n->prev = node;
    }

    int get(int key) {
        if (position.count(key) == 0) return -1;
        else {
            auto node = position[key];
            deleteNode(node);
            insertNode(node);
            return node->val;
        }
    }

    void put(int key, int value) {
        if (position.count(key) != 0) {
            Node* node = position[key];
            node->val = value;
            deleteNode(node);
            insertNode(node);
            return;
        }

        if (size == capacity) {
            Node* node = tail->prev;
            position.erase(node->key);
            deleteNode(node);
            delete node;
            size -= 1;
        }

        Node* node = new Node(key, value);
        insertNode(node);
        position[key] = node;
        size += 1;
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl; // 10

    cache.put(3, 30); // evicts 2
    cout << cache.get(2) << endl; // -1

    cache.put(4, 40); // evicts 1
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 30
    cout << cache.get(4) << endl; // 40

    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
