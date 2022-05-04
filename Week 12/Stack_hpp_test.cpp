#include "List.hpp"

template <class T>
class Stack : protected List<T> {
public:
    // member types
    using value_type = T;
    using reference  = T&;

    reference top()    { return List<T>::front(); }
    bool empty() const { return List<T>::empty(); }
    void push(const value_type& value)  
                               { List<T>::insert(List<T>::begin(), value); }
    void pop() { if (!empty()) { List<T>::erase(List<T>::begin()); }       }
};


/// ouput our linked list
/// @param output pass by reference to output
/// @param list the list contain the data
template <class T>
std::ostream& operator<<(std::ostream& output, Stack<T> stack);

/// @paragraph This function will write ouput the entire stack
template <class T>
std::ostream& operator<<(std::ostream& output, Stack<T> stack)
{
    std::string separator[2]{};

    output << "top -> ";

    while (!stack.empty()) 
    {
        std::cout << *separator << stack.top();
        stack.pop();
        *separator = " -> ";
        if (stack.empty())
        {
            output << " -> ";
        }
    }
    return output << "nullptr";
}


int main(int argc, char* argv[])
{
    Stack<char*> stack1 {};
    Stack<char*> stack2 {};
    Stack<int>   stack3 {};

    for ( ; *argv; ++argv) 
    {
        stack1.push(*argv);
        stack3.push(--argc);
    }

    std::cout << "stack1: " << stack1 << '\n';
    std::cout << "stack2: " << stack2 << '\n';
    std::cout << "stack3: " << stack3 << "\n\n";

    while (!stack1.empty()) 
    {
        stack2.push(stack1.top());
        stack1.pop();
    }

    std::cout << "stack1: " << stack1 << '\n';
    std::cout << "stack2: " << stack2 << std::endl;

    return EXIT_SUCCESS;
}

// // top of a stack
// template <class T>
// typename Stack<T>::reference Stack<T>::top()
// {
//     // return empty() ? throw std::logic_error("top") : List<T>::front();
//     return List<T>::front();
// }

// template <class T>
// bool Stack<T>::empty() const
// {
//     return List<T>::empty();
// }

// template <class T>
// void Stack<T>::push(const value_type& value)
// {
//     List<T>::insert(List<T>::begin(), value);
// }

// template <class T>
// void Stack<T>::pop()
// {
//     List<T>::erase(List<T>::begin());
// }