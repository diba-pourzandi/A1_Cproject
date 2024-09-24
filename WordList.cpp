#include "WordList.h"

// Default constructor : WordList list; initializing head and tail to nullptr and size to 0. This is an empty list.
WordList::WordList() : head(nullptr), tail(nullptr), size(0) {}

// Copy constructor : WordList list1(list2); &other here is a reference to list2, so we are copying the head, tail, and size of list2 into the NEW head, tail, and size variables of list1
WordList::WordList(const WordList &other) : WordList() // the second WordList() is calling the default constructor to initialize the new list
{
    for (Node *node = other.head; node != nullptr; node = node->next) // starts at the head of the other list, goes through each node (node = node->next is the expression that is executed after each iteration of the loop. It moves the node pointer to the next node in the list) till nullptr
    {
        push_back(node->word); // uses the push_back function to add the word from the other list to the new list
    }
}

// Move constructor : WordList list1(move(list2)); && is an rvalue reference == binds to a temporary value that will be destroyed after the move constructor is called (means list2 will be destroyed after the move constructor is called)
WordList::WordList(WordList &&other) noexcept : head(other.head), tail(other.tail), size(other.size) // head, tail, and size of the new list (list1) are set to the head, tail, and size of the other list (list2)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

// Copy assignment operator : WordList list1 = list2;
WordList &WordList::operator=(const WordList &other)
{
    if (this != &other) // if list 1 is not list 2
    {
        WordList copy = other; // create a list called copy that holds the other list / list 2
        swap(*this, copy);     // insert list 2 into list 1
    }
    return *this; // return list 1
}

// Move assignment operator : WordList list1 = move(list2);
WordList &WordList::operator=(WordList &&other) noexcept
{
    if (this != &other) // if list 1 is not list 2
    {
        swap(head, other.head); // swap the head of list 1 with the head of list 2
        swap(tail, other.tail);
        swap(size, other.size);
    }
    return *this; // return list 1
}

// Destructor
WordList::~WordList()
{
    while (!isEmpty())
    {
        pop_front(); // while the list is not empty, remove the first word
    }
}

// Return the length of the list
size_t WordList::length() const
{
    return size;
}

// Check if the list is empty
bool WordList::isEmpty() const
{
    return size == 0; // if size is 0, then give true (empty), else give false (not empty)
}

// Return the first word in the list
Word &WordList::front()
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty");
    }
    return head->word; // return word member of the head node
}

// Return the last word in the list
Word &WordList::back()
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty");
    }
    return tail->word; // return word member of the tail node
}

// Add a word to the front of the list
void WordList::push_front(const Word &word)
{
    Node *node = new Node(word, head, nullptr);
    if (head != nullptr) // if the head is not nullptr, which means the list is not empty
    {
        head->prev = node; // the previous of the current head node is set to the new node
    }
    head = node;         // else, the head pointer of the list is updated to the new node
    if (tail == nullptr) // if the list is empty
    {
        tail = node; // tail is set to the new node
                     // this means both head and tail are pointing to the new node, as it is the only node in the list
    }
    size++; // increment the size of the list
}

// Add a word to the back of the list
// eg. list.push_back(Word("dog")); // add at the end
void WordList::push_back(const Word &word)
{
    Node *node = new Node(word, nullptr, tail); // (the word new node will hold, next node set null here because will be the last pointer, previous node will be set to the current tail node)
    if (tail != nullptr)                        // if the tail is not nullptr, which means the list is not empty
    {
        tail->next = node; // -> accesses the member of the object pointing (accesses the next pointer of the tail node and sets it to the new node). New node becomes end of the list.
                           // For example, if you have a pointer p that points to an object of a class that has a member m, you can access m through p using the -> operator like this: p->m.
    }
    tail = node;         // else, the tail pointer of the list is updated to the new node, as the new node is now the last node in the list.
    if (head == nullptr) // if the list is empty
    {
        head = node; // head is set to the new node
                     // this means both head and tail are pointing to the new node, as it is the only node in the list
    }
    size++; // increment the size of the list
}

// Remove and return the first word in the list
Word WordList::pop_front()
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty");
    }
    Node *node = head;      // creates a pointer node that points to the first node in the list (head)
    Word word = node->word; // creates a word object that holds the word of the first node since we wil be deleting the node !!
    head = node->next;      // updates the head pointer to the next node in the list
                            // this means the first node is no longer in the list
    if (head != nullptr)    // If the list is not empty after removing the first node
    {
        head->prev = nullptr; // this line sets the prev pointer of the new first node to nullptr
    }
    else
    {
        tail = nullptr; // tail is set to nullptr as there are no nodes in the list
    }
    delete node; // deletes the first node
    size--;      // decrements the size of the list
    return word; // returns the word that was in the first node
}

// Remove and return the last word in the list
Word WordList::pop_back()
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty");
    }
    Node *node = tail;      // create a pointer node that points to the last node in the list (tail)
    Word word = node->word; // grab the word from the last node
    tail = node->prev;      // the previous node becomes the new tail effectively removing the last node
    if (tail != nullptr)    // if list not empty
    {
        tail->next = nullptr; // next of this new tail is set to nullptr
    }
    else
    {
        head = nullptr; // if list is empty, head is set to nullptr
    }
    delete node; // can now delete the last node
    size--;
    return word;
}

// Insert a word in sorted order : WordList list; list.insertSorted(Word("cat"));
void WordList::insertSorted(const Word &word)
{
    if (isEmpty() || word <= head->word) // if the list is empty or the word is less than or equal to the first word in the list
    {
        push_front(word); // add the word to the front of the list
    }
    else if (word >= tail->word) // if the word is greater than or equal to the last word in the list
    {
        push_back(word);
    }
    else // if the word is in the middle of the list
    {
        Node *current = head;                                          // new node current is set to the head of the list
        while (current->next != nullptr && current->next->word < word) // loop that while not at end of list and word we want to insert is greater than the current word
        {
            current = current->next; // move to the current pointer to the next node
                                     // So when the loop stops, current points to the node whose word is less than the word to be inserted. The next node (current->next) is the first node whose word is not less than the word to be inserted.
        }
        // make new node with new word and insert it into the list
        Node *node = new Node(word, current->next, current); //  next node of the new node is the next node of the current node, and previous node of the new node is the current node
        // change pointers of existing nodes to include new node
        current->next->prev = node; // the previous node of the next node of the current node is set to the new node
        current->next = node;       // the next node of the current node is set to the new node
        size++;
    }
}

// Remove a word from the list
bool WordList::remove(const Word &word)
{
    Node *node = search(word); // search for the word in the list
    if (node == nullptr)
    {
        return false;
    }
    if (node->prev != nullptr) // if not at beginning
    {
        node->prev->next = node->next; // the next of the previous node is set to the next of the current node
    }
    else // if at beginning
    {
        head = node->next; // the head is set to the next of the current node
    }
    // if not at end
    if (node->next != nullptr)
    {
        node->next->prev = node->prev; // the previous of the next node is set to the previous of the current node
    }
    else // if at end
    {
        tail = node->prev; // the tail is set to the previous of the current node
    }
    delete node;
    size--;
    return true;
}

// Fetch the word at the specified index
Word WordList::fetchWord(int index) const // eg. list.fetchWord(2);
{
    Node *node = getWord(index); // get the node at the specified index
    if (node == nullptr)
    {
        throw std::runtime_error("Index out of range");
    }
    return node->word; // return the word of the node
}

// Print the list with n words per line
void WordList::print(ostream &os, int n) const // eg. list.print(cout, 5);
{
    Node *current = head;      // pointer to the head of the list
    int count = 0;             // counter to keep track of the number of words printed
    while (current != nullptr) // as long as the current node is not nullptr
    {
        os << current->word << ' '; // print the word of the current node
        if (++count % n == 0)       // if the number of words printed is a multiple of n (eg . 5, 10, 15, etc.)
        {
            os << '\n'; // print a newline
        }
        current = current->next; // move to the next node
    }
    if (count % n != 0) // if the number of words printed is not a multiple of n (not equal to 5, 10, 15, etc.)
                        // write this and not simply "/n" because if the last line is a multiple, they've already printed a newline
    {
        os << '\n'; // print a newline
    }
}

// Search for a word in the list
WordList::Node *WordList::search(const Word &word) const
{
    Node *current = head; // pointer to the head of the list
    while (current != nullptr)
    {
        if (current->word == word) // if the word of the current node is equal to the word we are searching for
        {
            return current; //  return the current node
        }
        current = current->next; // else move to the next node
    }
    return nullptr; // if empty list or word not found
}

// Get the node at the specified index
WordList::Node *WordList::getWord(int n) const
{
    if (n >= size)
    {
        throw std::runtime_error("Index out of range");
    }
    Node *current = head;       // pointer to the head of the list
    for (int i = 0; i < n; i++) // loop through the list until the specified index
    {
        current = current->next;
    }
    return current; // return the node at the specified index
}

// Overloaded insertion operator
ostream &operator<<(ostream &os, const WordList &list)
{
    for (WordList::Node *node = list.head; node != nullptr; node = node->next) // loop through the list
    {
        os << node->word << ' '; // print the word of the current node
    }
    return os;
}

bool WordList::lookup(const Word &word) const
{
    return search(word) != nullptr; // if the word is found in the list, return true, else return false
}
