#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node { int data; Node *next; };

void Linklist(Node *ptr) 
{
    // linked 1,2,3 together and we sorta have 1-2-3
    while (ptr != nullptr)
    {
    cout << ptr->data << endl;
    ptr  = ptr->next;
    cout << &ptr << endl;
    }

}

int main() {
    struct Node *head;
    struct Node *second;
    struct Node *third;
    
    head   = new Node;
    // cout << &head;
    second = new Node;
    // cout << &second;
    third  = new Node;
    // cout << &third;
    
    // cout   << &head   << endl;
    // cout   << &second << endl;
    // cout   << &third  << endl;

    head->data   = 1;
    head->next   = second;
    
    second->data = 2;
    second->next = third;
    
    third->data  = 3;
    third->next  = nullptr;
    
    Linklist(head);
}