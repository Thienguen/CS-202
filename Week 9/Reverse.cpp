/// @note This simple program reverse a singly linked list
/// @date 3/18/2022
/// @author Thien Nguyen

// include libs, I have everything within powa now
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>

struct Node 
{
    int data;
    struct Node *next;
};

// construct this 
Node *head = nullptr;

Node* reverse(Node *head) 
{
    Node *current, *prev, *next;
    current = head;
    prev    = nullptr;
    next    = nullptr;

    while (current != nullptr) 
    {
        next            = current->next;
        current->next   = prev;
        prev            = current;
        current         = next;
    }
    head = prev;
    return head;
}

// only append 1 in here
Node* Insert(Node *head, int data)
{
    // create the node and allocate the memory for its
    /// @note this is C, don't use it here or even think
    ///       of using malloc
    // Node *temp = (struct Node*)malloc(sizeof(struct Node));

    // only 1 so this hold the nullptr
    // at the end it will point to tail
    // it holds the data but also, point to
    // nullptr
    auto temp = new Node {data, nullptr};

    // temp->data = data;
    // temp->next = nullptr;

    // if this is our beginning of the list
    if (head == nullptr) {
        head = temp;
    } else {
        Node *temp1 = head;
        while (temp1->next != nullptr) {
            temp1 = temp1->next;
        }
            temp1->next = temp;
    }
    return head;
}

// To check our program 
void printnodes(Node *head) {
    std::cout << "\nThis is the code { ";
    while(head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "}";
}

void destroy(Node *head)
{
    auto current = nullptr;
    std::cout << "The memory being allocated is being destroy,"
              << " so no memory leak occure.\n\n";
    while (head != nullptr)
    {
        current = head;
        head    = head->next;
        delete    current;
    }
}

int main() {

    Node *head = nullptr;
    Node *current = nullptr;

    head = Insert(head, 4);
    head = Insert(head, 2);
    head = Insert(head, 6);
    head = Insert(head, 10);
    head = Insert(head, 8);

    current = head;
    printnodes(head);
    std::cout << " before reverse the list \n";
        
    head = reverse(head);
    printnodes(head);
    std::cout << " after reverse the list \n\n";

    destroy(head);
    // return to the OS
    return 0;
}

// this is bad, don't put it in main
// -=--------=--------=--------=-------
//         std::cout << "{";
// while (current != nullptr) {
//     if (current->next == nullptr) {
//         std::cout << current->data;
//         current = current->next;
//     } else {
//         std::cout << current->data << ",";
//         current = current->next;
//     }
// }
//         std::cout << "}";
// -=--------=--------=--------=-------