#ifndef WORDCAT_H
#define WORDCAT_H

#include "WordList.h"
#include "Word.h"
#include <iostream>

class WordCat
{
private:
    Word category;
    WordList words;

    void perform(int choice);
    int menu() const;

public:
    WordCat();
    WordCat(const Word &categoryName);

    WordCat(const WordCat &other);
    WordCat(WordCat &&other) noexcept;
    WordCat &operator=(const WordCat &other);
    WordCat &operator=(WordCat &&other) noexcept;
    ~WordCat() = default;

    void run();
    void printWords() const;
    void insertWord(const Word &word);
    void removeWord(const Word &word);
    void clearWords();
    void modifyCategoryName(const Word &newCategoryName);
    bool searchWord(const Word &word) const;
    void showWordsStartingWith(char letter) const;
    void loadFromFile(const char *filename);
    Word getName() const; // takes no arguments and returns word, the category name
    const char *c_str() const;
    size_t length() const;

    friend std::ostream &operator<<(std::ostream &os, const WordCat &wordCat);
};

#endif // WORDCAT_H
