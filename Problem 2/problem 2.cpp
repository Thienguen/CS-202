/*
    Thien Nguyen Revision on 3/29/2022
    * Description: recursive reverse string
    * Input: Define in main
    * Output: Results to console
*/

#include <iostream>
using namespace std;

void reverse(string& str, int lstr, int fstr) {
    if (lstr > fstr) { return; }

    swap(str[lstr], str[fstr]);

    reverse(str, lstr + 1, fstr - 1);
};

int main()
{
    string  strArr[] = 
    { 
        "hello",
        "racecar",
        "tattarrattat",
        "stupidity is an option",
        "because it's our nature to be one",
        "animal loots foliated detail of stool lamina"
    };
    int strSize = sizeof(strArr) / sizeof(strArr[0]);

    cout << "Recursion Problem 2 - Reverse String" << endl << endl;

    for (int i = 0; i < strSize; i++) 
    {
        cout << i <<": " << strArr[i] << endl;

        // reverse with tail recursion start at string array i
        // position 0 to the end() - 1
        reverse(strArr[i], 0, strArr[i].size() - 1);

        cout << "R: " << strArr[i] << endl << endl;
    }

    return EXIT_SUCCESS;
}
