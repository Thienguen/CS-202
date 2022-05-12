# Keyword Functions Overloading: ThienGuen - 3/29/2022

In C++, two functions can have the same name if the number and/or type of arguments passed is different.

These functions having the same name but different arguments are known as overloaded functions. For example:

```c++
    // same name different arguments
    int test() { }
    int test(int a) { }
    float test(double a) { }
    int test(int a, double b) { }
```

The return types of all these 4 functions are not the same. Overloaded functions may or may not have different return types but they must have different arguments

---
---
---
---

## Keyword Default Arguments (Parameters): ThienGuen - 3/29/2022

If a function with default arguments is called without passing arguments, then the default parameters are used.

However, if arguments are passed while calling the function, the default arguments are ignored. [Default argument](Pretty%20images/cpp-default-parameters.webp)

`Things to Remember`

1. Once we provide a default value for a parameter, all subsequent parameters must also have default values. For example,

Exmaple:

```c++
// Invalid
void add(int a, int b = 3, int c, int d);

// Invalid
void add(int a, int b = 3, int c, int d = 4);

// Valid
void add(int a, int c, int b = 3, int d = 4);
```

2. If we are defining the default arguments in the function definition instead of the function prototype, then the function must be defined before the function call.

```c++
// Invalid code
int main() {
    // function call
    display();
}

void display(char c = '*', int count = 5) {
    // code
}
```

---
---

- Tính phủ quyết (overriding) / hay còn gọi là ghi đè: [[202Comments#^d8fcd3]]

Để thực hiện cho nhu cầu overriding, bạn chỉ cần đặt tên phương thức ở lớp con trùng tên và tham số truyền vào với phương thức đã có ở lớp cha.

- Nạp Chồng Phương Thức (Overloading): [[202Comments#^420109]]

Overloading cho phép một lớp có khả năng định nghĩa ra nhiều phương thức có cùng tên, nhưng khác nhau về tham số truyền vào. ^70330d


    If an object is passed by value:

- Contents of data members of the actual parameter are copied into the
corresponding data members of the formal parameter

- Problem: when passing by reference, the actual parameter changes when the
formal parameter changes

        Solution: use const in the formal parameter declaration

- Encapsulation: combines data and operations on data in a single unit

- Inheritance: creates new objects (classes) from existing objects (classes)

- Polymorphism: the ability to use the same expression to denote different
operations