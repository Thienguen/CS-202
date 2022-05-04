/// @file "Stack.hpp"
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

#include "List.hpp"

template <class T>
class Stack : protected List<T> {
public:
    // member types
    using value_type = T;
    using reference  = T&;

    reference top()    { return List<T>::front(); }
    bool empty() const { return List<T>::empty(); }

    void push(const value_type& value) {
        List<T>::insert(List<T>::begin(), value);
    }
    
    void pop() {
        if (!empty()) { List<T>::erase(List<T>::begin()); }
    }
};

/// ouput our linked list
/// @param output pass by reference to output
/// @param list the list contain the data
template <class T>
std::ostream& operator<<(std::ostream& output, Stack<T> stack);

/// @paragraph This function will write ouput the entire stack
template <class T>
std::ostream& operator<<(std::ostream& output, Stack<T> stack) {
    std::string separator[2] {};

    output << "top -> ";

    while (!stack.empty()) {
        std::cout << *separator << stack.top();
        stack.pop();
        *separator = " -> ";

        if (stack.empty()) {
            output << " -> ";
        }
    }

    return output << "nullptr";
}

// if ('(' || ' { ' || ' [ ')
//     stack.push(c);
// else if ( ')' || ' } ' || ' ] ')
//     if (stack.empty())
//         return false;
//     else if (stack.top() == '(' && c == ')')
//         stack.pop();
//     else if (stack.top() == '{' && c == '}')
//         stack.pop();
//     else if (stack.top() == '[' && c == ']')
//         stack.pop();
//     else
//         return false;
// else
//     return false;
// }

// (*   *)

  // A Stack List that keeps track of char values - Stack

    // Checks if there are only 2 arguments -- If{}
        // Takes the entire 2nd argument as a string - var
        // Flag variable that reads in characters - var
        // Better count variable than i - var

        // Iterates through the Expression whilst not encountering an error-- For{}
            // Inserts {, [, < 
            // Reads Closing Braces for further evaluation
                // Erases a corrsponding brace {}
                // Erases a corrsponding brace []
                // Erases a corrsponding brace <>
                // Doesn't find a corresponding brace and an error occurs
            // Reads a ( for a special case
                /* Sees if it reads a special case after intial brace and
                   Inserts special case and increase iterator reading as
                   One Character, (*  */
                // Inserts a normal (
            // Reads the special case
                /* Sees the special case is followed with a closing brace and
                   Erases special case from stack and increasing the iterator
                   Whilst being read as One Character, *)  */
                    // Doesn't find a corresponding special case and an error occurs
                // Special case isn't special
            // Reads for a closing brace without special case
                // Erases corresponding brace ()
                // Doesn't find a corresponding brace and an error occurs
            // Goes to the next iteration -- End of For{}

        // Stack is Empty and everything was read properly    -- YES
        // Everything is read properly but stack is not empty -- NO
        // Stack is not empty and an error occured somewhere  -- NO

    // No arguments or too may argumnets -- End of If{}