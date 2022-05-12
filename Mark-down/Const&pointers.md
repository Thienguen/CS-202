
# Keyword const in C++

## Thien Guen, bored

---
## <span style="color:pink">Constant Variables in C++</span>

- If you make any variable as constant, using const keyword, you cannot change its value. Also, the constant variables must be initialized while they are declared.

- A variable declared as const can be initialized, but its value cannot be later modified through an assignment. For a simple type,

```c++
int main
{
    const int i = 10;
    const int j = i + 10;     // works fine
    i++;                      // this leads to Compile time error   
}
```

## <span style="color:pink">Pointers with const keyword in C++</span>

## - `Pointer to a const variable`

This means that the pointer is pointing to a const variable. And the const is at the left of asterisl (*) sign.

Example:

```c++
const int* u;

char const* v;
```

## - `const Pointer`

We put the const keyword to the right of the asterisk (*).

```c++
int x = 1;

// p is a const pointer that point to an integer or variable x
int* const p = &x;
```

The code above said that pointer p will always point to the variable x but we can change the value of what its pointing to, by change the value of x

```c++
int x = 3;
int y = 4;
int * const ptr = &x;
*ptr = -1;             // OK -- ptr is pointing to a non-const int
ptr = &y;              // ERROR -- attempt to assign to const object
```

- “ptr is a constant pointer to an int”. Technically, you can't modify the pointer or the address itself, but you can change the value or object that ptr is pointing to


## `Finally`

We can declare that both the pointer itself and the object it is pointing to are const:

```c++
int x = 3;
int y = 4;
const int * const ptr = &x;
ptr = &y ;             // ERROR -- attempt to assign to const object
*ptr = -1;             // ERROR -- attempt to assign to const object
```

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

---
---

Only `types with values` may be declared as const. The following types do not have values:

- References; they alias objects that may have values but do not have values of their own.

- Arrays; as we saw previously, arrays are objects that do not have values of their own.

- Functions; we will see function types later in the course.

## `Arrays and const`

Similar to a reference, an array may not be const itself, but its elements may be:

```c++
const double arr[4] = { 1.1, 2.3, -4.5, 8 };
arr[2] = 3.1;          // ERROR -- attempt to assign to const object
```

The declaration const double arr[4] is read inside out as “arr is an array of four constant doubles.” The elements can be initialized through an initializer list, but they may not be modified later through assignment.

## `const Conversion `

If we initialize a reference-to-non-const with a const object, we would enable the object to be modified through the reference. Thus, such a conversion is prohibited:

```c++
const int x = 3;
int &ref = x;      // ERROR -- enables const object to be modified through ref
ref = 4;           // ERORR -- would modify the x object if the above were allowed
```

---
---
` My 2 cents: ` If a function does not need to modify the underlying object, then it should be declared as const. Declaring a struct as const prevents any of its members from being modified.

Except for very small structs, we generally do not pass structs by value, since creating a copy of a large struct can be expensive. Instead, we pass them by pointer or by reference. If the original object needs to be modified, we use a pointer or reference to non-const. Otherwise, we use a pointer or reference to const:

```c++
void func_ptr(const Person *p);   // const can go on either side of
void func_ref(Person const &p);   // Person, but must be to the left
                                  // of * or & for the Person itself
                                  // to be non-modifiable
```

Example:

```c++
// MODIFIES: person
// EFFECTS: Increases the person's age by one. If they are now older
//          than 70, they are no longer a ninja.
void Person_birthday(Person person) {
    ++p.age;
    if (p.age > 70) {
        p.is_ninja = false;
    }
}
```

![stack value object|400](Pretty%20images/struct%20stack.png)

```c++
// REQUIRES: ptr points to a valid Person object
// MODIFIES: *ptr
// EFFECTS: Increases the person's age by one. If they are now older
//          than 70, they are no longer a ninja.
void Person_birthday(Person *ptr) {
    ++(*ptr).age;
    if ((*ptr).age > 70) {
        (*ptr).is_ninja = false;
    }
}
```

![stack reference object|400](Pretty%20images/reference%20stack.png)

---
---

## Explaning Pointer - Simplistic way

When you call method on object e.g.

```cpp
struct Stru{ void foo() { std::cout<< this; } }
int main(){
    Stru s;
        s.foo();
}

```

Then this pointer points to the object it was called on. In my example, foo will print address of s. Because foo() was called on s.

- **Pointer** It's limited usage (could be more) to structs and classes.

When executing a member function, it points to the object the function was called on. That's about **it**