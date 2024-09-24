#ifndef WORDCATVEC_H
#define WORDCATVEC_H

#include "WordCat.h"
#include <iostream>
#include <stdexcept>

class WordCatVec
{
private:
    WordCat *word_category;
    size_t capacity; // number of categories that can be stored
    size_t size;     // number of categories

    void resize(size_t new_capacity);

public:
    WordCatVec();
    ~WordCatVec();

    void addCategory(const WordCat &category);
    void removeCategory(const char *category_name);
    void clearCategory(const char *category_name);
    void modifyCategory(const char *category);
    void searchCategories(const char *word) const;
    void showWordsStartingWith(char letter) const;
    void loadFromFile(const char *filename);
    void printCategories() const;
    void run();
};

#endif // WORDCATVEC_H
