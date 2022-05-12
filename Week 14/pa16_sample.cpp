#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/// A macro that defines algorithms
#define ALGORITHMS {LINEAR, BINARY, BUBBLE, SELECT, INSERT, MERGE, QUICK, STDSORT}

namespace cs202
{	// all the sort techniques
	template <typename Iter, typename T> Iter seqsearch (Iter first, Iter last, const T& value);
	template <typename Iter, typename T> Iter binsearch (Iter first, Iter last, const T& value);
	template <typename Iter> void bubble_sort (Iter first, Iter last);
	template <typename Iter> void selection_sort(Iter first, Iter last);
	template <typename Iter> void insertion_sort(Iter first, Iter last);
	template <typename Iter> void merge_sort(Iter first, Iter last);
	template <typename Iter> void quick_sort (Iter first, Iter last);
} // namespace cs202

class Benchmark {
private:
	// the set of algorithms to test for performance	
	enum algorithm_t : size_t ALGORITHMS;

	// the list of vectir test sizes (initializer_list)
	const initializer_list<size_t> TEST_SIZE;

	// the list of random values to process (initializer_list)
	const vector<int> INIT; 

	const array<string, 8> LABEL
	{	// list of labels to display for each algorithm
		"Linear Search",	 // LINEAR
		"Binary Search",	 // BINARY
		"Bubble Sort",		 // BUBBLE
		"Selection Sort",    // SELECTION
		"Insertion Sort",	 // INSERTION
		"Merge Sort",		 // MERGE
		"Quick Sort",	 	 // QUICK
		"Std::sort"	 		 // STDSORT
	};

private:
	// convenience alias foravector iterator
	using iterator = typename vector<int>::iterator;

	// convenience alias forapointer toavoid function taking two iterators as parameters
	using func_t = void(*)(iterator, iterator);

	// function returns the time taken to call funct on the range [first, last)
	static double time (func_t func, iterator first, iterator last);

	// returnsarandomized vector ofaspecified size
	static vector<int> rand_vector(size_t size);

	// wrapper functions to match signature of funct_t
	static void seqsearch(iterator first, iterator last) {
		(void)cs202::seqsearch(first, last, INT_MIN);
	}

	static void binsearch(iterator first, iterator last) {
		(void)cs202::binsearch(first, last, numeric_limits<int>::min());
	}

public:
	// constructor sets the sequence of vector sizes to time values
	explicit Benchmark(initializer_list<size_t>&& sizes)
	: TEST_SIZE(move(sizes)), 
	INIT(Benchmark::rand_vector(*max_element(TEST_SIZE.begin(), TEST_SIZE.end()))) {}
	
	// runs the benchmark 
	void run();

	// printsatable header
	void table_header();

};

int main() 
{
	Benchmark bench{ 10000, 20000, 40000, 80000, 160000 };

	bench.table_header();

	bench.run();

	return EXIT_SUCCESS;
}

/// @paragraph Sort the vector using the specified algorithm
void Benchmark::run() 
{	// save current configurations
	const auto fmt_flags = cout.flags();

	// set report configurations
	cout << fixed << showpoint << setprecision(5);

	for (auto alg : ALGORITHMS) 
	{
		cout << left << setw(15) << LABEL[alg] << right << flush;

		for (auto size : TEST_SIZE) 
		{	// for each size, run the algorithm and print the time
			auto seconds = 0.0;

			// a randomized vector of required size, copied fron INIT
			auto test = vector<int>{ INIT.begin(), INIT.begin() + size };
			
			switch (alg) 
			{	// all cases have been covered so no default case is needed
				case LINEAR:
					seconds = Benchmark::time(Benchmark::seqsearch, test.begin(), test.end());
					break;
				case BINARY:
					std::sort(test.begin(), test.end());
					seconds = Benchmark::time(Benchmark::binsearch, test.begin(), test.end());
					break;
				case BUBBLE:
					seconds = Benchmark::time(cs202::bubble_sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
				case SELECT:
					seconds = Benchmark::time(cs202::selection_sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
				case INSERT:
					seconds = Benchmark::time(cs202::insertion_sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
				case MERGE:
					seconds = Benchmark::time(cs202::merge_sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
				case QUICK:	
					seconds = Benchmark::time(cs202::quick_sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
				case STDSORT:
					seconds = Benchmark::time(std::sort, test.begin(), test.end());
					assert(is_sorted(test.begin(), test.end()));
					break;
			}
			cout << setw(13) << seconds << flush;
		}
		cout << endl;	// cout << setw(13) << '\n' << flush;
	}

	cout.flags(fmt_flags); 	// restore original configurations
}

/// Measures the time taken foraspecified function to process the range
/// [first,last).
///
/// @param func The function to call
/// @param first The first element in the range.
/// eparam last The end of the range.
///
/// @returns The time taking for func to process [first, last).
double Benchmark::time(func_t func, iterator first, iterator last)
{	// return the time taken to call func on the range [first, last)
	using namespace chrono;
	
	auto start = chrono::high_resolution_clock::now();

	func(first, last);

	auto stop = chrono::high_resolution_clock::now();

	return duration_cast<microseconds>(stop - start).count() / 1'000'000.0;
}

/// Printsatable header.
/// ----------------------------------------------------------------------
void Benchmark::table_header()
{	// formatted
	cout << setw(15) << ' ';

	for (auto size : TEST_SIZE) 
	{
		cout << setw(13) << size;
	}

	cout << '\n' << string(15 + 13 * TEST_SIZE.size(), '-') << '\n';
}

/// ----------------------------------------------------------------
/// Generates and returnsarandomized vector of integers in the range [0,size)
/// @param size The size of the random vector.
//
/// @returns A randomized vector of integers.
/// ----------------------------------------------------------------

vector<int> Benchmark::rand_vector(size_t size) 
{	// vector of specifed size to be return
	auto vec = vector<int>(size);

	iota(vec.begin(), vec.end(), 0);
	shuffle(vec.begin(), vec.end(), minstd_rand());

	return vec;
}

/// Returns an iterator to the first element in the range [first, last) that is
/// equal to value, or last if no such element is found.
///
/// @tparam Iter Type of the iterator.
/// @tparam T Generic type of the value.
/// @param first The first element in the range.
/// @param last The end of the range.
/// @param value The value to compare the elements to.
//
/// @returns An iterator to the first element equal to value or last if no such
/// element found.
/// -----------------------------------------------------------------------
/// @sa https://en.cppreference.com/w/cpp/algorithm/find

template <typename Iter, typename T>
Iter cs202::seqsearch(Iter first, Iter last, const T& value)
{	// return the iterator to the first element in the range [first, last) that is
	// equal to value, or last if no such element is found
	auto position = last;

	for ( ; first != last && position == last; ++first) {
		if (*first == value) {
			position = first;
		}
	}

	return position;
}

/// Checks if an element equivalent to value appears within the range
/// [first,last). For this function to succeed, the range [first,last) be
/// quite ordered with respect to value.
/// @param Iter Type of the iterator.
/// @param T Generic type of the value.
/// @param first The first element in the range.
/// @param last The end of the range.
/// @param value The value to compare elements to.
/// @sa https://en.wikibooks.org/wiki/Algorithm Implementation/Search/Binary search#C++ (generic)

template <typename Iter, typename T>
Iter cs202::binsearch(Iter first, Iter last, const T& value)
{	// return the iterator to the first element in the range [first, last) that is
	// equal to value, or last if no such element is found
	assert(is_sorted(first, last));

	auto position = last;

	while (first < last && position == last) 
	{	// find the median value between the Iterators first and last
		const auto mid = next(first, distance(first, last) / 2);

		// divide and conquer
		if (*mid == value) 
		{	// found the value
			position = mid;
		} 
		else if (*mid < value) 
		{	// search the right half
			first = mid + 1;
		} 
		else 
		{	// search the left half
			last = mid;
		}
	}

	return position;
}

/// -----------------------------------------------------------------------
/// Sorts the elements in the range [first,last) in non-descending order using
/// the Bubble Sort algorithm.
/// Elements are compared using operator<.
//
/// @param Iter Type of the iterator.
/// @param first The first element in the range to sort.
/// @param last The end of the range.
///
/// @sa https://en.wikibooks.org/wiki/Algorithm-Implementation/Sorting/Bubble-sort#C++
/// -----------------------------------------------------------------------

template <typename Iter>
void cs202::bubble_sort(Iter first, Iter last)
{	// sort the elements in the range [first, last) in non-descending order using
	// the Bubble Sort algorithm
	for (auto i = first; i != last; ++i) 
	{	// iterate through the range [first, last)
		for (auto j = first; j != i; ++j) 
		{	// iterate through the range [first, last)
			if (*j > *i) 
			{	// swap the elements
				swap(*j, *i);
			}
		}
	}
}

/// -----------------------------------------------------------------------
/// Sorts the elements in the range (first,last) in non-descending order using
/// the Selection Sort algorithm.
/// Elements are compared using operator<.
///
/// @param Iter Type of the iterator.
/// @param first The first element in the range to sort.
/// @param last The end of the range.
///
/// @sa https://en.wikibooks.org/wiki/Algorithm Implementation/Sorting/Selection sort#C++
/// -----------------------------------------------------------------------

template <typename Iter>
void cs202::selection_sort(Iter first, Iter last)
{	
	for ( ; first != last; ++first) {
		swap(*first, *min_element(first, last));
	}
}

/// -----------------------------------------------------------------------	
/// Sorts the elements in the range [first,last) in non-descending order using
/// the Insertion Sort algorithm.
/// Elements are compared using operator<.
///
/// @param Iter Type of the iterator.
/// @param first The first element in the range to sort.
/// @param last The end of the range.
///
/// @sa https://en.wikibooks.org/wiki/Algorithm Implementation/Sorting/Insertion sort#C/C++
/// -----------------------------------------------------------------------	

template <typename Iter>
void cs202::insertion_sort(Iter first, Iter last) 
{
	if (first != last) {
		swap(*first, *min_element(first, last));

		for (auto i = first; ++i < last; first = i) {
			for (auto j = i; *j < *first; --j, --first) {
				swap(*j, *first);
			}
		}
	}
}

// -----------------------------------------------------------------------
/// Sorts the elements in the range (first, last) in non-descending order using
/// the Merge Sort algorithm.
/// Elements are compared using operator<.
///
/// @param Iter Type of the iterator.
/// @param first The first element in the range to sort.
/// @param last The end of the range.
//
/// @sa https://en.cppreference.com/w/cpp/algorithm/inplace merge
/// -----------------------------------------------------------------------

template <typename Iter>
void cs202::merge_sort(Iter first, Iter last)
{	// number of elements in the range [first, last)
	const auto size = distance(first, last);

	if (size > 1) 
	{	// divide the range [first, last) into two halves
		const auto middle = next(first, size / 2);

		cs202::merge_sort(first, middle);
		cs202::merge_sort(middle, last);
		inplace_merge(first, middle, last);
	}
}

/// -----------------------------------------------------------------------
/// Sorts the elements in the range [first, last) in non-descending order using
/// the Quick Sort algorithm.
/// Elements are compared using operator<.
// etparam Iter Type of the iterator.
/// eparam first The first element in the range to sort.
/// eparam last The end of the range.
///
/// @sa https://rosettacode.org/wiki/Sorting algorithms/Quicksort
/// -----------------------------------------------------------------------

template <typename Iter>
void cs202::quick_sort(Iter first, Iter last)
{	// number of elements in the range [first, last)
	if (distance(first, last) > 1)
	{	// left  end   of current partition
		// right end   of current partition
		// the   pivot of the current partition
		auto left  = first;
		auto right = last;
		auto pivot = left++;

		while (left < right)
		{	// reorder elements in the range [first, last)
			if (*left < *pivot) { ++left; }
			else
			{
				while (left != right && *pivot < *right) { --right; }
				swap(*left, *right);
			}
		}

		--left;

		swap(*pivot, *left);

		cs202::quick_sort(first, left);
		cs202::quick_sort(right, last);
	}
}

/* EOF */






