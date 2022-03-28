/// @file Set.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 2/7/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment test black box for class Set
/// @note People who helped: Miguel C helped me with the const
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

#include "Set.h"

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Inserts only unique items into the bag
/// Internally, the items are not maintained in any particular order.
/// @pre size() < CAPACITY
/// @param value Element value to insert.
void Set::insert(const value_type& value) {
    // if it's a newly found value, we call the bag function
    if (count(value) == 0) {
        Bag::insert(value);
    } 
}


