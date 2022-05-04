/// @file pa15-test.cxx
/// @author Kevin Mess <kevin.mess@csn.edu>
/// @date 2022-04-30
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Catch2 Unit tests for recursive functions.

#include <algorithm>
#include <array>
#include <cmath>
#include <forward_list>
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "recursive.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// constant definitions
const std::array<int, 0>     EMPTY{};
const std::array<int, 5>     A  { 1, 2, 3, 4, 5 };
const char                   C[]{ '1', '2', '3', '4', '5' };
const std::forward_list<int> F  { 1, 2, 3, 4, 5 };
const std::list<int>         L  { 1, 2, 3, 4, 5 };
const std::string            S  { "12345" };
const std::vector<int>       V  { 1, 2, 3, 4, 5 };

// ----------------------------------------------------------------------------

TEST_CASE("void pattern(unsigned n)") {
    const auto expected = std::array<std::string, 6> {
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

// ----------------------------------------------------------------------------

TEST_CASE("double power(double base, int exp)") {
    for (double b = -10.0; b < 10.0; b += 0.5) {
        for (int e = -5; e < 5; ++e) {
            if (b != 0.0 && e != 0) {
                CHECK(power(b, e) == Approx( std::pow(b, e) ));
            }
        }
    }
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> size_t size(Iter first, Iter last)") {
    CHECK(cs202::size(EMPTY.begin(), EMPTY.end()) == 0);
    CHECK(cs202::size(A.begin(), A.end()) == 5);
    CHECK(cs202::size(C, C + 5) == 5);
    CHECK(cs202::size(F.begin(), F.end()) == 5);
    CHECK(cs202::size(L.begin(), L.end()) == 5);
    CHECK(cs202::size(S.begin(), S.end()) == 5);
    CHECK(cs202::size(V.begin(), V.end()) == 5);
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter, class T> \
size_t count(Iter first, Iter last, const T& value)") {
    std::array<unsigned, 15>    a  { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    char                        c[]{ "122333444455555" };
    std::forward_list<unsigned> f  { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    std::list<unsigned>         l  { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    std::string                 s  { "122333444455555" };
    std::vector<unsigned>       v  { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };

    CHECK(cs202::count(EMPTY.begin(), EMPTY.end(), 42) == 0);

    for (unsigned i = 0; i <= 5; ++i) {
        CHECK(cs202::count(a.begin(), a.end(), i) == i);
        CHECK(cs202::count(c, c + 15, static_cast<char>(i + '0')) == i);
        CHECK(cs202::count(f.begin(), f.end(), i) == i);
        CHECK(cs202::count(l.begin(), l.end(), i) == i);
        CHECK(cs202::count(s.begin(), s.end(), static_cast<char>(i + '0')) == i);
        CHECK(cs202::count(v.begin(), v.end(), i) == i);
    }
}

// ----------------------------------------------------------------------------

#ifdef TESTSUM
TEST_CASE("template <class Iter, class T> \
auto sum(Iter first, Iter last, T init) -> decltype(init)") {
    CHECK(sum(EMPTY.begin(), EMPTY.end(), 0) == 0);
    CHECK(sum(EMPTY.begin(), EMPTY.end(), 42) == 42);
    CHECK(sum(A.begin(), A.end(), 0) == 15);
    CHECK(static_cast<unsigned char>(sum(C, C + 5, 0)) == 255);
    CHECK(sum(F.begin(), F.end(), 0) == 15);
    CHECK(sum(L.begin(), L.end(), 0) == 15);
    CHECK(static_cast<unsigned char>(sum(S.begin(), S.end(), 0)) == 255);
    CHECK(sum(V.begin(), V.end(), 0) == 15);

    std::vector<std::string> syllables{"ab", "ra", "ca", "da", "bra"};
    CHECK(sum(syllables.begin(), syllables.end(), std::string{}) == "abracadabra");
}
#endif

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> Iter smallest(Iter first, Iter last)") {
    CHECK(cs202::smallest(EMPTY.begin(), EMPTY.end()) == EMPTY.end());
    CHECK(*cs202::smallest(A.begin(), A.end()) == 1);
    CHECK(*cs202::smallest(C, C + 5) == '1');
    CHECK(*cs202::smallest(F.begin(), F.end()) == 1);
    CHECK(*cs202::smallest(L.begin(), L.end()) == 1);
    CHECK(*cs202::smallest(S.begin(), S.end()) == '1');
    CHECK(*cs202::smallest(V.begin(), V.end()) == 1);
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> Iter largest(Iter first, Iter last)") {
    CHECK(cs202::largest(EMPTY.begin(), EMPTY.end()) == EMPTY.end());
    CHECK(*cs202::largest(A.begin(), A.end()) == 5);
    CHECK(*cs202::largest(C, C + 5) == '5');
    CHECK(*cs202::largest(F.begin(), F.end()) == 5);
    CHECK(*cs202::largest(L.begin(), L.end()) == 5);
    CHECK(*cs202::largest(S.begin(), S.end()) == '5');
    CHECK(*cs202::largest(V.begin(), V.end()) == 5);
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> void sort(Iter first, Iter last)") {
    std::array<int, 0>     empty{};
    std::array<int, 5>     a1  { 5, 3, 4, 2, 1 };
    char                   c1[]{ '5', '3', '4', '2', '1' };
    std::forward_list<int> f1  { 5, 3, 4, 2, 1 };;
    std::list<int>         l1  { 5, 3, 4, 2, 1 };
    std::string            s1  { "53421" };
    std::vector<int>       v1  { 5, 3, 4, 2, 1 };

    cs202::sort(empty.begin(), empty.end());
    CHECK(std::is_sorted(empty.begin(), empty.end()));

    cs202::sort(a1.begin(), a1.end());
    CHECK(std::is_sorted(a1.begin(), a1.end()));

    cs202::sort(c1, c1 + 5);
    CHECK(std::is_sorted(c1, c1 + 5));

    cs202::sort(f1.begin(), f1.end());
    CHECK(std::is_sorted(f1.begin(), f1.end()));

    cs202::sort(l1.begin(), l1.end());
    CHECK(std::is_sorted(l1.begin(), l1.end()));

    cs202::sort(s1.begin(), s1.end());
    CHECK(std::is_sorted(s1.begin(), s1.end()));

    cs202::sort(v1.begin(), v1.end());
    CHECK(std::is_sorted(v1.begin(), v1.end()));
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> void fprint(Iter first, Iter last)") {
    const auto expected = std::string{ "1 2 3 4 5 " };
    const auto oldbuf   = std::cout.rdbuf();
    auto stream         = std::ostringstream{};

    std::cout.rdbuf(stream.rdbuf());  // both streams share one buffer

    cs202::fprint(EMPTY.begin(), EMPTY.end());
    CHECK(stream.str().empty());
    stream.str("");

    cs202::fprint(A.begin(), A.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::fprint(C, C + 5);
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::fprint(F.begin(), F.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::fprint(L.begin(), L.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::fprint(S.begin(), S.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::fprint(V.begin(), V.end());
    CHECK(stream.str() == expected);
    stream.str("");

    std::cout.rdbuf(oldbuf);
}

// ----------------------------------------------------------------------------

TEST_CASE("template <class Iter> void rprint(Iter first, Iter last)") {
    const auto expected = std::string{ "5 4 3 2 1 " };
    const auto oldbuf   = std::cout.rdbuf();
    auto stream         = std::ostringstream{};

    std::cout.rdbuf(stream.rdbuf());  // both streams share one buffer

    cs202::rprint(EMPTY.begin(), EMPTY.end());
    CHECK(stream.str().empty());
    stream.str("");

    cs202::rprint(A.begin(), A.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::rprint(C, C + 5);
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::rprint(F.begin(), F.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::rprint(L.begin(), L.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::rprint(S.begin(), S.end());
    CHECK(stream.str() == expected);
    stream.str("");

    cs202::rprint(V.begin(), V.end());
    CHECK(stream.str() == expected);
    stream.str("");

    std::cout.rdbuf(oldbuf);
}

/* EOF */

