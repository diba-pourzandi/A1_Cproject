#include <cstring>
#include <iostream>
using namespace std;

class Word
{
private:         // means can only be accessed by the class itself
    char *word;  // pointer to the first character of an array of characters (word)
    size_t size; // size_t is an unsigned integer type, used to represent the size of objects in bytes

public:
    // Default constructor : (Word w;)
    // initializing word to point to a new array of size 1 (containing only the null character '\0') and size to 0. This is an empty word.
    Word() : word(new char[1]{'\0'}), size(0) {}
    // better to use initilization list rather than assignment in constructor body
    // 1. since assignment will first default-initialize the member and then assign it a value, which means you can't use CONST members in assignment
    // 2. even if you list the varibales in a different order than they are declared, they will be initialized in the order they are declared in the class (our private section)

    // Conversion constructor : Word w("hello");
    // input is a pointer to the first character of the array of characters that is input.
    // functions like strlen, strcpy, strcat, strcmp, etc. move through the array of characters until they reach the null character '\0' at the end of the array.
    Word(const char *input) : word(new char[strlen(input) + 1]), size(strlen(input))
    {
        strcpy(word, input);
    }
    // word = new char[strlen(input) + 1] : allocating memory for the new word (its length + /0 character at the end)
    // size = strlen(input) : setting the size of the new word to the length of the input
    // strcpy(word, input) : copying the input intto the word variable

    // Copy constructor : Word w1("hello"); Word w2(w1);
    // &other here is a reference to w1, so we are copying the word and size of w1 into the NEW array of characters and size variables of w2
    // already have the size and word variables or w1 because has gone through the conversion constructor == Word w1("hello")
    // The dot operator (.) is used to access the members (variables, methods) of an object (so can access the word and size variables of w1 in this case)
    /*
    Dot Operator VS Arrow Operator

    class MyClass {
public:
    int x;
    MyClass(int val) : x(val) {}
};

int main() {
    MyClass obj(10);  // obj is an object of MyClass
    MyClass* ptr = &obj;  // ptr is a pointer to obj

    // Accessing member of obj directly
    std::cout << "Value of x: " << obj.x << std::endl;

    // Accessing member of obj through pointer
    std::cout << "Value of x: " << ptr->x << std::endl;

    return 0;
}

    */
    Word(const Word &other) : word(new char[other.size + 1]), size(other.size)
    {
        strcpy(word, other.word);
    }

    // Move constructor : Word w1("hello"); Word w2(std::move(w1))
    // (std::move is a utility function that converts its argument into an rvalue reference)
    // && is an rvalue reference == binds to a temporary value that will be destroyed after the move constructor is called
    // to make sure that it does not also destroy our new word (w2) we set w1.word to nullptr, so w1 no longer points to the array of characters that w2 copied
    // Since size is not an array but size_t, and does not have a pointer, we do not need to set it to nullptr
    // instead, we just set it to 0
    // "noexcept" promises the function will not throw exceptions which can help with optimization
    Word(Word &&other) noexcept : word(other.word), size(other.size)
    {
        other.word = nullptr;
        other.size = 0;
    }

    // Copy assignment operator : Word w1("hello"); Word w2; w2 = w1;
    // if the word is not the same as the word we are trying to copy, we delete the word and size of the word we are trying to copy
    // then we copy the word and size of the word we are trying to copy into the new word
    // we return the new word
    Word &operator=(const Word &other)
    {
        if (this != &other) // this is a pointer to the object that is calling the function (w2) and &other is a pointer to the object that is being passed in (w1) == if w2 is not w1
        {
            delete[] word; // to make sure that w2 does not have a word already, we delete
            word = new char[other.size + 1];
            size = other.size;
            strcpy(word, other.word);
        }
        return *this;
    }

    // Move assignment operator : Word w1("hello"); Word w2; w2 = std::move(w1);
    Word &operator=(Word &&other) noexcept
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

    // MOVE VS COPY
    // Move operations are used when the source object is a temporary object or an object that is going to be destroyed after the move operation.
    // Copy operations are used when the source object is not going to be destroyed after the copy operation.

    // CONSTRUCTORS VS ASSIGNMENT OPERATORS
    // Constructors are used to CREATE an object of a class.
    // Eg. Word w2 = w1;
    //  Assignment operators are used to assign the value of one EXISTING object to another EXISTING object.
    // Eg. w2 = w1;

    // Destructor : ~Word w;
    ~Word()
    {
        delete[] word;
    }

    // Accessor for length :
    // Word w("hello") ; size_t len = w.length(); // len will be 5
    size_t length() const // with "const" at the end, member function promises not to change any member variables (size or word) of the object it's called on.
                          // so can use it on const objects or non-const objects !
    {
        return size;
    }

    // When you return a value (not a pointer or a reference) from a function, like size_t length() const is doing, you're returning a copy of the value.
    //  ^^ Will never be able to modify w in the example above, only len.

    // for more complex types, like arrays or strings, returning a copy can be expensive.
    // In these cases, you can return a pointer or a reference to the value instead of the value itself.
    // This way, you're not copying the value, you're just returning a reference to it.
    // This is more efficient, but it also means that the value you're returning can be changed by the caller, which can lead to bugs.
    // To prevent this, you can return a const pointer or a const reference, which means that the value can't be changed by the caller.

    // Accessor for C-style string :
    // Word w("hello"); char *str = w.c_str();  // str now points to the string "hello"
    const char *c_str() const
    {
        return word;
    }
    //

    // Mutator methods :
    // Word w("hello"); w.changeWord(w2);
    void changeWord(const Word &newWord) // function does not return any value (void)
    {
        delete[] word;                     // delete the word that is already there
        word = new char[newWord.size + 1]; // allocate memory for the new word
        size = newWord.size;               // set the size of the new word
        strcpy(word, newWord.word);        // copy the new word into the word variable
    }

    // Word w("hello"); w.changeWord("world");
    void changeWord(const char *newWord)
    {
        delete[] word;
        word = new char[strlen(newWord) + 1];
        size = strlen(newWord);
        strcpy(word, newWord);
    }

    // Concatenation method
    Word concat(const Word &other, const char *delimiter = " ") const
    {
        size_t newSize = size + strlen(delimiter) + other.size;
        char *newWord = new char[newSize + 1];
        strcpy(newWord, word);
        strcat(newWord, delimiter);
        strcat(newWord, other.word);
        return Word(newWord);
    }

    // Comparison method
    bool isLess(const Word &other) const
    {
        return strcmp(word, other.word) < 0; // if word is lexicographically less than other.word, return a negative number and therefore, true
    }

    // Method to get the n'th character
    char at(size_t n) const // which index to get the character from (starts at 0!)
    {
        if (n < size) // if index is within the bounds of the word
        {
            return word[n];
        }
        throw out_of_range("Index out of range");
    }

    // Method to read from an input stream
    void read(istream &in) // isStream is a reference to an input stream
    {
        char temp[100];        // temporary array of characters to store the input
        in.getline(temp, 100); // get the input from the input stream, 100 characters at most
        changeWord(temp);      // change the word to the input
    }

    // Overloaded insertion operator
    // friends are functions or classes that have access to the private members of a class.
    // Necessary because they need to access the word member variable
    friend ostream &operator<<(ostream &out, const Word &input) // first parameter is where word will be printed, second parameter is the word to be printed
    {
        out << input.word;
        return out;
    }

    // Word w("hello");
    // cout << w << :endl;
    //  Prints "hello"

    // Overloaded extraction operator
    friend istream &operator>>(istream &in, Word &input) // first paramter is where the word will be read from, second parameter is the word to be read
    {
        char temp[100];         // temporary array of characters to store the input
        in >> temp;             // get the input from the input stream
        input.changeWord(temp); // change the word to the input
        return in;              // return the input stream
    }

    // Word w;
    // cout << "Enter a word: ";
    // cin >> w;  // Reads a word from the standard input into w
    // cout << "You entered: " << w << std::endl;
};