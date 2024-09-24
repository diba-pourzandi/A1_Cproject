#ifndef WORDLIST_H
#define WORDLIST_H

#include "Word.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class WordList
{
private:
    struct Node
    {
        Word word;
        Node *next;
        Node *prev;

        // Constructors for Node
        Node(const Word &aword, Node *next = nullptr, Node *prev = nullptr)
            : word(aword), next(next), prev(prev) {}

        Node() = delete;
        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(const Node &) = delete;
        Node &operator=(Node &&) = delete;
        ~Node() = default;
    };

    Node *head;
    Node *tail;
    size_t size;

    Node *search(const Word &word) const;
    Node *getWord(int n) const;

public:
    WordList();
    WordList(const WordList &other);
    WordList(WordList &&other) noexcept;
    WordList &operator=(const WordList &other);
    WordList &operator=(WordList &&other) noexcept;
    ~WordList();

    size_t length() const;
    bool isEmpty() const;
    Word &front();
    Word &back();
    void push_front(const Word &word);
    void push_back(const Word &word);
    Word pop_front();
    Word pop_back();
    void insertSorted(const Word &word);
    bool remove(const Word &word);
    Word fetchWord(int index) const;
    void print(ostream &os, int n = 5) const;
    bool lookup(const Word &word) const;

    friend ostream &operator<<(ostream &os, const WordList &list);
};

#endif // WORDLIST_H
