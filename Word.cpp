#include "Word.h"

// Default constructor : (Word w;) initializing word to point to a new array of size 1 (containing only the null character '\0') and size to 0. This is an empty word.
Word::Word() : word(new char[1]), size(0)
{
    strcpy(word, "\0");
}

// Conversion constructor : Word w("hello"); input is a pointer to the first character of the array of characters that is input.
Word::Word(const char *input) : word(new char[strlen(input) + 1]), size(strlen(input))
{
    strcpy(word, input);
}

// Copy constructor : Word w1("hello"); Word w2(w1); &other here is a reference to w1, so we are copying the word and size of w1 into the NEW array of characters and size variables of w2
Word::Word(const Word &other) : word(new char[other.size + 1]), size(other.size) // // The dot operator (.) is used to access the members (variables, methods) of an object (so can access the word and size variables of w1 in previous example)
{
    strcpy(word, other.word);
}

// Move constructor : Word w1("hello"); Word w2(std::move(w1))
// && is an rvalue reference == binds to a temporary value that will be destroyed after the move constructor is called
// to make sure that it does not also destroy our new word (w2) we set w1.word to nullptr, so w1 no longer points to the array of characters that w2 copied
Word::Word(Word &&other) noexcept : word(other.word), size(other.size)
{
    other.word = nullptr;
    other.size = 0;
}

// Copy assignment operator : Word w1("hello"); Word w2 = w1;
Word &Word::operator=(const Word &other)
{
    if (this != &other) // this is a pointer to the object that is calling the function (w2) and &other is a pointer to the object that is being passed in (w1) == if w2 is not w1
    {
        delete[] word;                   // to make sure that w2 does not have a word already, we delete
        word = new char[other.size + 1]; // allocate memory for the new word
        size = other.size;               // set the size of the new word
        strcpy(word, other.word);        // copy the new word into the word variable
    }
    return *this;
}

// Move assignment operator : Word w1("hello"); Word w2 = std::move(w1)
Word &Word::operator=(Word &&other) noexcept
{
    if (this != &other)
    {
        delete[] word;
        word = other.word;
        size = other.size;
        other.word = nullptr;
        other.size = 0;
    }
    return *this;
}

// Destructor : ~Word w;
Word::~Word()
{
    delete[] word;
}

// Accessor for length
// // Word w("hello") ; size_t len = w.length(); // len will be 5
size_t Word::length() const
{
    return size;
}

// Accessor for C-style string
// // Word w("hello") ; const char *str = w.c_str(); // str will point to the first character of the array of characters that is word.
const char *Word::c_str() const
{
    return word;
}

// Mutator methods
// Word w("hello"); w.changeWord(w2);
void Word::changeWord(const Word &newWord) // function does not return any value (void)
{
    delete[] word;                     // delete the word that is already there
    word = new char[newWord.size + 1]; // allocate memory for the new word
    size = newWord.size;               // set the size of the new word
    strcpy(word, newWord.word);        // copy the new word into the word variable
}

// Word w("hello"); w.changeWord("world");
void Word::changeWord(const char *newWord)
{
    delete[] word;
    word = new char[strlen(newWord) + 1];
    size = strlen(newWord);
    strcpy(word, newWord);
}

// Concatenation method : Word w1("hello"); Word w2("world"); Word w3 = w1.concat(w2); // w3 will be "helloworld"
Word Word::concat(const Word &other, const char *delimiter) const // delimiter is a string that will be added between the two words eg. if you have a Word object w1 with the word "Hello", another Word object w2 with the word "World", and you call w1.concat(w2, ", "), the concat method will return a new Word object with the word "Hello, World".
{
    size_t newSize = size + strlen(delimiter) + other.size; // size of the new word (including delimiter)
    char *newWord = new char[newSize + 1];                  // allocate memory for the new word
    strcpy(newWord, word);                                  // copy the first word into the new word
    strcat(newWord, delimiter);                             // concatenate the delimiter
    strcat(newWord, other.word);                            // concatenate the second word
    return Word(newWord);                                   // return the new word
}

// Comparison method
bool Word::isLess(const Word &other) const
{
    return strcmp(c_str(), other.c_str()) < 0; // if word is lexicographically less than other.word, return a negative number and therefore, true
}

// Method to get the n'th character
char Word::at(size_t n) const // which index to get the character from
{
    if (n < length()) // if index is within the bounds of the word
    {
        return c_str()[n];
    }
    throw std::out_of_range("Index out of range");
}

// Print method : Word myWord("example"); //myWord.print(std::cout);  prints "example"
void Word::print(ostream &os) const
{
    os << word;
}

// Read method
void Word::read(istream &is)
{
    char buffer[1000];         // temporary array of characters to store the input
    is >> buffer;              // get the input from the input stream
    delete[] word;             // delete the word that is already there
    size = strlen(buffer);     // set the size of the new word
    word = new char[size + 1]; // allocate memory for the new word
    strcpy(word, buffer);      // copy the new word into the word variable
}

// Overloaded insertion operator<< : Word myWord("example"); std::cout << myWord; //prints "example"
ostream &operator<<(ostream &os, const Word &word)
{
    os << word.c_str();
    return os;
}

// Overloaded extraction operator : Word myWord; std::cin >> myWord; // reads a word from the keyboard
istream &operator>>(istream &in, Word &word) // first paramter is where the word will be read from, second parameter is the word to be read
{
    char temp[100];        // temporary array of characters to store the input
    in >> temp;            // get the input from the input stream
    word.changeWord(temp); // change the word to the input
    return in;             // return the input stream
}

// Overloaded comparison operators
// Word w1("hello"); Word w2("world"); if (w1 >= w2) { // do something }
bool Word::operator>=(const Word &other) const //
{
    return strcmp(c_str(), other.c_str()) >= 0; // if word is lexicographically greater than or equal to other.word, return a positive number and therefore, true
}

bool Word::operator<=(const Word &other) const
{
    return strcmp(c_str(), other.c_str()) <= 0;
}

bool Word::operator<(const Word &other) const
{
    return strcmp(c_str(), other.c_str()) < 0;
}

bool Word::operator==(const Word &other) const
{
    return strcmp(c_str(), other.c_str()) == 0;
}