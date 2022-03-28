#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <sstream>

#include "Bag.h"

#include "Set.h"

//------------------------------------------------------------

TEST_CASE("default constructor") {
    // got a new bag
    const Bag bag;

    // if bag is empty and nothing inside, it's a new one
    CHECK(bag.empty() == true);
    CHECK(bag.size() == 0);
}

//------------------------------------------------------------

TEST_CASE("Bag::size()") {
    // declare a new Bag
    Bag bag;

    // check the maximum capacity of our bag
    for (Bag::size_type i = 1; i <= Bag::CAPACITY; ++i) {
        bag.insert(static_cast<Bag::value_type>(i));
        CHECK(bag.size());    
        }
}

//------------------------------------------------------------

TEST_CASE("Bag::empty()") {
    // a new bag
    Bag bag;

    // if nothing inside return true, otherwise...
    CHECK(bag.empty() == true);
    bag.insert(69);
    CHECK(bag.empty() == false);

}

//------------------------------------------------------------

TEST_CASE("Bag::insert()") {
    // 20 is out of the 80 char limit so HALF
    const auto HALF = Bag::CAPACITY / 2;

    // a new bag
    Bag bag;    

    // insert twice of the same value and the bag receive both of them
    for (Bag::size_type i = 1; i <= HALF; ++i) {
        bag.insert(static_cast<Bag::value_type>(i));
        bag.insert(static_cast<Bag::value_type>(i));
        CHECK(bag.count(static_cast<Bag::value_type>(i)) == 2);
    }
}

//------------------------------------------------------------

TEST_CASE("erase_one") {
    // a new bag
    Bag bag;

    // insert some random values
    bag.insert(1);
    bag.insert(2);
    bag.insert(3);

    // try to erase an non-existent value
    CHECK(bag.count(69) == 0);
    CHECK(bag.erase_one(69) == false);
    CHECK(bag.size() == 3);

    // try to erase a known value
    CHECK(bag.erase_one(1) == true);
    CHECK(bag.count(2) == 1);
    CHECK(bag.size() == 2);

}

//------------------------------------------------------------

TEST_CASE("Bag::clear") {
    // a new bag
    Bag bag;

    for (Bag::value_type i = 1; i <=5; ++i) {
        for (int j = 0; j < i; ++j) {
            bag.insert(i);
        }
        CHECK(bag.count(i) == static_cast<Bag::size_type>(i));
    }

}

//------------------------------------------------------------

TEST_CASE("Bag::write()") {
    std::ostringstream output;

    // a new bag;
    Bag bag;
    // an empty bag
    bag.write(output);
    CHECK(output.str() == "{}");

    output.str(" ");
    // insert some random values
    bag.insert(1);
    bag.insert(2);
    bag.insert(3);

    bag.write(output);
    CHECK(output.str() == "{1,2,3}");
}

//------------------------------------------------------------

TEST_CASE("Set::insert()") {
    const auto HALF = Set::CAPACITY / 2;

    // a variable of the new set derived class we just wrote
    Set set;

    for (Set::size_type i = 1; i <= HALF; i++) {
        set.insert(static_cast<Set::value_type>(i));
        set.insert(static_cast<Set::value_type>(i));
        CHECK(set.count(static_cast<Set::value_type>(i)) == 1);
    }

}

