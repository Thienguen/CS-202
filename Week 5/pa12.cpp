/// @file "pa12.h"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 2/16/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment 
/// @note People who helped: TA Jordan
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <sstream>

#include "Container.h"

//------------------------------------------------------------

TEST_CASE("default constructor") {
    // got a new container
    const Container container;

    // if container is empty and nothing inside, it's a new one
    CHECK(container.empty() == true);
    CHECK(container.size() == 0);
    
}

//------------------------------------------------------------

TEST_CASE("Constructor::(copy)") {
    // declare 2 container
    Container container_1{ 1, 2, 3, 4, 5 };

    // using copy constructor
    Container container_2 = container_1;

    // using copy =' make a shallow copy
    // container_2 = container_1;

    // checks if the size()(s) are equal
    CHECK(container_1.size() == container_2.size());
}

//------------------------------------------------------------

TEST_CASE("Constructor::(init") {
    // declare 2 container
    Container container_1{ 1, 2, 3, 4, 5 };
    Container container_2{ 1, 2, 3, 4, };
    // checks if the size()(s) are equal
    CHECK(container_1.size() != container_2.size());
}

//------------------------------------------------------------

TEST_CASE("Container::empty()") {
    // newly created so emtpy for sure
    Container container;
    // check if the new container is empty
    CHECK(container.empty() == true);
}

//------------------------------------------------------------

TEST_CASE("Container::size()") {
    // declare 2 container
    Container container_1{ 1, 2, 3, 4, 5 };
    Container container_2{ 1, 2, 3, 4, 5 };
    // checks if the size()(s) are equal
    CHECK(container_1.size() == container_2.size());
}

//------------------------------------------------------------

TEST_CASE("Container::pushback()") {
    // declare container
    Container container_1{ 0, 1, 2, 3, 4, 5 };
    Container container_2{ 0, 1, 2, 3, 4, 5, 6, 7 };

    // size() < capacity so size able to do 7
    container_1.push_back(8);
    CHECK(container_1.size() == 7);

    // if the used == capacity then size() is now 9
    container_2.push_back(8);
    CHECK(container_2.size() == 9);
}

//------------------------------------------------------------

TEST_CASE("Container::erase() and Container::find()") {
    std::ostringstream output;              // declared output,
    Container erased{ 0, 1, 2, 3, 4, 5 };   // and erase container
    int *pos = erased.find(2);              // a pointer to the element
                                            // we want to erase
    // just ordinary erased container before being erase
    write(output, erased);
    CHECK(output.str() == "{0,1,2,3,4,5}");

    // set it back to empty
    output.str(" ");

    // erase 1 element
    erased.erase(pos);
    write(output, erased);
    CHECK(output.str() == "{0,1,3,4,5}");
}

//------------------------------------------------------------

TEST_CASE("Container::find()") {
    std::ostringstream output;              // declared output,
    Container erased{ 0, 1, 2, 3, 4, 5 };   // and erase container
    int *pos = erased.find(2);              // a pointer to the element
                                            // we want to erase

    // erase 1 element
    output.str(" ");
    erased.erase(pos);
    write(output, erased);
    CHECK(output.str() == "{0,1,3,4,5}");

}


//------------------------------------------------------------

TEST_CASE("Container::clear()") {
    Container container_1{ 0, 1, 2, 3, 4, 5 };  // declare container

    container_1.clear();    // call the clear function
                            // and check
    CHECK(container_1.size() == 0);
    CHECK(container_1.empty() == true);
}

TEST_CASE("find(const value_type&, pointer)") {
    Container box1 { 42, 65, 66, 67, 42, 68, 69, 42 };

    CHECK(box1.find(42) == box1.begin());
    CHECK(box1.find(42, box1.begin() + 1) == box1.begin() + 4);
    CHECK(box1.find(42, box1.begin() + 5) == box1.begin() + 7);
    CHECK(box1.find(73) == box1.end());
}

//------------------------------------------------------------

TEST_CASE("Container::swap()") {
    // std::cout or output
    std::ostringstream output;
    // declare container
    Container container_1{ 0, 1, 2, 3, 4, 5 };
    Container container_2{ 0, 1, 2, 3, 4, 5, 6, 7 };

    // swaping two container content
    container_1.swap(container_2);

    // write the content
    output.str(" ");
    write(output, container_1);
    CHECK(output.str() == "{0,1,2,3,4,5,6,7}");

    // write the content
    output.str(" ");
    write(output, container_2);
    CHECK(output.str() == "{0,1,2,3,4,5}");
}

//------------------------------------------------------------

TEST_CASE("Container::equal") {
    // declare container
    Container container_1{ 0, 1, 2, 3, 4, 5 };
    Container container_2{ 0, 1, 2, 3, 4, 5, 6, 7 };
    Container container_3{ 0, 1, 2, 3, 4, 5 };

    // the first two is different
    CHECK(equal(container_1, container_2) == false);

    // the 1 and 3 are the same
    CHECK(equal(container_1, container_3) == true);
}

//------------------------------------------------------------

TEST_CASE("Container::write") {
    // std::cout or output
    std::ostringstream output;
    // declare container
    Container container_1{ 0, 1, 2, 3 };
    Container container_2{ 0, 1, 2, 3, 4, 5, 6, 7 };

    // write the content
    output.str(" ");
    write(output, container_1);
    CHECK(output.str() == "{0,1,2,3}");

    // write the content
    output.str(" ");
    write(output, container_2);
    CHECK(output.str() == "{0,1,2,3,4,5,6,7}");

}

//------------------------------------------------------------

