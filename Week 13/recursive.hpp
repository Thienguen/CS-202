#ifndef RECURSIVE_HPP
#define RECURSIVE_HPP

// a silly implementation of * printing
void print2(int n, int i);
void pattern2(unsigned n);
void print2_version2(unsigned n);

// pa15 assignm,ent
void   pattern(unsigned n);
double power(double base, int exp);

namespace cs202
{   // namespace cs202
template <class Iter> size_t size(Iter first, Iter last);
template <class Iter, class T> size_t count(Iter first, Iter last, const T& value);
template <class Iter, class T> auto sum(Iter first, Iter last, T init) -> decltype(init);
template <class Iter> Iter smallest(Iter first, Iter last);
template <class Iter> Iter largest(Iter first, Iter last);
template <class Iter> void sort(Iter first, Iter last);
template <class Iter> void fprint(Iter first, Iter last);
template <class Iter> void rprint(Iter first, Iter last);
}

/// --------------------------------------------------
///     @note Functions definition -
/// --------------------------------------------------

/// @paragraph first approach?
/// EFFECT: return the size of the container
// template <class Iter>
// size_t cs202::size(Iter first, Iter last)
// {
//     size_t count = 0;
//     while (first != last)
//     {
//         ++first;
//         ++count;
//     }
//     return count;
// }

/// @paragraph second approach
/// EFFECT: return the size of the container
template <class Iter>
size_t cs202::size(Iter first, Iter last)
{
    size_t size_var = 0;

    if (first == last) {
        return size_var;
    }
    else {
        return 1 + cs202::size(++first, last);
    }
}

/// @paragraph first approach?
/// EFFECT: return counts and returns the number
///         of occurrences of value within the range
// template <class Iter, class T>
// size_t cs202::count(Iter first, Iter last, const T& value)
// {
//     size_t count = 0;
//     while (first != last)
//     {
//         if (*first == value) { ++count; }
//             else { ++first; }
//     }
//     return count;
// }

/// @paragraph second approach
/// EFFECT: return counts and returns the number
///         of occurrences of value within the range
template <class Iter, class T>
size_t cs202::count(Iter first, Iter last, const T& value)
{
    if (first == last) {
        return 0;
    }
    else if (*first == value)
    {
        return 1 + cs202::count(++first, last, value);
    }
    else
    {
        return cs202::count(++first, last, value);
    }
}

/// @paragraph another approach
/// EFFECT: return counts and returns the number
///         of occurrences of value within the range
// template <class Iter, class T>
// size_t cs202::count(Iter first, Iter last, const T& value)
// {
//     if (first == last)
//     {
//         return 0;
//     }
    
//     auto next = first;

//     return size_t {*first == value ? 1 : 0} + cs202::count(++next, last, value);
// }

/// @paragraph return the sum of a range of elements
/// @param first iterator to the first element in the range
/// @param last iterator to the last element in the range
/// @return the sum of the elements in the range
template <class Iter, class T>
auto sum(Iter first, Iter last, T init) -> decltype(init) 
{
    if (first == last) {
        return init;
    }

    auto next = first;

    if (++next == last) {
        return *first;
    }

    return *first + sum(next, last, *first);
}

template <class Iter>
Iter cs202::smallest(Iter first, Iter last)
{   // empty range and 1 element
    if (first == last) {
        return last;
    }
    else if (size(first, last) == 1) {
        return first;
    }

    Iter temp = first;
    if (*first < *smallest(++temp, last))
    {
        return first;
    }
    else {
        return smallest(temp, last);
    }
}

/// @paragraph second approach
/// @param first iterator to the first element in the range
/// @param last iterator to the last element in the range
/// EFFECT: return the smallest element in the range
// template <class Iter>
// Iter cs202::smallest(Iter first, Iter last)
// {   // empty range and 1 element
//     if (first == last) return last;

//     auto next = first;

//     if (++next == last) return first;

//     const auto min_value = cs202::smallest(next, last);

//     if (*first < min_value) return first;
//     else return min_value;
// }

/// @paragraph second approach
/// @param first iterator to the first element in the range
/// @param last iterator to the last element in the range
/// EFFECT: return the largest element in the range
template <class Iter>
Iter cs202::largest(Iter first, Iter last)
{   // empty range and 1 element
    if (first == last) {
        return last;
    }
    else if (size(first, last) == 1) {
        return first;
    }

    Iter temp = first;
    if (*first > *largest(++temp, last))
    {
        return first;
    }
    else {
        return largest(temp, last);
    }
}

/// @paragraph second approach
/// @param first iterator to the first element in the range
/// @param last iterator to the last element in the range
/// EFFECT: return the largest element in the range
// template <class Iter>
// Iter cs202::largest(Iter first, Iter last)
// {   // empty range and 1 element
//     if (first == last) return last;

//     auto next = first;

//     if (++next == last) return first;

//     const auto max_value = cs202::largest(next, last);

//     if (*first > max_value) return first;
//     else return max_value;
// }

template <class Iter>
void cs202::sort(Iter first, Iter last)
{
    if (first == last) {
        return;
    }

    // smallest first occurence in the range
    Iter smol = smallest(first, last);
    // swap the smallest with the first element
    std::swap(*first, *smol);

    // auto temp   =  *first;
    //     *first  =  *smol;
    //     *smol   =  *temp;

    // sort the rest of the range
    cs202::sort(++first, last);
}

template <class Iter>
void cs202::fprint(Iter first, Iter last)
{
    if (first == last) {
        return;
    }
    else
    {
        std::cout << *first << " ";
        fprint(++first, last);
    }
}

template <class Iter>
void cs202::rprint(Iter first, Iter last)
{
    if (first != last)
    {   // temp so we won't derefencing nullptr
        Iter temp = first;
        rprint(++temp, last);
        std::cout << *first << " ";
    }
}

/// NOTES: Non-namespace functions definitions
/// --------------------------------------------------
/// --------------------------------------------------

/// @paragraph first approach
/// EFFECT: print the * pattern
void pattern(unsigned n)
{
    char star = '*';
    // base case
    if (n == 0)
        return;
    // general case
    // recursively calling printn()
    else {
        pattern(n - 1);
        std::cout << std::string(n, '*') << std::endl;
    }

    // using a for loop, I'm a sinner
    // for (unsigned i = 0; i < n; i++)
    // {
    //     std::cout << "*";
    // }
    // std::cout << "\n";
}


/// @paragraph first approach
/// EFFECT: return the power of base to exp
double power(double base, int exp)
{
    // general case
    if (exp > 0)
    {   // non-zero value of base
        return base * power(base, exp - 1);
    }
    else if (exp < 0)
    {   // negative value of exp
        return 1 / power(base, -exp);
    }
    else
    {   // base case
        return 1.0;
    }
}

/// @paragraph second approach
/// EFFECT: return the power of base to exp
// double power(double base, int exp)
// {
//     assert(!base == 0.0 && exp = 0);

//     if (exp == 0) return 1.0;

//     if (exp < 0)
//     {
//         assert(exp <= INT_MAX);
//         return 1.0 / power(base, -exp);
//     }

//     return base * power(base, exp - 1);
// }

// /// @paragraph second approach
// /// EFFECT: print the * pattern
// // function to print a row
// void pattern2(unsigned n)
// {
//     // base case
//     if (n == 0)
//         return;

//     // general case
//     // recursively calling printn()
//     pattern2(n - 1);
//     std::cout << "* ";
// }

// // function to print the pattern
// void pattern2_version2(unsigned n)
// {
//     if (n == 0)
//     {
//         std::cout << '\n';
//         return;
//     }
//     std::cout << '*';
//     pattern2_version2(n - 1);
// }

// /// @paragraph third approach
// /// EFFECT: print the * pattern
// // function to print a row
// void pattern2(unsigned n)
// {
//     void line(unsigned n);

//     if (n) {
//         pattern2(n - 1);
//         pattern2_version2(n);
//     }
// }

/// @paragraph second approach
/// EFFECT: print the * pattern
// void pattern(unsigned n)
// {
//     if (n > 0)
//     {
//         pattern(n - 1);
//         std::cout << std::string(n, '*') << std::endl;
//     }
// }

#endif /* EOF */