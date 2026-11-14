/*
Problem statement: Stream of Characters

Design a data structure that checks whether any suffix of a character stream
matches a word in a given dictionary.

Implement the StreamChecker class:
- StreamChecker(vector<string>& words): Initialize with the dictionary words.
- bool query(char letter): Append letter to the stream and return true if
  some non-empty suffix of the stream equals a dictionary word; otherwise,
  return false.

All words are non-empty and contain lowercase English letters. Each query
also supplies a lowercase English letter. Queries retain the previous stream.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StreamChecker
{
    struct Node
    {
        int cnt = 0;
        vector<Node *> next = vector<Node *>(26, nullptr);
    };

    Node *root;

    void insert(Node *node, string &s, int index)
    {
        if (index >= s.length())
        {
            node->cnt += 1;
            return;
        }

        int c = s[index] - 'a';
        if (node->next[c] == nullptr)
        {
            node->next[c] = new Node();
        }

        insert(node->next[c], s, index + 1);
    }

    string q;

public:
    StreamChecker(vector<string> &words)
    {
        root = new Node();

        for (auto v : words)
        {
            reverse(v.begin(), v.end());
            insert(root, v, 0);
        }
    }

    bool query(Node *node, string &s, int index)
    {
        if (node == nullptr)
            return false;
        if (node->cnt != 0)
            return true;
        if (index < 0)
            return false;

        int c = s[index] - 'a';
        return query(node->next[c], s, index - 1);
    }

    bool query(char letter)
    {
        q += letter;
        return query(root, q, (int)q.size() - 1);
    }
};

int main() {
    vector<string> words = {"cd", "f", "kl"};
    StreamChecker checker(words);

    cout << boolalpha;
    cout << checker.query('a') << endl; // false
    cout << checker.query('b') << endl; // false
    cout << checker.query('c') << endl; // false
    cout << checker.query('d') << endl; // true: suffix "cd".
    cout << checker.query('e') << endl; // false
    cout << checker.query('f') << endl; // true: suffix "f".
    cout << checker.query('g') << endl; // false
    cout << checker.query('h') << endl; // false
    cout << checker.query('i') << endl; // false
    cout << checker.query('j') << endl; // false
    cout << checker.query('k') << endl; // false
    cout << checker.query('l') << endl; // true: suffix "kl".

    return 0;
}
