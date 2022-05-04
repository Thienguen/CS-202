/// @file "pa18.cpp"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/27/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment test brackets for Stack.hpp, I wrote this 
///         the morning before we submit the assignment, bravo me
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

#include "Stack.hpp"


int main() 
{
    Stack<char*> stack {};
    std::string  input = "(*(++it) (*))";
    int length = input.length();

    char top;

    bool valid = true;

    int  count = 0;

        for (size_t i = 0; i < length && valid == true; i++)
        {
            if (input[i] == '{'  || input[i] == '[' || input[i] == '<')
            {
                stack.push(&input[i]);
                count++;
            }
            else if (input[i] == '}' || input[i] == ']' || input[i] == '>')
            {
                if (!stack.empty())
                {
                    top = *stack.top();
                    if ((top == '{' && input[i] == '}')
                    ||  (top == '[' && input[i] == ']')
                    ||  (top == '<' && input[i] == '>'))
                    {
                        stack.pop();
                        count++;
                    }
                    else if (top != input[i])
                    {
                        valid = false;
                    }
                }
            }
            else if (input[i] == '(')
            {
                if (i < length - 1 && input[i + 1] == '*')
                {
                    // stack.push('*');
                    stack.push(&input[i + 1]);
                    i++;
                    count++;
                }
                else 
                {
                    stack.push(&input[i]);
                    count++;
                }
            }
            else if (input[i] == '*')
            {
                if (i < length - 1 && input[i + 1] == ')')
                {
                    if (*stack.top() == '*')
                    {
                        stack.pop();
                        i++;
                        count++;
                    }
                    else { valid = false; }
                }
                else { count++; }
            }
            else if (input[i] == ')')
            {
                if (*stack.top() == '(')
                {
                    stack.pop();
                    count++;
                }
                else { valid = false; }
            }
            else { count++; }
        }

        if (valid == true && stack.empty())
        {
            std::cout << "YES" << std::endl;
        }
        else if (!stack.empty() && valid)
        {
            std::cout << "NO " << count + 1 << std::endl;
        }
        else
        {
            std::cout << "NO " << count + 1 << std::endl;
        }

    return EXIT_SUCCESS;
}

