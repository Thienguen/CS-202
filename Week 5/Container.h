/// @file "Container.h"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 2/16/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment 
/// @note People who helped: TA Miguel
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// define CONTAINER_H when computer don't know it yet
#ifndef CONTAINER_H
#define CONTAINER_H

#include <cassert>
#include <iostream>
#include <ostream>
#include <utility>
#include <algorithm>
#include <initializer_list>

/// A Container stores a set of values The storage of the 
/// Container is handled automatically, being expanded as needed.

class Container {
public:
    /// Member types.
    using value_type    = int;
    using size_type     = std::size_t;
    using pointer       = value_type*;
    using const_pointer = const value_type*;
    
    // #ifdef DEBUG
    // Container& operator= (const Container& rhs) = delete;
    // #endif

    // default/ parameterized constructor
    Container(size_type count = 0) 
    : capacity(count), used(0) { data = new int[count]; }

    /// Copy ctor.
    Container(const Container& other);
    
    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// Destructor.
    ~Container();
    
    /// Checks if the container has no elements, e.g begin() == end()
    /// @returns true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }
    
    /// Returns the number of elements in the container.
    size_type size() const { return used; };
    
    /// Returns a pointer to the first element.
    pointer begin() { return data; }
    const_pointer begin() const { return data; }
    
    /// Returns a pointer to the end (the element following the last element).
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }
    
    /// Adds an element to the end.
    void push_back(const value_type& value);
    
    /// Removes a single item from the container.
    void erase(pointer pos);
    
    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() { used = 0; };

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);
    
    /// Finds the first element equal to the given target. 
    /// Search begins at pos. 
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type& target, pointer pos = nullptr);

    const_pointer find(const value_type& target, pointer pos = nullptr) const ;
    
private:
    size_type capacity;  ///< Physical capacity of container.
    size_type used;      ///< Number of items in container.
    pointer   data;      ///< Array of items.
};

// related non-member functions

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
bool equal(const Container& lhs, const Container& rhs);

/// Performs stream output on Containers, using "{1,2,3}" format.
void write(std::ostream& output, const Container& container);


#endif 

/* CONTAINER_H */