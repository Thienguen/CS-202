/// @file "pa17a.cpp"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/27/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment generata 2 linked list
///        then merge them by specifications
/// @note People who helped: Kevin, and me
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

/// include libs, I have everything within powa now
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>
#include <string>

#include "simple_list.h"

void generate_list(Node*& head, Node*& tail);

void list_copy_unique(const Node*  first1, const Node*  last1,
                      const Node*  first2, const Node*  last2,
                            Node*& first3,       Node*& last3);

void one_list_copy_unique(const Node*  first1, const Node*  last1,
                                Node*& first2,       Node*& last2);

int main()
{
    // you could turn this off, but I think I can call it a day
    // srand(time(0));

    // initialized all of our variables to default nullptr
    Node *head{};
    Node *tail{};

    Node *head2{};
    Node *tail2{};

    Node *head3{};
    Node *tail3{};

    std::cout << '\n' << std::string(69, '-') << '\n';

    // generating 2 allowed duplicate linked_list
    generate_list(head, tail);

    // formatted output
    std::cout << "\n";
    list_print(head, tail);
    std::cout << "\nGENERATED LIST\n" << std::string(69, '-') << '\n';

    generate_list(head2, tail2);

    // formatted output
    std::cout << "\n";
    list_print(head2, tail2);
    std::cout << "\nGENERATED LIST\n" << std::string(69, '-') << '\n';

    // copy it over but in a way
    list_copy_unique(head, tail, head2, tail2, head3, tail3);

    // formatted output
    std::cout << "\n";
    list_print(head3, tail3);
    std::cout << "\nMERGED LIST\n" << std::string(69, '-') << '\n';

    // return to the OS
    return 0;
}

/// @param head the head of our linked_list
/// @param tail the tail of our linked_list
/// @paragraph  generating a random values linked_list with range 0..100
void generate_list(Node*& head, Node*& tail)
{
    // fresh start
    list_init(head, tail);

    // generating a mid-field random value
    int num1 = rand() % 30 + 30;

    // insert that number
    list_insert_last(head, tail, num1);

    // while loop until we got enough Nodes
    while (list_size(head, tail) < 15)
    {
        int n = rand() % 100 + 1;

        // bound checking, allowed duplicates, but not too far away
        if (list_front(head, tail) >= n && n > list_front(head, tail) - 5)
        {
            list_insert_first(head, tail, n);
        }
        else if (list_back(head, tail) <= n && n < list_back(head, tail) + 5)
        {
            list_insert_last(head, tail, n);
        }
    }
}

/// @param head  the head of our linked_list
/// @param tail  the tail of our linked_list
/// @param head2 the head of our linked_list_number_2
/// @param tail2 the tail of our linked_list_number_2
/// @param head3 the head of our linked_list_number_3
/// @param tail3 the tail of our linked_list_number_3
/// @paragraph   Merge two list together to a super list/ base on specs
void list_copy_unique(const Node*  first1, const Node*  last1,
                      const Node*  first2, const Node*  last2,
                            Node*& first3,       Node*& last3)
{
    // I swear I'll write more pseudo code more, these two are pointers
    // track our journey
    const Node *iterator1 = first1;

    const Node *iterator2 = first2;

    // must be both...!- last1/2
    // before it's end of the linked list
    while (iterator1 != nullptr && iterator2 != nullptr)
    {
        // pseudo code algo
        if (list_front(iterator1, last1) == list_front(iterator2, last2))
        {
            iterator1 = iterator1->link;
        }  // if list 1 have smol value
        else if (list_front(iterator1, last1) < list_front(iterator2, last2))
        {
            if (list_search(last3, last3, iterator1->info) == false)
            {
                list_insert_last(first3, last3, iterator1->info);
            }
            iterator1 = iterator1->link;
        }  // if list 2 have smol value
        else
        {
            if (list_search(last3, last3, iterator2->info) == false)
            {
                list_insert_last(first3, last3, iterator2->info);
            }
            iterator2 = iterator2->link;
        }
    }

    // make sure it's end of both list
    while (iterator1 != nullptr)
    {
        if (list_search(last3, last3, iterator1->info) == false)
        {
            list_insert_last(first3, last3, iterator1->info);
        }
        iterator1 = iterator1->link;
    }

    while (iterator2 != nullptr)
    {
        if (list_search(last3, last3, iterator2->info) == false)
        {
            list_insert_last(first3, last3, iterator2->info);
        }
        iterator2 = iterator2->link;
    }
}

/// @paragraph purely a test
void one_list_copy_unique(const Node*  first1, const Node*  last1,
                                Node*& first2,       Node*& last2)
{
    for (const Node* i = first1; i != nullptr; i = i->link)
    {
        if (list_search(first2, last2, i->info) == false)
        {
            list_insert_last(first2, last2, i->info);
        }
    }
}
