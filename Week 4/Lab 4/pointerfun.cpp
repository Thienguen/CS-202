#include <iostream>

int main() {
    using std::cout;

    // reads data into a,b and c.
     int a;
     int b;
     int c;

     int* p = &a;
     int* q = &b;
     int* r = &c;

     std::cin >> *p >> *q >> *r;
     
    cout << "------------------POINTERS FUN------------------\n";    
    cout << "value of a is: "   << a 
         << " - and its address: "  << &a << std::endl;
    cout << "value of p is: "   << *p 
         << " - and its address: " << p << std::endl;
    
    cout << "\nvalue of b is: " << b 
         << " - and its address: "  << &b << std::endl;
    cout << "value of q is: "   << *q 
         << " - and its address: " << q << std::endl;

    cout << "\nvalue of c is: " << c 
         << " - and its address: "  << &c << std::endl;
    cout << "value of r is: "   << *r 
         << " - and its address: "  << r << std::endl;

    cout << __FUNCTION__ << " passed\n";
    return 0;
}