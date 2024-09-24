#include "WordCat.h" //which includes WordList.h and Word.h
#include <fstream>   // fstream for file I/O
#include <stdexcept> // runtime_error
#include <cctype>    // tolower : converts a letter to lowercase
using namespace std;

// Default constructor : WordCat word_cat;
WordCat::WordCat() : category(), words() {}

// Constructor : for eg. WordCat word_cat(Word("fruits"));
// creating an instance of the class WordCat (called word_cat) with category name "fruits" by calling the conversion constructor of Word class
// uses reference so instead of copying word object, it uses the same object / memory location
WordCat::WordCat(const Word &categoryName) : category(categoryName), words() {}

// Copy constructor : WordCat word_cat1(word_cat2);
WordCat::WordCat(const WordCat &other) : category(other.category), words(other.words) {}

// Move constructor : WordCat word_cat1(move(word_cat2));
// std::move is used to cast an lvalue to an rvalue reference (temporary object), which allows us to call the move constructor
WordCat::WordCat(WordCat &&other) noexcept : category(move(other.category)), words(move(other.words)) {}

// Copy assignment operator : word_cat1 = word_cat2;
WordCat &WordCat::operator=(const WordCat &other)
{
    if (this != &other)
    {
        category = other.category;
        words = other.words;
    }
    return *this;
}

// Move assignment operator : word_cat1 = move(word_cat2);
WordCat &WordCat::operator=(WordCat &&other) noexcept
{
    if (this != &other)
    {
        category = move(other.category);
        words = move(other.words);
    }
    return *this;
}

// Print all words in the category
void WordCat::printWords() const
{
    cout << words;
}

// Insert a new word into the category
void WordCat::insertWord(const Word &word)
{
    words.insertSorted(word); // method found in WordList class
}

// Remove a word from the category
void WordCat::removeWord(const Word &word)
{
    if (!words.remove(word)) // method found in WordList class
                             // if false
    {
        cout << "Word not found in the category.\n";
    }
}

// Clear all words in the category
void WordCat::clearWords()
{
    while (!words.isEmpty()) // while the list is not empty
    {
        words.pop_front(); // remove the first word
    }
}

// Modify the category name
void WordCat::modifyCategoryName(const Word &newCategoryName)
{
    category = newCategoryName;
}

// Search for a word in the category
bool WordCat::searchWord(const Word &word) const
{
    return words.lookup(word); // lookup method found in WordList class, uses search method to find the word
}

// Show all words starting with a specific letter
void WordCat::showWordsStartingWith(char letter) const
{
    for (int i = 0; i < words.length(); ++i)
    {
        Word word = words.fetchWord(i);             // fetchWord method found in WordList class, goes through the list and returns the word at the index
        if (tolower(word.at(0)) == tolower(letter)) // comparing the first character of the word with the given letter
                                                    // word.at(0) vs word[0] ; .at() performs bounds checking, [] does not
        {
            cout << word << ' ';
        }
    }
    cout << '\n'; // new line
}

// Load words from a file
void WordCat::loadFromFile(const char *filename)
{
    ifstream file(filename); // ifstream class is part of the c++ standard library and is used to read from files
    if (!file.is_open())     // same with is_open() (member function prvided by ifstream class)
    {
        throw runtime_error("Failed to open file.");
    }
    char word[100];      // temporary array to store the word read from the file
    while (file >> word) // extraction operator reads a word from the file and stores it in the word array, deliniated by whitespace
    {
        Word wordObj(word);  // creating a Word object with the word read from the file
        insertWord(wordObj); // inserting the word into the category
    }
}

// Run the interactive menu
void WordCat::run()
{
    int choice = menu(); // display the menu and get the user's choice
    while (choice != 0)  // while the user does not choose to exit
    {
        perform(choice); // perform (method below) the action based on the user's choice
        choice = menu(); // display the menu again and get the user's choice
    }
    cout << "bye.\n";
}

// Display the menu
int WordCat::menu() const // will not change any member variables
{
    cout << "===========================\n";
    cout << "Word Category: " << category.c_str() << '\n';
    cout << "===========================\n";
    cout << "1. Print all the words in this category\n";
    cout << "2. Insert a new word into this category\n";
    cout << "3. Remove a given word from this category\n";
    cout << "4. Empty this category\n";
    cout << "5. Modify the category name\n";
    cout << "6. Search for a specific word in this category\n";
    cout << "7. Show all the words starting with a given letter\n";
    cout << "8. Load from a text file\n";
    cout << "0. Exit\n";
    cout << "===========================\n";
    cout << "Enter Your Choice: ";
    int choice;
    cin >> choice; // user input, which will be stored in the choice variable for the switch statement
    return choice;
}

// Perform the selected action
void WordCat::perform(int choice)
{
    switch (choice)
    {
    case 1:
        printWords();
        break;
    case 2:
    {
        char input[100]; // creating a temporary array to store the word
        do
        {
            cout << "Enter a word: ";
            // temporary array to store the word, max size of 100 characters
            // cin.ignore();            // ignore any characters from previous inputs or whitespace in the input buffer (because cin leaves the newline character ('\n') in the input buffer. If you were to call cin.getline() immediately after reading input with cin, cin.getline() would read the newline character and immediately stop)
            // cin.getline(input, 100); // cin.getline(char_array, size) where char array is the where the input will be stored (declared beforehand here) and size is the maximum number of characters to read
            cin >> input; // reads up to 99 char. + null terminator
            insertWord(Word(input));
        } while (strcmp(input, "exit") != 0); // if the user enters 'exit', the loop will stop
        break;
    }
    case 3:
    {
        cout << "Enter a word to remove: ";
        char input[100];
        cin.ignore();
        cin.getline(input, 100);
        removeWord(Word(input));
        break;
    }
    case 4:
        clearWords();
        break;
    case 5:
    {
        cout << "Enter a new category name: ";
        char input[100];
        cin.ignore();
        cin.getline(input, 100);
        modifyCategoryName(Word(input));
        break;
    }
    case 6:
    {
        cout << "Enter a word to search for: ";
        char input[100];
        cin.ignore();
        cin.getline(input, 100);
        if (searchWord(Word(input)))
        {
            cout << "Word found in the category.\n";
        }
        else
        {
            cout << "Word not found in the category.\n";
        }
        break;
    }
    case 7:
    {
        cout << "Enter the starting letter: ";
        char letter;   // creating a variable to store the letter
        cin >> letter; // user input stored in the letter variable
        showWordsStartingWith(letter);
        break;
    }
    case 8:
    {
        cout << "Enter the filename to load from: ";
        char filename[100];
        cin >> filename;
        loadFromFile(filename);
        break;
    }
    case 0:
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }
}

// Overloaded insertion operator :
ostream &operator<<(ostream &os, const WordCat &wordCat) //
// cout << wordCat; // prints Category: fruits Words: 5
{
    os << "Category: " << wordCat.category.c_str() << '\n';
    os << "Words: " << wordCat.words << '\n';
    return os;
}

// getName method : returns the category name
Word WordCat::getName() const
{
    return category;
}

// method that transforms word into a c-string
const char *WordCat::c_str() const
{
    return category.c_str();
}

size_t WordCat::length() const
{
    return words.length();
}
