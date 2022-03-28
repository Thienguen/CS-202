/// @file Container.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 2/20/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment
/// @note People who helped: TA William
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

#include "Container.h"

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

// helper function copy for easier for everything
static void copy(const int *first, const int *const last, int *dest);

/// Copy constructor
Container::Container(const Container& other)
    : Container(other.size()) {
    copy(other.begin(), other.end(), begin());  // copy all the elements
    used = other.size();
}

/// Initializer List constructor
Container::Container(const std::initializer_list<value_type>& init)
    : Container(init.size()) {
    // copy all the elements from init.begin() to init.end() to data
    copy(init.begin(), init.end(), begin());
    used = init.size();

    // data = new int[init.size()];
    // capacity = init.size();
    // used = init.size();
}

/// Destructor.
Container::~Container() {
    // Dynamically delete the array we allocated earlier
    delete [] data;
    data       = nullptr;
    used       = 0;
    capacity   = 0;
}

/// Adds an element to the end.
void Container::push_back(const value_type& value) {
    // variable declaration(s)
    pointer data_2;

    // if the array is at its maximum capacity
    if (used == capacity) {
        // make a new dynamic array of sufficient size (capacity +8)
        pointer data_2 = new value_type[capacity += 8] ;
        // auto pointer data_2 { new value_type[capacity += 8] {} };

        // copy elements from data to new temp array
        copy(begin(), end(), data_2);

        // delete the old data array
        delete [] data;

        // reassign data pointer to the temp array
        data = data_2;
    }

    // increment used to take everything back
    *(data + used) = value;
    used++;

    // a different version of increment used to take everything back
    // *(data + used++) = value;
}

/// Removes a single item from the container.
void Container::erase(pointer pos) {
    // if pos is not empty
    if (pos != nullptr) {
        // assert pos still in range
        assert(begin() <= pos && pos < end());
        // overwrite the useless element to the end - 1
        copy(pos + 1, end(), pos);
        --used;
    }
}

/// Exchanges the contents of the container with those of other.
/// @param other
void Container::swap(Container& other) {
    size_type temp_capacity;  ///< Physical capacity of container.
    size_type temp_used;      ///< Number of items in container.
    pointer   temp_data;      ///< Array of items.

    // swap the capcity of the container with those of other
    temp_capacity      = capacity;
    capacity           = other.capacity;
    other.capacity     = temp_capacity;

    // swap the used of the container with those of other
    temp_used          = used;
    used               = other.used;
    other.used         = temp_used;

    // swap the data of the container with those of other
    temp_data          = data;
    data               = other.data;
    other.data         = temp_data;
}

/// Finds the first element equal to the given target.
/// Search begins at pos.
/// @returns pointer to the element if found, or end() if not found.
Container::pointer Container::find(const value_type& target, pointer pos) {
    // // start the pos at begin()
    // if (pos == nullptr) {
    // }
    //     // assert if pos is still in range
    //     pointer p = end();
    //     assert(pos >= begin() && pos < end());

    //     // loop till the end();
    //     while (pos != end()) {
    //         // if it's the value we need, take it
    //         if (*pos == target) {
    //             p = pos;
    //         } else {
    //             // increment the position
    //             pos++;
    //         }
    //     }
    //         pos = begin();
    // return p;

// ------------------------------------------------------------
    // start the pos at begin()
    pointer first = pos == nullptr ? begin() : pos;
    pointer location = end();

    // assert if pos is still in range
    assert(first >= begin() && first < end());
    
    // loop till the end();
    while (first != location) {
        // if it's the value we need, take it
        if (*first == target) {
            location = first;
        } else {
        // increment the position
            ++first;
        }
    }
        return location;
}

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
bool equal(const Container& lhs, const Container& rhs) {
    // bool variable to check T/F whether lhs & rhs equal or not
    bool valid = false;

    // iterator go through lhs & rhs
    Container::const_pointer j = lhs.begin();
    Container::const_pointer k = rhs.begin();

    if (lhs.size() == rhs.size()) {
        valid = true;

        // if not at the end() of the container
        // since end() always pased the container by 1 in address
        while (j < lhs.end() && valid == true) {
            // comparing value at the address being pointed to
            if (*j == *k) {
                valid = true;
            } else {
                valid = false;
            }

            // iterate through the container
            ++j;
            ++k;
        }
    }

    // Container::const_pointer fisrt1 = lhs.begin();
    // Container::const_pointer last1 = lhs.end();
    // Container::const_pointer first2 = rhs.begin();

    // bool result = rhs.size() == lhs.size();

    // while (result && first1 != last1) {
    //     result = *first1 ++ == *first2++;
    // }
    // return result

    return valid;
}

/// Performs stream output on Containers, using "{1,2,3}" format.
void write(std::ostream& output, const Container& container) {
    // seperator do be reset after each loop
    char sep[2] = "";
    output << '{';

    // print the content of the container
    for (Container::value_type i : container) {
        output << sep << i;
        *sep = ',';
    }

    output << '}';
}

// definition of the helper function copy
static void copy(const int *first, const int *const last, int *dest) {
    // formal parameters to indicate the beginning
    // and end of the range to copy.
    while (first != last) {
        // dereference the variable dest and first
        // so increment after the value at that point
        // since it's an array it increment to the next value
        *dest++ = *first++;
    }
}

