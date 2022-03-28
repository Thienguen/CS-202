
# Keyword const in C++

## Thien Guen, bored

---
## <span style="color:pink">Constant Variables in C++</span>

If you make any variable as constant, using const keyword, you cannot change its value. Also, the constant variables must be initialized while they are declared.

```c++
int main
{
    const int i = 10;
    const int j = i + 10;     // works fine
    i++;                      // this leads to Compile time error   
}
```

## <span style="color:pink">Pointers with const keyword in C++</span>

## - Pointer to a const variable

This means that the pointer is pointing to a const variable. And the const is at the left of asterisl (*) sign.

Example:

```c++
const int* u;

char const* v;
```

## - const Pointer

We put the const keyword to the right of the asterisk (*).

```c++
int x = 1;

// p is a const pointer that point to an integer or variable x
int* const p = &x;
```

The code above said that pointer p will always point to the variable x but we can change the value of what its pointing to, by change the value of x

Why are we doing this?

Usage: The constant pointer to a variable is useful where you want a storage that can be changed in value but not moved in memory. Because the pointer will always point to the same memory location, because it is defined with const keyword, but the value at that memory location can be changed.

## <span style="color:pink">const Function Arguments and Return types</span>

We can make the return type or arguments of a function as const. Then we cannot change any of them.

```c++
void f(const int i) { i++; } // error

const int g() { return 1; }  // gud
```

If a function has a non-const parameter, it cannot be passed a const argument while making a call.

```c++
void t(int*) 
{ 
    // function logic
}
```
If we pass a const int* argument to the function t , it will give error.
But, a function which has a const type parameter, can be passed a const type argument as well as a non-const argument.
```c++
void g(const int*) 
{
    // function logic
}
```
This function can have a int* as well as const int* type argument.

## <span style="color:pink">Defining Class Data members as const</span>

These are data variables in class which are defined using const keyword. They are not initialized during declaration. Their initialization is done in the constructor.

```c++
class Test
{
public:
    const int i;
    Test(int x):i(x) { cout << "\ni value set: " << i; }
};

int main()
{
    Test t(10);
    Test s(20);
}
```

In this program, i is a constant data member, in every object its independent copy will be present, hence it is initialized with each object using the constructor. And once initialized, its value cannot be changed. The above way of initializing a class member is known as Initializer List in C++.

## <span style="color:pink">Defining Class Object as const</span>

When an object is declared or created using the const keyword, its **data members can never be changed, during the object's lifetime**.

    const class_name object;

## <span style="color:pink">Defining Class's Member function as const</span>

- A const member functions never modifies data members in an object.

```c++
    return_type function_name() const; 
```

```c++
    class StarWars
{
    public:
    int i;
    StarWars(int x) { i = x; }  // constructor

    // constant function
    int falcon() const { cout << "Falcon has left the Base"; }
        /* 
            can do anything but will not
            modify any data members
        */
    int gamma() { i++; }
};

int main()
{
    StarWars objOne(10);            // non const object
    const StarWars objTwo(20);      // const object

    objOne.falcon();     // No error
    objTwo.falcon();     // No error

    cout << objOne.i << objTwo.i;

    objOne.gamma();     // No error
    objTwo.gamma();     // Compile time error
}
```
    Output: Falcon has left the Base
            Falcon has left the Base
            10 20

## mutable Keyword

mutable keyword is used with member variables of class, which we want to change even if the object is of const type. Hence, mutable data members of a const objects can be modified.
