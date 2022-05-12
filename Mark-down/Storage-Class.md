# Keyword Storage Class: ThienGuen

---
### <span style="color:pink">Local Variables</span>

- A variable defined inside a function (defined inside function body between braces) is called a local variable or automatic variable.

- Its scope is only limited to the function where it is defined. In simple terms, local variable exists and can be accessed only inside a function.

- The life of a local variable ends (It is destroyed) when the function exits.

<span style="background-color: green">Example:</span>

```c++
[[include]] <iostream>
using namespace std;

void test();

int main() 
{
    // local variable to main()
    int var = 5;

    test();
    
    // illegal: var1 not declared inside main()
    var1 = 9;
}

void test()
{
    // local variable to test()
    int var1;
    var1 = 6;

    // illegal: var not declared inside test()
    cout << var;
}
```
---
---

### <span style="color:pink">Global Variables</span>

- If a variable is defined outside all functions, then it is called a global variable.

- The scope of a global variable is the whole program. This means, It can be used and changed at any part of the program after its declaration.

- Likewise, its life ends only when the program ends.

<span style="background-color: green">Example:</span>

```c++

[[include]] <iostream>
using namespace std;

// Global variable declaration
int c = 12;

void test();

int main()
{
    ++c;

    // Outputs 13
    cout << c <<endl;
    test();

    return 0;
}

void test()
{
    ++c;

    // Outputs 14
    cout << c;
}
```

---
---

### <span style="color:pink">Static Local Variables</span> [[Static#^e504c2|Static Variables]]

- A static local variable exists only inside a function where it is declared (similar to a local variable) but its lifetime starts when the function is called and ends only when the program ends.

- The main difference between local variable and static variable is that, the value of static variable persists the end of the program.

<span style="background-color: green">Example:</span>

```c++
[[include]] <iostream>
using namespace std;

void test()
{
    // var is a static variable
    static int var = 0;
    ++var;

    cout << var << endl;
}

int main()
{
    
    test();
    test();

    return 0;
}
```

Output: 

1

2

In the above program, test() function is invoked 2 times.

During the first call, variable var is declared as static variable and initialized to 0. Then 1 is added to var which is displayed in the screen.

When the function test() returns, variable var still exists because it is a static variable.

During second function call, no new variable var is created. The same var is increased by 1 and then displayed to the screen.


## <span style="color:pink">Static Variables inside Functions</span> [[Static#^a4194b|Static Functions]]

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

## <span style="color:pink"> Static Class Objects</span> [[Static#^44b7ca|Static Class]]

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

## <span style="color:pink">Static Member Functions </span> [[Static#^c06d29|Link]]


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

