/// @file   "pa16.cpp"
/// @author  Thien Nguyen thiennguyen@.csn.edu
/// @date    5/7/22
/// @note    I pledge my word of honor that
///          I have abided by the the CSN Academic Integrity Policy
///          while completing this assignment.
///
/// @brief   This assignment measures the time it takes
///          to search and sort various sort techniques.
/// @note    People who helped: Kevin, William, and me.
/// @cite    https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
/// @cite    https://www.geeksforgeeks.org/bubble-sort/
/// @cite    https://www.techiedelight.com/selection-sort-iterative-recursive/
/// @cite    https://www.techiedelight.com/insertion-sort-iterative-recursive/
/// @cite    https://www.techiedelight.com/merge-sort-singly-linked-list/
/// @cite    https://www.techiedelight.com/binary-search/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>
#include <iomanip>
#include <limits>
#include <climits>

using namespace std::chrono;
using iterator = std::vector<int>::iterator;

/// helper functions
template <typename Container>
void populate(Container& vec);

template <typename Container>
void again(Container& v1, Container& v2, Container& v3,
           Container& v4, Container& v5);

template <typename Container>
void formatted(Container& v1, Container& v2, Container& v3,
               Container& v4, Container& v5, int number);

/// searching functions
template <typename Container, typename T>
int linear_search(Container v, T a);

template <typename Container, typename T>
int binary_search(Container v, T a);

/// soring functions
template <typename Container>
void bubble_sort(Container& v);

template <typename Container>
void selection_sort(Container& v);

template <typename Container>
void insertion_sort(Container& v);

/// merge two containers and sort it
template <typename Container>
void merge(Container& v, Container& other, int first, int mid, int last);

template <typename Container>
void merge_sort(Container& v, Container& other, int first, int last);

/// recursion of quick sort
template <typename Container>
int partition(Container& v, int first, int last);

template <typename Container>
void quick_sort(Container& v, int first, int last);

template <typename Container>
double measure_time(Container& v, int number);

/// @paragraph Extra_functions I wrote, to see if work
template <typename Container>
void selection_sort_recursive(Container& v, int i);

template <typename Container>
void bubble_sort_recursive(Container& v, int n);

template <typename Container>
void insertion_sort_recursive(Container& v, int i);

template <typename Container>
int binary_search_recursive(Container& v, int a, int first, int last);

template <class Iter, class Container>
double sort_time(void sort_name(Iter, Iter), Container v);

/// --------------------------------------------------  END

// OUTPUTING FORMAT>...I'MSOSORRY
void header();

int main()
{   // I sear I could simplify the main to 40 lines
    std::cout << std::setprecision(5) << std::fixed;

    std::vector<int> vector_1(10000);
    std::vector<int> vector_2(20000);
    std::vector<int> vector_3(40000);
    std::vector<int> vector_4(80000);
    std::vector<int> vector_5(160000);

    populate(vector_1);
    populate(vector_2);
    populate(vector_3);
    populate(vector_4);
    populate(vector_5);

    header();

    std::cout << std::left << std::setw(20) << "Linear Search";

    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 1);

    std::cout << std::left << std::setw(20) << "Binary Search";

    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 2);

    std::cout << std::left << std::setw(20) << "Bubble Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 3);

    std::cout << std::left << std::setw(20) << "Selection Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 4);

    std::cout << std::left << std::setw(20) << "Insertion Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 5);

    std::cout << std::left << std::setw(20) << "Merge Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 6);

    std::cout << std::left << std::setw(20) << "Quick Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 7);

    std::cout << std::left << std::setw(20) << "std::sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 8);

    std::cout << "\nTimes reported in seconds\n";

    return EXIT_SUCCESS;
}

/// @paragraph This function populates a vector with random numbers
/// @param[in] vec is the vector to be populated
template <typename Container>
void populate(Container& vec)
{
    std::iota(vec.begin(), vec.end(), 0);
}

/// @paragraph This function resets a vector to random unosrted
/// @param[in] v is the vector to be reset
template <typename Container>
void again(Container& v1, Container& v2, Container& v3,
           Container& v4, Container& v5)
{
    std::shuffle(v1.begin(), v1.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v2.begin(), v2.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v3.begin(), v3.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v4.begin(), v4.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v5.begin(), v5.end(),
                 std::default_random_engine(std::random_device{}()));
}

template <typename Container>
void formatted(Container& v1, Container& v2, Container& v3,
               Container& v4, Container& v5, int number)
{
    std::cout << std::right
              << std::setw(7)  << measure_time(v1, number)
              << std::setw(13) << measure_time(v2, number)
              << std::setw(13) << measure_time(v3, number)
              << std::setw(13) << measure_time(v4, number)
              << std::setw(13) << measure_time(v5, number)
              << std::endl << std::flush;
}

/// @paragraph Search the vector using a linear search.
/// @param v The vector to search.
/// @param a The value to search for.
/// @return The index of the value in the vector.
template <typename Container, typename T>
int linear_search(Container v, T a)
{   // search for the value in the vector
    size_t index = 0;

    bool found = false;

    while (!found && index < v.size())
    {
        if (v[index] == a)
            found = true;
        else
            index++;
    }

    if (found)
        return index;
    else
        return -1;
}

/// @paragraph Search the vector using a binary search.
/// @param v The vector to search.
/// @param a The value to search for.
/// @return The index of the value in the vector.
template <typename Container, typename T>
int binary_search(Container v, T a)
{   // search for the value in the vector
    int first = 0;
    int last  = v.size() - 1;
    int mid;

    bool found = false;

    while (first <= last && !found)
    {
        mid = (first + last) / 2;
        if (v[mid] == a)
        {   // if the value is found, return the index
            found = true;
        }
        else if (a > v[mid])
        {   // if the value is greater than the midpoint
            first = mid + 1;
        }
        else
        {   // if the value is less than the midpoint
            last = mid - 1;
        }
    }

    if (found)
        return mid;
    else
        return -1;
}

/// @paragraph Sort the vector using bubble sort.
/// @param v The vector to sort.
template <typename Container>
void bubble_sort(Container& v)
{   // sort the vector using bubble sort
    for (size_t i = 0; i < v.size() - 1; i++) {
        for (size_t j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
template <typename Container>
void selection_sort(Container& v)
{   // sort the vector using selection sort
    for (size_t i = 0; i < v.size() - 1; i++) {
        int min = i;
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        std::swap(v[i], v[min]);
    }
}

/// @paragraph Sort the vector using an insertion sort.
/// @param v The vector to sort.
template <typename Container>
void insertion_sort(Container& v)
{   // sort the vector using insertion sort
    for (size_t i = 1; i < v.size(); i++)
    {   // for each element in the vector
        int j = i;
        int temp = v[i];
        while (j > 0 && v[j - 1] > temp)
        {   // while the element is smaller than the previous
            v[j] = v[j - 1];
            j--;
        }
        v[j] = temp;
    }
}

/// @paragraph Sort the vector using a merge sort.
/// @param v  The vector to sort.
/// @param other The vector to sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
template <typename Container>
void merge(Container& v, Container& other, int first, int mid, int last)
{   // merge the two vectors
    int k = first, i = first, j = mid + 1;

    // while there are elements in the left and right runs
    while (i <= mid && j <= last)
    {
        if (v[i] <= v[j])
        {   // if the left element is smaller than the right
            other[k++] = v[i++];
        }
        else
        {   // if the right element is smaller than the left
            other[k++] = v[j++];
        }
    }

    // copy any remaining elements from the left run
    while (i <= mid)
    {
        other[k++] = v[i++];
    }

    // copy the sorted elements back into the original vector
    for (int index = first; index <= last; index++) {
        v[index] = other[index];
    }
}

/// @paragraph Sort the vector using a merge sort.
/// @param v The vector to sort.
/// @param other The vector to sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
template <typename Container>
void merge_sort(Container& v, Container& other, int first, int last)
{   // sort the vector using merge sort
    if (last == first) return;

    // find midpoint
    // int mid = (first + last) / 2;
    int mid = (first + ((last - first) >> 1));

    // recursively split runs into two halves until run size == 1,
    // then merge them and return up the call chain
    merge_sort(v, other, first, mid);        // left half
    merge_sort(v, other, mid + 1, last);     // right half

    merge(v, other, first, mid, last);       // merge the two halves
}

/// @paragraph Partition of the quick sort
/// @param v The vector to sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
/// @return The index of the partitioned element.
template <typename Container>
int partition(Container& v, int first, int last)
{   // partition the vector
    int pivot = v[last];

    // elements less than the pivot will be pushed to the left of `pIndex`
    // elements more than the pivot will be pushed to the right of `pIndex`
    // equal elements can go either way
    int index = first;

    // each time we find an element less than or equal to the pivot, `index`
    // is incremented, and that element would be placed before the pivot.
    for (int j = first; j < last; j++)
    {
        if (v[j] <= pivot)
        {
            std::swap(v[index], v[j]);
            index++;
        }
    }

    // swap `index` with pivot
    std::swap(v[index], v[last]);

    // return the index of the pivot
    return index;
}

/// @brief Quick sort the vector
/// @param v The vector to sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
template <typename Container>
void quick_sort(Container& v, int first, int last)
{   // sort the vector using quick sort
    if (first < last)
    {
        int pivot = partition(v, first, last);

        // recur on subarray containing elements that are less than the pivot
        quick_sort(v, first, pivot - 1);

        // recur on subarray containing elements that are more than the pivot
        quick_sort(v, pivot + 1, last);
    }
}

template <typename Container>
double measure_time(Container& v, int number)
{
    std::vector<int> aux = v;
    auto start = high_resolution_clock::now();

    // switch case for all sort techniques we have implemented
    switch (number)
    {
    case 1:
        linear_search(v, INT_MIN);
        break;
    case 2:
        binary_search(v, INT_MIN);
        break;
    case 3:
        bubble_sort(v);
        break;
    case 4:
        selection_sort(v);
        break;
    case 5:
        insertion_sort(v);
        break;
    case 6:
        merge_sort(v, aux, 0, v.size() - 1);
        break;
    case 7:
        quick_sort(v, 0, v.size() - 1);
        break;
    case 8:
        std::sort(v.begin(), v.end());
        break;
    default:
        break;
    }

    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count() / 1'000'000.0;
}

void header()
{   // print the header
    std::cout << std::setw(27) << "10000"
              << std::setw(13) << "20000"
              << std::setw(13) << "400000"
              << std::setw(14) << "800000"
              << std::setw(13) << "1600000\n"
              << std::string(79, '-') << std::endl;
}

/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a starting point
/// @brief   return in void is not good but I'm too lazy to even change the if
template <typename Container>
void selection_sort_recurisve(Container& v, int i)
{   // sort the vector using selection sort
    if (i == v.size() - 1) {
        return;
    }

    int min = i;
    for (int j = i + 1; j < v.size(); j++)
    {   // find the smallest element
        if (v[j] < v[min])
        {   // if the smallest element is found,
            min = j;
        }
    }
    // swap the smallest element with the current element
    // on top of the vector
    std::swap(v[i], v[min]);

    // recursively call the function
    selection_sort_recursive(v, i + 1);
}

/// @paragraph Sort the vector using buble sort recursively
/// @param v The vector to sort.
/// @param n The vector size
template <typename Container>
void bubble_sort_recursive(Container& v, int n)
{   // sort the vector using bubble sort
    for (int i = 0; i < n - 1; i++)
    {   // for each element in the vector
        if (v[i] > v[i + 1])
        {   // if the element is bigger than the next element
            std::swap(v[i], v[i + 1]);
        }
    }
    // recursively call the function and we move toward the base case
    if (n - 1 > 1) {
        bubble_sort_recursive(v, n - 1);
    }
}

/// @paragraph Sort the vector using insertion sort recursively
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a breaking point, since 0 is already sorted
///          we start at 1
template <typename Container>
void insertion_sort_recursive(Container& v, int i)
{   // sort the vector using insertion sort
    int j = i;
    int temp = v[i];
    while (j > 0 && v[j - 1] > temp)
    {   // while the element is smaller than the previous
        v[j] = v[j - 1];
        j--;
    }
    v[j] = temp;

    // recursively call the function
    if (i + 1 <= v.size() - 1) {
        insertion_sort_recursive(v, i + 1);
    }
}

/// @paragraph   Search the vector using binary search
/// @param v     The vector to search
/// @param a     The element to search for
/// @param first The first element of Container
/// @param last  The last element of Container
/// @return      The index of the element
template <typename Container>
int binary_search_recursive(Container& v, int a, int first, int last)
{   // search for the value in the vector
    int mid = (first + last) / 2;

    if (v[mid] == a)
    {   // if the value is found, return the index
        return mid;
    }
    else if (v[mid] < a)
    {   // if the value is greater than the midpoint
        return binary_search_recursive(v, a, mid + 1, last);
    }
    else
    {   // if the value is less than the midpoint
        return binary_search_recursive(v, a, first, mid - 1);
    }

    return -1;
}

template <class Iter, class Container>
double sort_time(void sort_name(Iter, Iter), Container v)
{   // measure the time for each sort
    auto start = high_resolution_clock::now();

    // sort the vector
    sort_name(v.begin(), v.end());

    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count() / 1000000.0;
}

// TODO: add heapsort and introsort
