/// @file "pa15.cpp"
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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <forward_list>
#include <algorithm>
#include <vector>

#include "recursive.hpp"

using namespace cs202;

TEST_CASE("void pattern(unsigned n)") {
    const auto expected = std::vector<std::string> {
        "",
        "*\n",
        "*\n**\n",
        "*\n**\n***\n",
        "*\n**\n***\n****\n",
        "*\n**\n***\n****\n*****\n"
    };
    const auto oldbuf = std::cout.rdbuf();
    auto stream = std::ostringstream{};

    std::cout.rdbuf(stream.rdbuf());  // both streams share one buffer

    for (unsigned i = 0; i <= 5; ++i) {
        pattern(i);
        CHECK(stream.str() == expected[i]);
        stream.str("");
    }

    std::cout.rdbuf(oldbuf);
}

TEST_CASE("double power(double base, int exponent)") {
    // how to basic
    CHECK(power(2,  3) == 8   );
    CHECK(power(2,  4) == 16  );
    CHECK(power(69, 0) == 1   );
    CHECK(power(2, -1) == 0.5 );
    CHECK(power(2, -2) == 0.25);

    // how to advanced
    CHECK(power(4.2, 3) == pow(4.2, 3));
    CHECK(power(3.0, 2) == 3.0 * 3.0);
    CHECK(power(9.1, 0) == 1.0);
}

TEST_CASE("int size(first, last)") {
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    CHECK(size(list.begin(), list.end()) == 12);
    CHECK(size(str.begin(), str.end())   == 11);
}

TEST_CASE("int count(first, last, value)") {
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    CHECK(cs202::count(list.begin(), list.end(), 42) == 0);
    CHECK(cs202::count(list.begin(), list.end(), 5)  == 1);
    CHECK(cs202::count(list.begin(), list.end(), 7)  == 2);
    CHECK(cs202::count(str.begin(), str.end(), 'l')  == 3);
}

TEST_CASE("smallest(first, last)") {
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    CHECK(*smallest(list.begin(), list.end()) == 0);
    CHECK(*smallest(str.begin(), str.end())   == ' ');
}

TEST_CASE("largest(first, last)") {
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    CHECK(*largest(list.begin(), list.end()) == 10);
    CHECK(*largest(str.begin(), str.end())   == 'w');
}

TEST_CASE("sort(first, last)") {
    // gonna thanks for built in CATCH2 for this
    auto list  = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    auto list2 = std::forward_list<int> { 0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10 };

    auto str   = std::string { "Hello world" };
    auto str2  = std::string { " Hdellloorw" };

    CHECK(std::is_sorted(list.begin(), list.end()) == false);

    cs202::sort(list.begin(), list.end());
    cs202::sort(str.begin(), str.end());

    CHECK(std::is_sorted(list.begin(), list.end()) == true);
    CHECK(std::is_sorted(str.begin(), str.end()) == true);

    CHECK(list == list2);
    CHECK(str  == str2);
}

TEST_CASE("fprint(first, last)") {
    // with magic, I figured how to test fprint!
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    const auto oldbuf = std::cout.rdbuf();
    auto stream = std::ostringstream{};

    std::cout.rdbuf(stream.rdbuf());  // both streams share one buffer

    cs202::fprint(list.begin(), list.end());
    cs202::fprint(str.begin(), str.end());

    std::cout.rdbuf(oldbuf);

    // it prints out every numbers and characters
    // inclduing the ' ' in the string
    CHECK(stream.str() == "10 2 4 7 7 9 1 0 3 8 6 5 H e l l o   w o r l d ");
}

TEST_CASE("rprint(first, last)") {
    // with magic, I figured how to test rprint!
    const auto list = std::forward_list<int> { 10, 2, 4, 7, 7, 9, 1, 0, 3, 8, 6, 5 };
    const auto str  = std::string { "Hello world" };

    const auto oldbuf = std::cout.rdbuf();
    auto stream = std::ostringstream{};

    std::cout.rdbuf(stream.rdbuf());  // both streams share one buffer

    cs202::rprint(list.begin(), list.end());
    cs202::rprint(str.begin(), str.end());

    std::cout.rdbuf(oldbuf);

    // it prints out every numbers and characters
    // inclduing the ' ' in the string
    CHECK(stream.str() == "5 6 8 3 0 1 9 7 7 4 2 10 d l r o w   o l l e H ");
}

