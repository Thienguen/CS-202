/// @file pa11.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 2/5/2022
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment create a Catch unit test
/// @note People who helped:
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <sstream>

#include "Bag.h"
#include "Bag.h"

#include "Set.h"
#include "Set.h"

/// 1 TEST CASE that test everything, i hope.

TEST_CASE(" Test case 1 ") {
    // variable declaration(s)
    std::ostringstream output;
    Bag bag;
    Set set;
    // TEST Set class with insert function
    bag.clear();

    bag.insert(1);
    CHECK(bag.count(1) == 1);

    bag.write(output);
    CHECK(output.str() == "{1}");

    // repeat
    output.str(" ");
    set.insert(1);
    set.insert(1);
    bag.write(output);
    CHECK(output.str() == "{1}");
}


TEST_CASE("Test case") {
    // variable declaration(s)
    std::ostringstream output;
    Bag bag;
    Set set;
    output.str(" ");

    // TEST 10 items in the bag
    for (int i = 1; i < 11; i++) {
        bag.insert(i);
    }

    // result
    bag.write(output);
    CHECK(output.str() == "{1,2,3,4,5,6,7,8,9,10}");
    CHECK(bag.empty() == false);

    // result should be {} after clear
    bag.clear();
    output.str(" ");
    bag.write(output);
    CHECK(output.str() == "{}");
    CHECK(bag.empty() == true);

    // TEST 1 item in the bag
    bag.insert(1);
    output.str(" ");
    bag.write(output);
    bag.clear();
    CHECK(output.str() == "{1}");

    // erase one
    bag.insert(1);
    bag.insert(2);
    bag.insert(3);

    // try to erase an non-existent value
    CHECK(bag.count(42) == 0);
    CHECK(bag.erase_one(42) == false);
    CHECK(bag.size() == 3);

    // try to erase a known value
    CHECK(bag.erase_one(1) == true);
    CHECK(bag.count(2) == 1);
    CHECK(bag.size() == 2);
}

TEST_CASE("Set::insert()") {
    const auto HALF = Set::CAPACITY / 2;

    Set set;

    for (Set::size_type i = 1; i <= HALF; ++i) {
        set.insert(static_cast<Set::value_type>(i));
        set.insert(static_cast<Set::value_type>(i));
        CHECK(set.count(static_cast<Set::value_type>(i)) == 1);
    }

}



/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------


