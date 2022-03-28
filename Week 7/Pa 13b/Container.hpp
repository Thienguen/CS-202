/// @file "Container.h"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/3/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment using template and putting definitions
///         as well as the prototypes of Container in here
/// @note People who helped: TA Miguel, TA Chris
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// define CONTAINER_H when computer don't know it yet
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cassert>
#include <iostream>
#include <ostream>
#include <utility>
#include <initializer_list>
#include <stdexcept>

/// A Container stores a set of values The storage of the
/// Container is handled automatically, being expanded as needed.

template <class T>
class Container {
public:
    /// Member types.
    // value type is what kind of type store , value at the position
    // size type is positional
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    // default/ parameterized constructor
    Container(size_type count = 0)
        : capacity(count), used(0) {
        data = new T[count];
    }

    /// Copy ctor.
    Container(const Container &other);

    /// Move ctor
    Container(Container &&other);

    /// Initializer List ctor
    Container(const std::initializer_list<value_type> &init);

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
    void push_back(const value_type &value);

    /// Removes a single item from the container.
    void erase(pointer pos);

    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() { used = 0; };

    /// Exchanges the contents of the container with those of other.
    void swap(Container &other);

    /// Finds the first element equal to the given target.
    /// Search begins at pos.
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type &target, pointer pos = nullptr);

    const_pointer find(const value_type &target, pointer pos = nullptr) const;

    // ------------------------------------------------------------
    /// @paragraph /include within pa13/ /include within pa13b/
    // ------------------------------------------------------------

    /// Replaces the contents of the container with a copy of the contents of rhs.
    Container &operator=(const Container &rhs);

    /// Move assignment
    Container &operator=(Container &&rhs);

    /// Returns other appended to this.
    /// @returns this
    Container &operator+=(const Container &other);

private:
    size_type capacity; ///< Physical capacity of container.
    size_type used;     ///< Number of items in container.
    pointer data;       ///< Array of items.
};

// ==========================================================================
/// @paragraph Prototypes overloading function non-member of class Container
// ==========================================================================

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
template <class T>
[[deprecated]]
bool equal(const Container<T>& lhs, const Container<T>& rhs);

// / Performs stream output on Containers, using "{1,2,3}" format.
template <class T>
[[deprecated]]
void write(std::ostream& output, const Container<T>& container);

/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

// ========================================================================
            /// @paragraph prototypes static function - nonmember
// ========================================================================

/// helper function copy for easier for everything;
/// Copies the elements in the range defined by [first,last) to another
/// range beginning at d_first. The elements are copied in forward order.
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer d_first);

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2);

/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
template <class T>
static typename Container<T>::pointer find(
       typename Container<T>::pointer first,
       typename Container<T>::pointer last,
 const typename Container<T>::value_type&
       value);

template<class T>
static void swap(T& a, T& b);
            // ====================================================
            /// @paragraph out-of-line member function definitions
            // ====================================================

/// Copy constructor
template <class T>
Container<T>::Container(const Container<T>& other)
    : Container<T>(other.size()) {
    ::copy<T>(other.begin(), other.end(), begin());  // copy all the elements
    used = other.size();
}

/// Move ctor
template <class T>
Container<T>::Container(Container<T>&& other)
    : capacity(other.capacity), used(other.used), data(other.data) {
    // leave other in a stable state
    other.data = nullptr;
    other.capacity = other.used = 0;
}

/// Initializer List constructor
template <class T>
Container<T>::Container(const std::initializer_list<value_type>& init)
    : Container<T>(init.size()) {
    // copy all the elements from init.begin() to init.end() to data
    ::copy<T>(init.begin(), init.end(), begin());
    used = init.size();

    // data = new int[init.size()];
    // capacity = init.size();
    // used = init.size();
}

/// Destructor.
template <class T>
Container<T>::~Container() {
    // Dynamically delete the memory we allocated earlier
    delete[] data;
    data = nullptr;
    used = 0;
    capacity = 0;
}

/// Adds an element to the end.
template <class T>
void Container<T>::push_back(const value_type& value) {
    // // variable declaration(s)
    // pointer data_2 = nullptr;
    // if the array is at its maximum capacity
    if (used == capacity) {
        // make a new dynamic array of sufficient size (capacity +8)
        pointer data_2 = new value_type[capacity += 8];
        // auto data_2 { new value_type[capacity += 8] {} };

        // copy elements from data to new temp array
        copy<T>(begin(), end(), data_2);

        // delete the old data array
        delete[] data;

        // reassign data pointer to the temp array
        data = data_2;
    }

    // // increment used to take everything back
    *(data + used) = value;
    ++used;

    // a different version of increment used to take everything back
    // *(data + used++) = value;
}

/// Removes a single item from the container.
template <class T>
void Container<T>::erase(pointer pos) {
    // if pos is not empty
    if (pos != nullptr) {
        // assert pos still in range
        assert(begin() <= pos && pos < end());
        // overwrite the useless element to the end - 1
        copy<T>(pos + 1, end(), pos);
        --used;
    }
}

/// Exchanges the contents of the container with those of other.
/// @param other
template <class T>
void Container<T>::swap(Container<T>& other) {
    // size_type temp_capacity; ///< Physical capacity of container.
    // size_type temp_used;     ///< Number of items in container.
    // pointer temp_data;       ///< Array of items.

    // // swap the capcity of the container with those of other
    // temp_capacity = capacity;
    // capacity = other.capacity;
    // other.capacity = temp_capacity;

    // // swap the used of the container with those of other
    // temp_used = used;
    // used = other.used;
    // other.used = temp_used;

    // // swap the data of the container with those of other
    // temp_data = data;
    // data = other.data;
    // other.data = temp_data;

    // take two parameter of type T, no matter what T might be
    ::swap(capacity, other.capacity);
    ::swap(used,     other.used    );
    ::swap(data,     other.data    );
}

/// Finds the first element equal to the given target.
/// Search begins at pos.
/// @returns pointer to the element if found, or end() if not found.
template <class T>
typename Container<T>::pointer Container<T>::find(const value_type& 
                                                  target, pointer pos) {
    // start the pos at begin() if it's nullptr
    pointer first = pos == nullptr ? begin() : pos;
    pointer location = end();

    return ::find<T>(first, location, target);
}

        // ------------------------------------------------------------
        /// @paragraph Overloading operator definitions (members)
        // ------------------------------------------------------------

/// Replaces the contents of the container with a copy of the contents of rhs.
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    // guard against self-assignment
    if (this != &rhs) {
        // 1. deallocate any memory that Container is using internally
        delete[] data;
        data = nullptr;
        used = 0;
        capacity = 0;

        // 2. allocate memory to hold the contents of rhs
        // 2.5. account for resize just in case
        data = new Container::value_type[rhs.capacity];
        used = rhs.size();

        // 3. copy the values from rhs into this instance
        copy<T>(rhs.data, rhs.data + rhs.size(), data);

        // std::copy(rhs.data, rhs.end(), data);
    }

    // 4. return *this
    return *this;
}

/// Move assignment
/// @param rhs syntax using && to reassign pointer to class private
template <class T>
Container<T>& Container<T>::operator=(Container<T>&& rhs) {
    if (this != &rhs) {
        delete[] data;

        // take ownership if rhs contents
        data     = rhs.data;
        capacity = rhs.capacity;
        used     = rhs.used;

        // leave the donor in a stable state
        rhs.data     = nullptr;
        rhs.capacity = rhs.used;
    }

    // return the TRUTH
    return *this;
}

/// Returns other appended to this.
/// @returns this
template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& other) {
    /// @paragraph this is why we don't use push_back in assignment operator
    /// @paragraph ? start off w the empty container it then resize it to 8
    /// copy that element from the (possibbly bigger) array then continue to        
    /// make another one right next to it lead to another
    /// empty container - resize then copy again again and again.
    /// do this to a milions of elements is wasting --> seg fault

    // ------------------------------------------------------------
    // // 1. push back the values from rhs into this instance
    // for (const_pointer i = other.begin(); i < other.end(); i++) {
    //     push_back(*i);
    // }
    // ------------------------------------------------------------

    // allocate the memory
    auto copy_data = new value_type[size() + other.size()];

    // copy the array to the new data
    ::copy<T>(begin(), end(), copy_data);

    // delete old data
    // assigning ownership of data to the copydata new chunk of memory
    delete[] data;

    // assign it to the new copy
    data = copy_data;

    // update the capacity
    capacity = size() + other.size();

    ::copy<T>(other.begin(), other.end(), end());

    // update the capacity
    used = capacity;

    // 2. return *this
    return *this;
}

// ------------------------------------------------------------
/// @paragraph Overloading operator definitions (NON-MEMBERS)
// ------------------------------------------------------------

/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    // using equal function we wrote down below
    return ::equal<T>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    // opposite of equal is !equal
    // return !::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    return !(lhs == rhs);
}

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) {

    /// @paragraph explanation for shortcut of operator+
    // ------------------------------------------------------------
    // create a new object that hold two set container
    // also set it equal to the lhs
    // Container total = lhs;

    // using the overloading operator +=
    // total += rhs;

    // return the object
    // return total;
    // ============================================================

    // this is an annonymus type
    // Container(lhs) is a left value due
    // to its being a soon be delete temp array
    // right value is unassignable (left side) in the assignment operator,
    return Container<T>(lhs) += rhs;
}

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {
    /// @paragraph in pa13b the write function is deprecated
    // ------------------------------------------------------------
    // using write function to write this <<
    // write(output, oset);
    // return output;
    // ============================================================

    // seperator do be reset after each loop
    char sep[2] = "";
    output << '{';

    // print the content of the container
    for (auto& i : oset) {
        output << sep << i;
        *sep = ',';
    }
    // end the array
    return output << '}';
}

// ========================================================================
            /// @paragraph defnition - static nonmember functions
// ========================================================================

/// Copies the elements in the range defined by [first,last) to another
/// range beginning at d_first. The elements are copied in forward order.
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer d_first) {
    // formal parameters to indicate the beginning
    // and end of the range to copy.
    while (first != last) {
        // dereference the variable dest and first
        // so increment after the value at that point
        // since it's an array it increment to the next value
        *d_first++ = *first++;
    }
}

/// Returns true if the range [first1,last1) is equal to the range
/// [first2,last2) and false otherwise.
template <class T>
static bool equal(typename Container<T>::const_pointer first1,
                  typename Container<T>::const_pointer last1,
                  typename Container<T>::const_pointer first2,
                  typename Container<T>::const_pointer last2) {
    // comparing the range of element between two set of array
    bool result = (last1 - first1) == (last2 - first2);

    // if result is true,
    while (result && first1 != last1) {
        result = *first1++ == *first2++;
    }

    // return THE TRUTH
    return result;
}

/// Checks the contents of lhs and rhs are equal, that is, they have the same
/// number of elements and each element in lhs compares equal with the element
/// in rhs at the same position.
template <class T>
bool equal(const Container<T>& lhs, const Container<T>& rhs) {
    // bool variable to check T/F whether lhs & rhs equal or not
    bool valid = false;

    // iterator go through lhs & rhs
    auto j = lhs.begin();
    auto k = rhs.begin();

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
    return valid;
}

template <class T>
/// Performs stream output on Containers, using "{1,2,3}" format.
void write(std::ostream& output, const Container<T>& container) {
    // seperator do be reset after each loop
    char sep[2] = "";
    output << '{';

    // print the content of the container
    for (auto& i : container) {
        output << sep << i;
        *sep = ',';
    }

    output << '}';
}


/// Returns a pointer to the first element in the range [first,last) that
/// compares equal to value, or last if no such element found.
template <class T>
static typename Container<T>::pointer find(
       typename Container<T>::pointer first,
       typename Container<T>::pointer last,
       const typename Container<T>::value_type&
       value) {
    // run through the loop
    // if it's the value we need, terminate the loop
    // increment through range of the array
        while (first != last) { if (*first == value) { last = first; } else { ++first; } }
        // the location of the target being either found or last which is garbage
        return last;
}

/// template class T swap function definitions 
template< class T >
static void swap(T& a, T& b) {
    // temp object type T 
    T temp;

    // simple math
    temp = a;
    a = b;
    b = temp;
}

#endif /* CONTAINER_HPP */
