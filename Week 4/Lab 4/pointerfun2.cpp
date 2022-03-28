#include <iostream>

int main() {
    using std::cout;

    const int  numbers[3]  = { 3, 1, 2 };
    const int* pointers[3] = { nullptr };

    // initialize pointers to respective elements in numbers
    for (size_t i = 0; i < 3; ++i) {
        pointers[i] = &numbers[i];
    }

    // sort the pointers
    pointers[0] = &numbers[1];
    pointers[1] = &numbers[2];
    pointers[2] = &numbers[0];

    cout << "sorted pointers: ";
    for (const int* ip : pointers) {
        cout << ' ' << *ip;
    }

    cout << "\nconstant array:  ";
    for (const int value : numbers) {
        cout << ' ' << value;
    }

    cout << '\n';

    return 0;
}