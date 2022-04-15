/*
    * Description: recursive largest smaller than K
    * Input: Define in main
    * Output: Results to main
*/

#include <iostream>
using namespace std;

// ****************************************************************

/// @param arr[] array 
/// @param l     iterator till before end - 1
/// @param u     the end of the array, size - 1
/// @param k     largest smaller than k than to this parameter
int largestSmallerThanK(int arr[], int l, int u, int k) {
    if (l != u) 
    {
        int temp = largestSmallerThanK(arr, ++l, u, k); // using temp as current max
        if (arr[l] > temp) 
        {
            if (arr[l] < k) { return arr[l]; }
            if (arr[l] > k) { return temp; }
        }
        
        if (arr[l] < temp) { return temp; }
            // if current index is less than the current max (temp)
            // return temp because its still the max
    }
    if (l == u) 
    {
        if (arr[l] < k)  { return arr[l]; }
            // you return l because l < k value
            // if youre at the end
    }
    return -1;
}
// ****************************************************************
//  Simple main for testing.

int main()
{
    int arr1[6]  = {1, 4, 3, 8, 7, 6};
    int arr2[19] = {0};
    int arr3[12] = {0};
    
    int k1 = 5;
    int k2 = 50;
    int k3 = 10;
    
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    cout << "\nRecursion Problem 1 - Largest Smaller than K" << endl << endl;

    cout << "Test 1:" << endl;

    // this print the array, make sure the last is not , 
    for (int i = 0; i < size1 - 1; i++) { cout << arr1[i] << ", "; } cout << arr1[size1 - 1] << endl;

    cout << "Largest Smaller than " << k1 << " is " << largestSmallerThanK(arr1, 0, size1 - 1, k1) << endl;

    /// ----------------------------------------------------/// 

    for (int i = 0; i < size2; i++) { arr2[i] = rand() % 100; }
    
    cout << "\nTest 2:" << endl;

    for (int i = 0; i < size2 - 1; i++) { cout << arr2[i] << ", "; } cout << arr2[size3 - 1] << endl;
    
    cout << "Largest Smaller than " << k2 << " is " << largestSmallerThanK(arr2, 0, size2 - 1, k2) << endl;

    /// ----------------------------------------------------/// 

    for (int i = 0; i < size3; i++) { arr3[i] = rand() % 100; }

    cout << "\nTest 3:" << endl;

    for (int i = 0; i < size3 - 1; i++) { cout << arr3[i] << ", "; } cout << arr3[size3 - 1] << endl;

    cout << "Largest Smaller than " << k3 << " is " << largestSmallerThanK(arr3, 0, size3 - 1, k3) << endl;

    return  EXIT_SUCCESS;
}