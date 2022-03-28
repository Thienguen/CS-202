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
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    // create a varibale bag type bag class we made
    Bag bag;

    // check it with empty function
    bag.clear();

    // if it returns 1 then the bag is empty
    cout << " \n Test: The bag have 0 item" << endl;
    cout << '\n' << bag.empty() << " (True) The bag is empty" << endl;
    cout << "------------------------------";
    /// -----------------------------------------------------------------------
    // insert 1 items into the bag
    bag.clear();
    bag.insert(1);
    // black box test
    cout << " \n Test: The bag only have 1 item \n" << endl;
    cout << bag.empty() << " (False) The bag is not empty \n" << endl;
    cout << bag.size() << " --> There is 1 item in the bag \n" << endl;
    // the result
    bag.write();
    cout << "\n------------------------------";
    /// -----------------------------------------------------------------------
    // insert 20 items
    bag.clear();

    for (int i = 0; i < Bag::CAPACITY; i++) {
        bag.insert(i);
    }

    // black box test
    cout << " \n Test: The bag have 20 items \n" << endl;
    cout << bag.empty() << " (False) The bag is not empty \n" << endl;
    cout << bag.size() << " --> There is 20 items in the bag \n" << endl;

    // the result
    bag.write();
    cout << "------------------------------\n" << endl;

    // testing count and erase one function
    bag.clear();
    // insert 3 value into the data
    bag.insert(1);
    bag.insert(2);
    bag.insert(3);

    // try to erase an non-existent value
    assert(bag.count(4) == 0);
    assert(bag.erase_one(4) == false);
    assert(bag.size() == 3);

    // try to erase a known value
    assert(bag.erase_one(1) == true);
    assert(bag.count(2) == 1);
    assert(bag.size() == 2);

    // this statement will only execute if the asserts above pass
    cout << __FUNCTION__ << " passed\n";
    // return to the operating system
    return EXIT_SUCCESS;
}


