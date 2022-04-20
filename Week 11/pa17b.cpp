/// @file "pa17b.cpp"
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

#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <ostream>
#include <iomanip>

#include "List.hpp"

using namespace std;

struct entry_t 
{
    std::string word{};
    size_t count{};
};

struct WordCount : public List<entry_t>
{
    iterator insert(const string& str);
};


int main()
{
    // lambda function to print out the list
    auto header = [](const std::string& s)
    {
        std::cout << s << '\n' << std::string(s.size(), '-') << '\n';
    };

    List<std::string> list;

    std::string word;

    while (std::cin >> word)
    {
        // delete the front punctuation
        while (std::ispunct(word.front())) {
            word.erase(word.begin());
        }

        // delete the back punctuation
        while (std::ispunct(word.back()))  {
            word.erase(word.end() - 1);
        }

        // to lower case and avoid stuff
        for (auto i = 0; i < static_cast<int>(word.size()); i++)
        {
            word.at(i) = static_cast<char>(std::tolower(word.at(i)));
        }

        if (std::find(list.begin(), list.end(), word) == list.end() 
            && word != "")
        {
            if (list.empty())
            {   // the first one
                list.insert(list.begin(), word);
            }
            else if (list.front() > word)
            {   // front of the list
                list.insert(list.begin(), word);
            }
            else if (list.back() < word)
            {   // end of the list
                list.insert(list.end(), word);
            }
            else
            {   // in the middle of the list
                auto     i = list.begin()->next;
                bool valid = true;

                while (valid)
                {   // right before the node it's smaller
                    if (word < i->data)
                    {
                        list.insert(i, word);
                        valid = false;
                    }
                    else 
                        { i = i->next; }
                }
            }
        }
    }

    // print the list
    auto temp = list.begin();

    std::cout << "\nFORWARD ORDER\n-------\n";

    for (auto c = temp; c != nullptr; c++)
    {
        std::cout << *c << std::endl;
        
        if (c->next == nullptr)
        {
            std::cout << "\nREVERSE ORDER\n-------\n";

            for (auto back = c; back != nullptr; back--)
            {
                std::cout << *back << std::endl;
            }
        }
    }

    list.clear();

    return EXIT_SUCCESS;
}


/// ------------------------------------------------------------
/// ------------------------------------------------------------
/// @brief insert a new word into the list

WordCount::iterator WordCount::insert(const string& str)
{
    auto pos = WordCount::iterator{};

    if (empty() || str < front().word)
    {
        // pos = front.insert(str);
        pos = List::insert(begin(), {str, 1});
    }
    else if (str > back().word)
    {
        // pos = back.insert(str);
        pos = List::insert(end(), {str, 1});
    }
    else
    {
        for (pos = begin(); pos != end() && pos->data.word < str; ++pos) {}

        if (pos != end()) 
        {
            if (pos->data.word == str)
            {
                ++pos->data.count;
            }
            else
            {
                // pos = pos->insert(str);
                pos = List::insert(pos, {str, 1});
            }
        }
    }

    return pos;
}