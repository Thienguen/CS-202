/// @file Bag.cpp
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

#include "Bag.h"

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Inserts an item into the bag.
/// Internally, the items are not maintained in any particular order.
/// @pre size() < CAPACITY
/// @param value Element value to insert.
void Bag::insert(const value_type& value) {
    // assert the boundary
    assert(size() < CAPACITY);
    // stored and count the total used array member
    data[used++] = value;

}

/// If target was in the bag, then one copy has been removed;
/// otherwise the bag is unchanged.
/// Internally, the items are not maintained in any particular order.
/// @param target Key value of the items to remove.
/// @return true if one copy was removed; false if nothing removed.
bool Bag::erase_one(const value_type& target) {
    // create a bool type so it won't stuck in calling the fucntion again
    // which --> recurrsion?
    bool valid = false;

    // remove the target and replace the final member
    for (size_type i = 0; !valid && i < size(); ++i) {
        if (data[i] == target) {
            data[i] = data[--used];
            valid = true;
        }
    }

    // return T/F if we find the items or not
    return valid;
}

/// Returns the number of items equal to the target.
/// @param target Key value of the item(s) to count.
/// @returns Number of items with value equal to the target.
Bag::size_type Bag::count(const value_type& target) const {
    // variable declaration(s)
    size_type counting = 0;

    // go through the data[0] -> data[used - 1]
    for (size_type i = 0; i < size(); ++i) {
        if (data[i] == target) {
            ++counting;
        }
    }
    // return the answer we found
    return counting;
}

/// Writes all items to an output stream in the format: {42,73,0,-59,7}
/// @param output The output stream (defaults to std::cout).
void Bag::write(std::ostream& output) const {
    if (used <= CAPACITY) {
        // if the bag have only 1 item
        if (size() == 1) {
            output << "{" << data[0] << "}";
        }

        // if the bag have multiple items
        if (size() > 1) {
            output <<  "{";

            for (size_type i = 0; i < size() - 1; i++) {
                output << data[i] << ",";
            }

            output << data[used - 1] << "}" << '\n';
        }
    }
}
