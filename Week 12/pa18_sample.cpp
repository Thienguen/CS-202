#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <ostream>
#include <iomanip>

#include "Stack.hpp"


size_t check_balance(const std::string& input);


int main(int argc, const char* argv[])
{
    using std::cout;

    int exit_code = EXIT_SUCCESS;

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>\n";
        exit_code = EXIT_FAILURE;
    }
    else
    {
        const size_t err_pos = check_balance(argv[1]);

        if (err_pos == 0)
        {
            cout << "The file " << argv[1] << " is balanced.\n";
        }
        else
        {
            cout << "The file " << argv[1] << " is not balanced.\n";
            cout << "Error at position " << err_pos << '\n';
            exit_code = EXIT_FAILURE;
        }

    return exit_code;
    }
}


size_t check_balance(const std::string& input)
{
    Stack<char> stack     {};
    bool         balance   { true };
    size_t       pos       { 1 };
    auto         current   { input.begin() };   

    for ( ; balance && current != input.end(); ++ current)
    {
        const auto next { current + 1 };

        switch (*current)
        {
            // handle the case of '('
            case '(':
                if (next != input.end() && *next == '*') { ++ current; }
                [[fallthrough]];
            case '[':
            case '{':
            case '<':
                stack.push(*current);
                break;
            
            case ')':
                balance = !stack.empty() && stack.top() == '(';
                stack.pop();
                break;
            
            case ']':
                balance = !stack.empty() && stack.top() == '[';
                stack.pop();
                break;

            case '>':
                balance = !stack.empty() && stack.top() == '<';
                stack.pop();
                break;

            case '}':
                balance = !stack.empty() && stack.top() == '{';
                stack.pop();
                break;

            case '*':
                if (next != input.end() && *next == ')') 
                {
                    balance = !stack.empty() && stack.top() == '*';
                    stack.pop();
                    ++current;
                }
                break;

            default:
                break;

            if (balance)
            {
                ++pos;
            }

        }
    }
    return balance && stack.empty() ? 0 : pos;
}