/// @file pa10.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 1/31/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment test black box for class Bag
/// @note People who helped: Miguel C helped me with the const
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>
#include <limits>
#include "Bag.h"

// setting a namcespace scope
using namespace std;

/// -----------------------------------------------------------------------
void test_constructor();
void test_size();
void test_empty();
void test_insert();
void test_erase_one();
void test_clear();
void test_count();



/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    test_constructor();
    test_size();
    test_empty();
    test_insert();
    test_erase_one();
    test_clear();
    test_count();

    // return to the operating system
    return EXIT_SUCCESS;
}

void test_constructor() {
    const Bag bag;

    assert(bag.empty() == true);
    assert(bag.size() == 0);

    cout << __FUNCTION__ << " passed\n";

}

void test_size() {
    Bag bag;
    for (Bag::size_type i = 1; i <= Bag::CAPACITY; i++) {
        bag.insert(static_cast<Bag::value_type>(i));
        assert(bag.size() == 1);
    }
    cout << __FUNCTION__ << " passed\n";
}

void test_empty() {
    Bag bag;

    assert(bag.empty() == true);
    bag.insert(19);
    assert(bag.empty() == false);

    cout << __FUNCTION__ << " passed\n";
}

void test_insert() {
    Bag bag;

    for (Bag::size_type i = 1; i <= Bag::CAPACITY; ++i) {
        bag.insert(static_cast<Bag::value_type>(i));
        assert(bag.count(static_cast<Bag::value_type>(i)) == 1); 
    }

    cout << __FUNCTION__ << " passed\n";

}


void test_erase_one() {
    Bag bag;

    bag.insert(8);
    bag.insert(4);
    bag.insert(8);

    // try to erase an non-existent value
    assert(bag.count(42) == 0);
    assert(bag.erase_one(42) == false);
    assert(bag.size() == 3);

    // try to erase a known value
    assert(bag.erase_one(8) == true);
    assert(bag.count(8) == 1);
    assert(bag.size() == 2);

    // this statement will only execute if the asserts above pass
    cout << __FUNCTION__ << " passed\n";

}


void test_clear() {
    Bag bag;

    bag.insert(8);
    bag.insert(4);
    bag.insert(8);

    assert(bag.empty() == false);
    assert(bag.size() == 3);

    bag.clear();

    assert(bag.empty() == true);
    assert(bag.size() == 0);

    cout << __FUNCTION__ << " passed\n";
}


void test_count() {
    Bag bag;

    for (int i = 1; i <= 5; ++i) {
        for (int j = 0; j < i; ++j) {
            bag.insert(i);
        }
        assert(bag.count(i) == static_cast<Bag::size_type>(i));
    }
    cout << __FUNCTION__ << " passed\n";
}



