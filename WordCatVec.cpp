#include "WordCatVec.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

WordCatVec::WordCatVec() : capacity(1), size(0) // default constructor : if write WordCatVec word_cat_vec; it will call this constructor
{
    word_category = new WordCat[capacity]; // dynamically allocate memory for the array of WordCat objects
}

WordCatVec::~WordCatVec()
{ // destructor
    delete[] word_category;
}

void WordCatVec::resize(size_t new_capacity)
{
    WordCat *new_array = new WordCat[new_capacity]; // dynamically allocate memory for the new array of WordCat objects
    for (size_t i = 0; i < size; ++i)
    { // copy the old array into the new array
        new_array[i] = word_category[i];
    }
    delete[] word_category;    // deallocate memory for the old array
    word_category = new_array; // point the word_category pointer to the new array
    capacity = new_capacity;   // set the capacity to the new capacity
}

void WordCatVec::addCategory(const WordCat &category)
{
    if (size == capacity)
    { // if the size is equal to the capacity, resize the array
        resize(capacity * 2);
    }
    word_category[size++] = category; // add category to the end of the array
}

void WordCatVec::removeCategory(const char *category_name)
{
    for (size_t i = 0; i < size; ++i) // loop through the array of WordCat objects
    {
        if (strcmp(word_category[i].getName().c_str(), category_name) == 0) // compares two character arrays so need to make a conversion to c-style string method on WordCat
        {                                                                   // if the category name is found
            for (size_t j = i; j < size - 1; ++j)                           // loop through the array starting from the index of the category to remove, found in the previous loop
            {
                word_category[j] = word_category[j + 1]; // move the next category to the current index for all categories after the one to remove
                                                         // do size - 1 so that j + 1 does not go out of bounds
            }
            --size;                                  // decrement the size of the array
            if (size < capacity / 2 && capacity > 1) // if the size is less than half the capacity and the capacity is greater than 1
            {
                resize(capacity / 2);
            }
            return;
        }
    }
    cout << "Category not found." << endl;
}

void WordCatVec::clearCategory(const char *category_name)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(word_category[i].getName().c_str(), category_name) == 0)
        {
            word_category[i].clearWords(); // method in WordCat class
            return;
        }
    }
    cout << "Category not found." << endl;
}

void WordCatVec::modifyCategory(const char *category)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (strcmp(word_category[i].getName().c_str(), category) == 0) // strcmp gives 0 if the two strings are equal
        {
            word_category[i].run(); // runs the WordCat run method because object is of type WordCat (word_category = new WordCat[capacity];)
            return;
        }
    }
    cout << "Category not found." << endl;
}

void WordCatVec::showWordsStartingWith(char letter) const
{
    for (size_t i = 0; i < size; ++i) // goes through all the categories
    {
        word_category[i].showWordsStartingWith(letter); // calls the showWordsStartingWith method in WordCat class
    }
}

void WordCatVec::loadFromFile(const char *filename)
{
    ifstream infile(filename); // open the file
    if (!infile)
    {
        cout << "Failed to open file." << endl;
        return;
    }

    char line[256];                      // temporary array to store the line read from the file of size 256
    WordCat *current_category = nullptr; // pointer to a WordCat object to store the current category

    while (infile.getline(line, sizeof(line))) // read a line from the file
    {
        if (strlen(line) == 0)
            continue;
        if (line[0] == '#') // if the line starts with a '#' character, it is a category name
        {
            if (current_category)
            {
                addCategory(*current_category); // add the current category to the array
                delete current_category;
            }
            current_category = new WordCat(line + 1); // create a new category with the name of the line without the '#' character
        }
        else if (current_category)
        {
            current_category->insertWord(line);
        }
    }

    if (current_category) // if there is a current category
    {
        addCategory(*current_category);
        delete current_category;
    }
}

void WordCatVec::searchCategories(const char *word) const
{
    bool found = false;
    for (size_t i = 0; i < size; ++i)
    {
        if (word_category[i].searchWord(word))
        {
            cout << "Found in category: " << word_category[i].getName() << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Word not found in any category." << endl;
    }
}

void WordCatVec::printCategories() const
{
    if (size == 0)
    {
        cout << "No categories available." << endl;
    }
    else
    {

        for (size_t i = 0; i < size; ++i)
        {
            cout << "Category: " << word_category[i].getName() << endl;
            cout << "Listing all words in that category: " << endl;
            if (word_category[i].length() == 0)
            {
                cout << " empty." << endl;
            }
            word_category[i].printWords();
            cout << endl; // print a new line
            cout << endl; // print a new line
        }
    }
}

void WordCatVec::run()
{
    int choice;
    do
    {
        cout << "============================\n";
        cout << "Word Vocabulary Center\n";
        cout << "============================\n";
        cout << "1. Print all categories\n";
        cout << "2. Add a new category\n";
        cout << "3. Remove a category\n";
        cout << "4. Clear a category\n";
        cout << "5. Modify a category\n";
        cout << "6. Search all categories for a specific word\n";
        cout << "7. Show all the words starting with a given letter\n";
        cout << "8. Load from a text file\n";
        cout << "0. Exit\n";
        cout << "============================\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            printCategories();
            break;
        case 2:
            char category_name[100];
            do
            {
                cout << "Enter the name of the new category (or 'exit' to stop): ";
                cin >> category_name;
                addCategory(WordCat(category_name));
            } while (strcmp(category_name, "exit") != 0); // if the user enters 'exit', the loop will
            break;
        case 3:
        {
            char category_name[100];
            cout << "Enter the name of the category to remove: ";
            cin >> category_name;
            removeCategory(category_name);
            break;
        }
        case 4:
        {
            char category_name[256];
            cout << "Enter the name of the category to clear: ";
            cin.ignore();
            cin.getline(category_name, 256);
            clearCategory(category_name);
            break;
        }
        case 5:
        {
            char category_name[256];
            cout << "Enter the name of the category to modify: ";
            cin.ignore();
            cin.getline(category_name, 256);
            modifyCategory(category_name);
            break;
        }
        case 6:
        {
            char word[256];
            cout << "Enter the word to search for: ";
            cin.ignore();
            cin.getline(word, 256);
            searchCategories(word);
            break;
        }
        case 7:
        {
            char letter;
            cout << "Enter the first letter of the words to show: ";
            cin >> letter;
            showWordsStartingWith(letter);
            break;
        }
        case 8:
        {
            char filename[256];
            cout << "Enter the name of the file to load: ";
            cin.ignore();
            cin.getline(filename, 256);
            loadFromFile(filename);
            break;
        }
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}
