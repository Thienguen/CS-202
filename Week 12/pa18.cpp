/// @file "pa18.cpp"
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

#include "Stack.hpp"

int main(int argc, char *argv[]) {
    // variables declarations(s)
    Stack<char *> stack {};
    std::string  input;

    // we only allow two argument
    if (argc == 2) 
    {
        // sweet
        input = argv[1];

        // this will help us check the top of the stack
        char top;

        // flag control
        bool valid  = true;

        // LCV
        int  length = input.length();

        // where the errors occurs
        int  count  = 0;

        for (size_t i = 0; i < length && valid == true; i++)
        {   // non - so special cases
            if (input[i] == '{'  || input[i] == '[' || input[i] == '<')
            {
                stack.push(&input[i]);
                count++;
            }
            else if (input[i] == '}' || input[i] == ']' || input[i] == '>')
            {   // if not empty, mean there is something to check
                if (!stack.empty())
                {   // for better view
                    top = *stack.top();
                    if ((top == '{' && input[i] == '}')
                    ||  (top == '[' && input[i] == ']')
                    ||  (top == '<' && input[i] == '>'))
                    {
                        stack.pop();
                        count++;
                    }
                    else if (top != input[i])
                    {   // if the bracket is not corresponding to the input
                        valid = false;
                    }
                }
            }
            else if (input[i] == '(')
            {   // not go out of range, and the next one is " * "
                if (i < length - 1 && input[i + 1] == '*')
                {   // we treat '(*' as one character
                    // stack.push('*');
                    stack.push(&input[i + 1]);
                    i++;
                    count++;
                }
                else 
                {   // it just an ordanary '('
                    stack.push(&input[i]);
                    count++;
                }
            }
            else if (input[i] == '*')
            {   // don't go out of range, and the next closing bracket is ')'
                if (i < length - 1 && input[i + 1] == ')')
                {
                    if (*stack.top() == '*')
                    {   // we only take the star, so we also only pop the '*'
                        stack.pop();
                        i++;
                        count++;
                    }
                    else { valid = false; }
                }
                else { count++; }  // well...it just a '*' in the middle, useless!
            }
            else if (input[i] == ')')
            {   // ordinary ')'
                if (*stack.top() == '(')
                {
                    stack.pop();
                    count++;
                }
                else { valid = false; }  // it doens't match!
            }
            else { count++; }   // something else not brackets, go to the next input[i]
        }

        if (valid == true && stack.empty())
        {
            std::cout << "YES" << std::endl;
        }
        else if (!stack.empty() && valid)
        {   // since it start from 0, or I should have set it to 1 when declare
            std::cout << "NO " << count + 1 << std::endl;
        }
        else
        {
            std::cout << "NO " << count + 1 << std::endl;
        }
    } 
    else 
    {   // input!, input!, input!
        std::cout << "\nUsage: " << argv[0] << " <EXPRESSO>\n" << std::endl;
    }

    return EXIT_SUCCESS;
}

