/// @file "simple_list.cpp"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/27/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment perform simple operation on linked_list
/// @note People who helped: Kevin, and me
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

#include "simple_list.h"
#include "simple_list.h"

/// initialize an empty list, we have a list !
void list_init(Node*& first, Node*& last)
{
    // if the list is dirty, purge it
    if ( first != nullptr) {
        list_destroy(first, last);
    }
    else {
        first = nullptr;
        last  = nullptr;
    }
}

/// checks whether a list is empty
bool list_is_empty(const Node* first, const Node* last)
{
    // variable declarations(s)
    bool valid = false;

    // check the list is empty
    // if (first == nullptr) {std::cout << "list is empty bro."; valid = true;}
    if (first == nullptr)    {
        valid = true;
    }

    // return the result
    return valid;
}

/// prints a list in order using {1,2,3} format
void list_print(const Node* first, const Node* last)
{
    // print the list
    std::cout << "{";
    while (first != nullptr) {
        if (first != last)
        {
            std::cout << first->info << ',';
            first = first->link;
        } else {
            std::cout << first->info;
            first = first->link;
        }
    }
    std::cout << "}\n";
}


/// returns the number of elements (nodes) in a list
size_t list_size(const Node* first, const Node* last)
{

    // the size of it
    size_t count = 0;
    while (first != nullptr) {
        count++;
        first = first->link;
    }
    // std::cout << "There are " << count << " nodes \n";

    // return size_t count
    return count;
}

/// destroys a list
void list_destroy(Node*& first, Node*& last) {

    // we only destroy if it's something inside
    while (first != nullptr) {

        // simple traver-purge list
        Node *temp = first;
        first = first->link;
        delete temp;

        // until nothing is left, purge last
        if (first == nullptr) {
            last = nullptr;
        }
    }
}

/// accesses the front element of a list
int list_front(const Node* first, const Node* last)
{
    assert(first != nullptr);
    return first->info;
    // if (head == nullptr) { throw }
}

/// accesses the back element of a list
int list_back(const Node* first, const Node* last)
{
    assert(last != nullptr);
    return last->info;
}

/// searches a list for an item, returning true if found
bool list_search(const Node* first, const Node* last, int item)
{

    // flag control toward return statement
    bool  found   = false;
    const Node *i = first;

    // found from something
    while (i != nullptr && !found)
    {
        // if we found it
        if (i->info == item) { found = true; }
        
        // traverse to the next Node
        i = i->link;
    }
    return found;

    // if (found) { std::cout << "found it! \n"; }

    // for (const Node *i = first, i != nullptr, i = i->link)
    // { if (i->info == item) { found = true }; }
}

/// inserts an element to the beginning of a list
void list_insert_first(Node*& first, Node*& last, int item)
{

    // create a new Node, assign its link to what first is pointin
    // then assign first to that new head Node
    auto newNode  = new Node {item, first};
         first    = newNode;

    // if nothing in the list the first place, must leave the list
    // in a stable form
    if (last == nullptr) { last = newNode; }
}

/// inserts an element to the end of a list
void list_insert_last(Node*& first, Node*& last, int item)
{
    auto newNode = new Node {item, nullptr};

    if (last == nullptr)
    {
        newNode->link = first;
        first = last = newNode;
    } else {
        // last node exist and I add it to the end
        last->link = newNode;

        // then direct the pointer last to our new last Node
        last       = newNode;
    }
}

/// removes the first element from a list
void list_delete_first(Node*& first, Node*& last)
{
    // delete from somthing
    if (first != nullptr) {
        Node *temp = first;
        first = first->link;
        delete temp;

        // if delete to nothing, leave its stable so we can re-use
        if (first == nullptr) { last = nullptr; }
    }
}

/// removes the last element
void list_delete_last(Node*& first, Node*& last)
{
    if (last != nullptr)
    {
        // there goes the only node
        // || last->link == nullptr
        if (first->link == nullptr)
        {
            first = nullptr;
            last = nullptr;
        }
        else
        {
            Node *prev = first;
            // now go to the second last element
            while (prev->link->link != nullptr)
            {
                prev = prev->link;
            }
            Node *temp = last;
            last = prev;
            last->link = nullptr;
            delete temp;
        }
    }
}

/// removes the first occurrence of item from a list
void list_delete_item(Node*& first, Node*& last, int item)
{

    Node *current = first;
    Node *prev    = nullptr;

    // traverse to the second-last element, if exists
    while (current != nullptr && current->info != item)
    {
        prev    = current;
        current = current->link;
    }

    // make sure the Node exits in the list
    if (current != nullptr)
    {
        if (current == first) { first = current->link; }
            else if (current != first) { prev->link = current->link; }
        
        delete current;
    }
}

// current = head
// while current is not null and current->info is not x
//     previous = current
//     current = current->link
// if current is not null
//     if current points to the first node
//         head = current->link
//     if current does not point to the first node
//         previous->link = current->link
//     destroy the current node

/// creates of copy of the nodes from first1 to last1,
/// the copy beginning at first2 and ending at last2
void list_copy(const Node* first1, const Node* last1,
               Node*& first2, Node*& last2)
{
    // run through the loop to see we have any thing to copy
    // pointer to a const variable so it's ok to change the pointer
    // insert_last...huh
    for (const Node* i = first1; i != nullptr; i = i->link)
    {
        list_insert_last(first2, last2, i->info);
    }
}

/// @note
// When writing linked list algorithms,
// always look at special cases:

// Empty list
// List with 1 element
// Activity at the beginning of the list
// Activity at the end of the list
// Activity will not occur (ex: The item is not in the list)

