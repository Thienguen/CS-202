# <span style="color:pink">C++ Comments by Thien Guen, bored.</span> 

# <p align="center"> Sort Summaries </p>

- [x] Linear Search
- [x] Binary Search
- [x] Bubble Sort
- [x] Selection Sort
- [x] Insertion Sort
- [x] Merge Sort
- [x] Quick Sort
- [x] std::sort

---
---

## `Linear Sort` 

```c++
/// @paragraph Search the vector using a linear search.
/// @param v The vector to search.
/// @param a The value to search for.
/// @return The index of the value in the vector.
int linear_search(std::vector<int> v, int a)
{   // search for the value in the vector
    for (int i = 0; i < v.size(); i++) { if (v[i] == a) return i; }

    return -1;
}
```

---
---

## `Binary Search` [[ADT in C++#^eb64d9|Link to ADT]]
How it actually works? 

![Binary Algo](Pretty%20images/binary%20search.png)

```c++
/// @paragraph Search the vector using a binary search.
/// @param v The vector to search.
/// @param a The value to search for.
/// @return The index of the value in the vector.
int binary_search(std::vector<int> v, int a)
{   // search for the value in the vector
    int low = 0;
    int high = v.size();
    // the above delcarations get us the index

    while (low < high)
    {
        int mid = (low + high) / 2;
        if (v[mid] == a)
        {   // if the value is found, return the index
            return mid;
        }
        else if (v[mid] < a)
        {   // if the value is greater than the midpoint
            low = mid + 1;
        }
        else
        {   // if the value is less than the midpoint
            high = mid - 1;
        }
    }

    return -1;
}
```
OR?


![[binary search.gif]]

> RECURISVE FORM

```c++
// recursive functions
int binary_search_recursive(std::vector<int> v, int a, int low, int high)
{   // search for the value in the vector
    int mid = (low + high) / 2;
    
    if (v[mid] == a)
    {
        return mid;
    }
    else if (v[mid] < a)
    {
        return binary_search_recursive(v, a, mid + 1, high);
    }
    else
    {
        return binary_search_recursive(v, a, low, mid - 1);
    }

    return -1;
}

```

---
---

## `Bubble Sort` 

Each pass of bubble sort steps through the list to be sorted compares each pair of adjacent items and swaps them if they are in the wrong order. At the end of each pass, the next largest element will “Bubble” up to its correct position. These passes through the list are repeated until no swaps are needed, which indicates that the list is sorted. In the worst-case, we might end up making an n-1 pass, where n is the input size.

How it actually works?

![bubble sort](Pretty%20images/bubble%20sort.png)

```c++
/// @paragraph Sort the vector using bubble sort.
/// @param v The vector to sort.
void bubble_sort(std::vector<int>& v)
{   // sort the vector using bubble sort
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}
```

OR?

![[Sorting_bubblesort_anim.gif]]

> RECURSIVE FORM

```c++
/// @paragraph Sort the vector using buble sort recursively
/// @param v The vector to sort.
/// @param n The vector size
void bubble_sort_recursive(std::vector<int>& v, int n)
{   // sort the vector using bubble sort
    for (int i = 0; i < v.size() - 1; i++)
    {   // for each element in the vector
        if (v[i] > v[i + 1])
        {   // if the element is bigger than the next element
            std::swap(v[i], v[i + 1]);
        }
    }
    // recursively call the function and we move toward the base case
    if (n - 1 > 1) { bubble_sort_recursive(v, n - 1); }
}

```

---
---
## `Selection Sort`

How it actually works?

![Selection Sort](Pretty%20images/selection%20sort.png)

```c++
/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
void selection_sort(std::vector<int>& v)
{   // sort the vector using selection sort
    for (int i = 0; i < v.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        std::swap(v[i], v[min]);
    }
}
```

OR? 

![[selection-sort-animation.gif]]

> RECURISVE FORM

```c++
/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a starting point
/// @brief   return in void is not good but I'm too lazy to even change the if
void selection_sort_recursive(std::vector<int>& v, int i)
{   // sort the vector using selection sort
    if (i == v.size() - 1) { return; }
    
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

```

## `Insertion Sort`

How it actually works?

![Insertion Sort](Pretty%20images/insertion%20sort.png)



```c++
/// @paragraph Sort the vector using an insertion sort.
/// @param v The vector to sort.
void insertion_sort(std::vector<int>& v)
{   // sort the vector using insertion sort
    for (int i = 1; i < v.size(); i++) 
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
```

OR?

![[CornyThickGordonsetter-size_restricted.gif]]

> RECURSIVE FORM

```c++
/// @paragraph Sort the vector using insertion sort recursively
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a breaking point, since 0 is already sorted
///          we start at 1
void insertion_sort_recursive(std::vector<int>& v, int i)
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
    if (i + 1 <= v.size() - 1) { insertion_sort_recursive(v, i + 1); }
}
```

## `Merge Sort`

How it actually works

![Merge Sort](Pretty%20images/Merge%20sort.png)

> OR?

![[merge_sort_gif.gif]]

```c++
/// @paragraph Sort the vector using a merge sort.
/// @param v The vector to sort.
/// @param v2 The vector to sort.
/// @param l The index of the first element in the vector.
/// @param h The index of the last element in the vector.
void merge(std::vector<int>& v, std::vector<int>& v2, int low, int mid, int high)
{   // merge the two vectors
    int k = low, i = low, j = mid + 1;

    // while there are elements in the left and right runs
    while (i <= mid && j <= high)
    {
        if (v[i] < v[j])
        {   // if the left element is smaller than the right
            v2[k++] = v[i++];
        }
        else 
        {   // if the right element is smaller than the left
            v2[k++] = v[j++];
        }
    }

    // copy any remaining elements from the left run
    while (i <= mid)
    {
        v2[k++] = v[i++];
    }

    // copy the sorted elements back into the original vector
    for (int i = low; i <= high; i++)
    {
        v[i] = v2[i];
    }
}

/// @paragraph Sort the vector using a merge sort.
/// @param v The vector to sort.
/// @param v2 The vector to sort.
/// @param low The index of the first element in the vector.
/// @param high The index of the last element in the vector.
void merge_sort(std::vector<int>& v, std::vector<int>& v2, int low, int high)
{   // sort the vector using merge sort
    if (high == low) return;

    // int mid = (low + high) / 2;
    int mid = (low + ((high - low) >> 1));

    // recursively split runs into two halves until run size == 1,
    // then merge them and return up the call chain
    merge_sort(v, v2, low, mid);        // left half
    merge_sort(v, v2, mid + 1, high);   // right half

    merge(v, v2, low, mid, high);       // merge the two halves
}
```

## `Quick Sort`

How it actually works

![Quick Sort](Pretty%20images/Quicksort.png)

```c++
/// @paragraph Partition of the quick sort
/// @param v The vector to sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
/// @return The index of the partitioned element.
int partition(std::vector<int>& v, int first, int last)
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
void quick_sort(std::vector<int>& v, int first, int last)
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
```

![[Quicksort.gif]]

![[Sorting_quicksort_anim.gif]]





