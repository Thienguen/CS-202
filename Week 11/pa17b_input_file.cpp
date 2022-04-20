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

int main()
{
    std::ifstream fin;

    std::string input = "darkness.txt";

    List<std::string> list;

    std::string word;

    fin.open(input);

    if (fin.is_open())
    {
        while (fin >> word)
        {
            while (std::ispunct(word.front())) {
                word.erase(word.begin());
            }

            while (std::ispunct(word.back()))  {
                word.erase(word.size() - 1);
            }

            for (auto i = 0; i < static_cast<int>(word.size()); i++)
            {
                word.at(i) = static_cast<char>(std::tolower(word.at(i)));
            }

            // search if it's found, increase count
            if (std::find(list.begin(), list.end(), word) == list.end() && word != "")
            {
                if (list.empty())
                {
                    list.insert(list.begin(), word);
                }
                else if (list.front() > word)
                {
                    list.insert(list.begin(), word);
                }
                else if (list.back() < word)
                {
                    list.insert(list.end(), word);
                }
                else
                {
                    auto     i = list.begin()->next;
                    bool valid = true;

                    while (valid)
                    {
                        if (word < i->data)
                        {
                            list.insert(i, word);
                            valid = false;
                        }
                        else { i = i->next; }
                    }

                }

            }
        }

        auto temp = list.begin();

        char separator[2] {};

        std::cout << "\nFORWARD ORDER\n---------------\n";

        int count = 1;

        for (auto c = temp ; c != nullptr; ++c)
        {
            *separator = '\n';

            std::cout << std::setw(2)
                      << count   << ". "
                      << *c << separator;

            ++count;

            if (c->next == nullptr)
            {
                --count;

                std::cout << "\nREVERSE ORDER\n---------------\n";

                for (auto back = c; back != nullptr; back = --back)
                {
                    *separator = '\n';

                    std::cout << std::setw(2)
                              << count      << ". "
                              << *back << separator;

                    --count;
                }
            }
        }
    }

    fin.close();

    list.clear();

    return EXIT_SUCCESS;
}
