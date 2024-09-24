#ifndef WORD_H // to avoid multiple inclusion
#define WORD_H

#include <cstring> // for strcpy, strlen, etc.
#include <iostream>
using namespace std;

class Word
{
private:
    char *word;
    size_t size;

public:
    Word();
    Word(const char *input);
    Word(const Word &other);
    Word(Word &&other) noexcept;
    Word &operator=(const Word &other);
    Word &operator=(Word &&other) noexcept;
    ~Word();
    size_t length() const;
    const char *c_str() const;
    void changeWord(const Word &newWord);
    void changeWord(const char *newWord);
    Word concat(const Word &other, const char *delimiter = " ") const;
    bool isLess(const Word &other) const;
    char at(size_t n) const;
    void print(ostream &os) const;
    void read(istream &is);
    friend ostream &operator<<(std::ostream &os, const Word &word);
    friend istream &operator>>(std::istream &is, Word &word);
    bool operator>=(const Word &other) const;
    bool operator<=(const Word &other) const;
    bool operator<(const Word &other) const;
    bool operator==(const Word &other) const;
};

#endif // WORD_H
