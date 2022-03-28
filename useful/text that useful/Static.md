# Keyword Static: ThienGuen

Static is a keyword in C++ used to give special characteristics to an element. Static elements are allocated storage only once in a program lifetime in static storage area. And they have a scope till the program lifetime. Static Keyword can be used with following

1. Static variable in functions
2. Static Class Objects
3. Static member Variable in class
4. Static Methods in class

## <span style="color:pink">Static Variables inside Functions</span>

Static variables when used inside function are **initialized only once**, and then they hold there value even through function calls.

    These static variables are stored on static storage area , not in stack.
<span style="background-color: green">Using Static Keyword:</span>

```c++
void counter()
{
    static int count = 0;
    cout << count++;
}

int main(0
{
    for(int i = 0; i < 5; i++) { counter(); }
    // return
    return 0;
}
```

    Output: 0 1 2 3 4
<span style="background-color: Red">Not using Static Keyword:</span>

```c++
void counter()
{
    int count=0;
    cout << count++;
}

int main(0
{
    for(int i = 0; i < 5; i++) { counter(); }
    // return
    return 0;
}

```

    Output: 0 0 0 0 0
If we do not use static keyword, the variable count, is reinitialized everytime when counter() function is called, and gets destroyed each time when counter() functions ends.

But, if we make it static, once initialized count will have a scope till the end of main() function and it will carry its value through function calls too.

If you don't initialize a static variable, they are by default initialized to zero.

## <span style="color:pink"> Static Class Objects</span>

Objects declared static are allocated storage in static storage area, and have scope till the end of program.

Static objects are also initialized using constructors like other normal objects. Assignment to zero, on using static keyword is only for primitive datatypes, not for user defined datatypes.

```c++
class Abc
{
public:
    int i;
     Abc() { i = 0; cout << "constructor"; }
    ~Abc() { cout << "destructor"; }
};

void foo() { static Abc obj; }

int main()
{
    int x = 0;
    if (x == 0) { foo(); }
    cout << "END";
}
```

    Output: constructor END destructor

The process goes something like this: 

- The function foo was called after the if statement, henced the object was created.
- The compiler then proceed to create an object of class Abc with the default constructor
- Then destroy it after main function exit.

The destructor was not called upon *the end of the scope of if condition*.

Where the reference of object obj should get destroyed. This is because object was static, which has scope till the program's lifetime, hence destructor for this object was called when **main function exits**.

## <span style="color:pink"> Static Data Member in Class </span>

    Static data members of class are those members which are shared by all the objects.

Static data member has a single piece of storage, and is not available as separate copy with each object, like other non-static data members.

Static member variables (data members) are not initialied using constructor, because these are not dependent on object initialization.

Also, it must be initialized explicitly, always outside the class. If not initialized, Linker will give error.

```c++
class X
{
public:
    static int i;
    X() { // construtor };
};

int X::i = 1;

int main()
{
    X obj;
    cout << obj.i;   // prints value of i
}
```

    Output: 1

Once the definition for static data member is made, user cannot redefine it. Though, arithmetic operations can be performed on it.

## <span style="color:pink">Static Member Functions </span>


```c++
class X
{
public:
    static void foo() { // statement }
};

int main()
{
    X::foo();   // calling member function directly with class name
}
```

These functions cannot access ordinary data members and member functions, but only static data members and static member functions.

It doesn't have any "this" keyword which is the reason it cannot access ordinary members.


    Static make this work and the function remain the same no matter how you called it how may time you call it and it only available in that, 
    make sure they die at the end of that function

A class object can be automatic or static

– Automatic: created when the declaration is reached and destroyed when the
surrounding block is exited

– Static: created when the declaration is reached and destroyed when the
program terminates

