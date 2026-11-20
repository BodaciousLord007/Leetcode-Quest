/*
Problem statement: All O`one Data Structure

Design a data structure to store the counts of strings with the ability
to return the strings with minimum and maximum counts.

Implement the AllOne class:
- AllOne(): Initializes the object of the data structure.
- void inc(string key): Increments the count of the string key by 1.
  If key does not exist in the data structure, insert it with count 1.
- void dec(string key): Decrements the count of the string key by 1.
  If the count of key is 0 after the decrement, remove it from the data
  structure. It is guaranteed that key exists in the data structure before
  the decrement.
- string getMaxKey(): Returns one of the keys with the maximal count.
  If no element exists, return an empty string "".
- string getMinKey(): Returns one of the keys with the minimum count.
  If no element exists, return an empty string "".

Each function must run in O(1) average time complexity.

Example:
AllOne allOne;
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "leet"
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Node {
  unordered_set<string> sList;
  int freq;
  Node *prev, *next;

  Node(int freq) {
    this->freq = freq;
    prev = next = nullptr;
  }
};

class AllOne {
public:
  Node *head;
  Node *tail;
  unordered_map<string, Node *> index;

  AllOne() {
    head = new Node(-1);
    tail = new Node(-1);

    tail->prev = head;
    head->next = tail;
  }

  void addNextNode(Node *node, Node *nxtNode) {
    nxtNode->prev = node;
    nxtNode->next = node->next;

    node->next->prev = nxtNode;
    node->next = nxtNode;
  }

  void deleteNode(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
  }

  void inc(string key) {
    if (index.find(key) == index.end()) {
      if (head->next == tail || head->next->freq != 1) {
        Node *target = new Node(1);
        addNextNode(head, target);
      }

      Node *target = head->next;
      target->sList.insert(key);
      index[key] = target;
      return;
    }

    Node *current = index[key];
    Node *target = current->next;

    if (target == tail || target->freq != current->freq + 1) {
      target = new Node(current->freq + 1);
      addNextNode(current, target);
    }

    current->sList.erase(key);
    target->sList.insert(key);
    index[key] = target;

    if (current->sList.empty())
      deleteNode(current);
  }

  void dec(string key) {
    if (index.find(key) == index.end())
      return;

    Node *current = index[key];

    if (current->freq == 1) {
      current->sList.erase(key);
      index.erase(key);

      if (current->sList.empty())
        deleteNode(current);
      return;
    }

    Node *target = current->prev;

    if (target == head || target->freq != current->freq - 1) {
      target = new Node(current->freq - 1);
      addNextNode(current->prev, target);
    }

    current->sList.erase(key);
    target->sList.insert(key);
    index[key] = target;

    if (current->sList.empty())
      deleteNode(current);
  }

  string getMaxKey() {
    if (tail->prev == head)
      return "";
    return *(tail->prev->sList.begin());
  }

  string getMinKey() {
    if (head->next == tail)
      return "";
    return *(head->next->sList.begin());
  }

  ~AllOne() {
    Node *curr = head;
    while (curr != nullptr) {
      Node *nxt = curr->next;
      delete curr;
      curr = nxt;
    }
  }
};

int main() {
  AllOne allOne;

  allOne.inc("hello");
  allOne.inc("hello");
  cout << allOne.getMaxKey() << endl; // "hello"
  cout << allOne.getMinKey() << endl; // "hello"

  allOne.inc("leet");
  cout << allOne.getMaxKey() << endl; // "hello"
  cout << allOne.getMinKey() << endl; // "leet"

  allOne.dec("hello");
  allOne.dec("hello");
  cout << allOne.getMaxKey() << endl; // "leet"
  cout << allOne.getMinKey() << endl; // "leet"

  return 0;
}

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
