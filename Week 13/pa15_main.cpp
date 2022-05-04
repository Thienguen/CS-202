/// @file "pa15_main.cpp"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 4/25/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment test brackets for Stack.hpp
/// @note People who helped: Kevin, and me
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

/// include libs, I have everything within powa now

#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <forward_list>
#include <algorithm>

#include "recursive.hpp"

using namespace cs202;

int main() 
{

    // print(5, 1);
    // pattern(5);
    // std::cout << std::endl;
    
    // std::cout << power(2, 3);
    // std::cout << std::endl;
    
    // std::cout << power(2, 4);
    // std::cout << std::endl;
    
    // std::cout << power(2, 0);
    // std::cout << std::endl;
    
    // std::cout << power(2, -1);
    // std::cout << std::endl;
    
    // std::cout << power(2, -2);
    // std::cout << std::endl;

    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    // std::string str { "Hello world" };

    // std::cout << size(list.begin(), list.end()) << std::endl;  // prints 12
    // std::cout << size(str.begin(), str.end()) << std::endl;    // prints 11

    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    // std::string str { "Hello world" };

    // std::cout << count(list.begin(), list.end(), 42) << std::endl;  // prints 0
    // std::cout << count(list.begin(), list.end(), 5)  << std::endl;   // prints 1
    // std::cout << count(list.begin(), list.end(), 7)  << std::endl;   // prints 2
    // std::cout << count(str.begin(), str.end(), 'l')  << std::endl;   // prints 3


    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };

    // if (smallest(list.begin(), list.end()) != list.end())
    // {
    //     std::cout << *smallest(list.begin(), list.end());  // prints 0
    // }

    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    // std::string str { "Hello world" };

    // cs202::sort(list.begin(), list.end());  // list is now {0,1,2,3,4,5,6,7,7,8,9,10}
    // cs202::sort(str.begin(), str.end());    // str is now " Hdellloorw"

    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    // fprint(list.begin(), list.end());  // prints 10 2 4 7 7 9 1 0 3 8 6 5
    // std::cout << std::endl;

    // std::forward_list<int> list { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    // rprint(list.begin(), list.end());  // prints 5 6 8 3 0 1 9 7 7 4 2 10
    // std::cout << std::endl;

    return EXIT_SUCCESS;
}
