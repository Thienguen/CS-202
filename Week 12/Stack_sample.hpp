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

    reference top()    { return this->front(); }
    
    bool empty() const { return List<T>::empty(); }
    // using List<T>::empty;

    void push(const value_type& value) { List<T>::insert(List<T>::begin(), value); }
    // void push(const value_type& value) { this->insert(this->begin(), value) }
    
    void pop() { if (!empty()) { List<T>::erase(List<T>::begin()); } }
    // void pop() { if (!empty()) { this->erase(this->begin()); } }
    // void pop() { this->erase(this->begin()); }
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
