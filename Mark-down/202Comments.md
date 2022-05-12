# <span style="color:pink">C++ Comments by Thien Guen, bored.</span>

---
` Why Learn C++? `:

- Multi-paradigm Language - C++ supports at least seven different styles of programming. Developers can choose any of the styles.

- General Purpose Language - You can use C++ to develop games, desktop apps, operating systems, and so on.

- Speed - Like C programming, the performance of optimized C++ code is exceptional.

- Object-oriented - C++ allows you to divide complex problems into smaller sets by using objects.

---

`For the question: How do sizeof(arr) / sizeof(arr[0]) work?` 

    If you have an array then sizeof(array) returns the number of bytes the array occupies. Since each element can take more than 1 byte of space, you have to divide the result with the size of one element (sizeof(array[0])). This gives you number of elements in the array

---

<span style="background-color: green">Tips:</span> When you're consolidating your static functions into the new hpp header, remember declaration order matters! Since those functions rely on data types defined within the Container class, the class definition must appear before the static function prototypes  

---

    When we call a function template such as max() for some arguments, the template parameters are determined by the arguments we pass. If we pass two ints to the parameter types const T&, the C++ compiler must conclude that T must be int. Note that no automatic type conversion is allowed here. Each T must match exactly. For example:

```c++
template <class T>
const T& max(const T& a, const T& b);
...
max(4, 7)    // OK: T is int for both arguments 
max(4, 4.2)  // ERROR: first T is int, second T is double

/*
There are three ways to handle such an error:
1. Cast the arguments so that they both match:
max(static_cast<double>(4), 4.2)  // OK 

2. Specify (or qualify) explicitly the type of T: 
max<double>(4, 4.2)  // OK 

3. Specify that the parameters may have different types, i.e., multiple type parameters. */ 

/* However, when a template function calls a template function, the compiler needs your help qualifying the data types. We use option (2) by specifying the type of T. Once you convert your Container class to be a template, you will have to help the compiler a bit more by specifying the data type for the static functions, e.g., */

::copy<T>(...)
::equal<T>(...)
::find<T>(...) 
```

**Using typename**

```cpp
template <class T>
static void copy(typename Container<T>::const_pointer first,
                 typename Container<T>::const_pointer last,
                 typename Container<T>::pointer       d_first);
```

---
---
We were discussing the efficiency/inefficiency of using push_back to implement in

 ```cpp
 Container::operator+=(). 
 ```

I wrote a short program to test that hypothesis using 4'000'000 elements. Here's the code. We'll be using similar techniques by the end of the semester.

```c++
[[include]] <chrono>
[[include]] <iostream>
[[include]] <random>
[[include]] "Container.h"

int main() 
{
    using std==chrono==duration_cast;
    using std==chrono==high_resolution_clock;
    using std==chrono==microseconds;
    using std::cout;

    constexpr auto NUM_ELEMENTS{ 4'000'000 };

    auto time2fill = [](Container& box) -> double 
    {
        auto random = std::minstd_rand();
    
        auto start = high_resolution_clock::now();
        
        for (auto i = 0; i < NUM_ELEMENTS; ++i) 
        {
            box.push_back(random());
        }
        
        auto stop = high_resolution_clock::now();
        
        return duration_cast<microseconds>(stop - start).count() / 1E6;
    };

    Container box1{ NUM_ELEMENTS };
    Container box2{};

    cout << "Time w/ allocated container: " << time2fill(box1) << " secs\n";
    cout << "Time w/ empty container:     " << time2fill(box2) << " secs\n";

    return 0;
}
```

Running this program on bellagio produced the following output (default precision): <br/>
*Time w/ allocated container: 0.144201 secs
Time w/ empty container:     3083.46 sec*

    -That is more than 21 thousand times slower than just allocating the array once with sufficient capacity. Starting with a capacity of 0 performs 4'000'000 / 8 = 500'000 separate reallocations and copies (and that takes time)!

    -::copy(), ::equal(), apply the same logic

**(Technically)** The only reason find() raised an issue is because of scope and conflicting function signatures. If the wrong header is included, these other functions would also have issues! Using :: resolves the scope issue. (Scope resolution is covered back in chapter 7 if you want a quick refresher; we've just never had so many nested levels of scope to contend with before!)

---
---

Remember, operator= only applies to an existing object, that already has its own dynamic array and initialized member variables. We're replacing the contents, so we discard whatever we're currently storing, and simply make a copy of the **rhs**. There is a substantial discussion of this operator in the handout and at cppreference.com 

[pa13b.cpp += operator]

As an example:

```c++

Container box { 0, 1, 2, 3, 4 };

```

I can see that *(box.begin() + 0) == 0,*(box.begin() + 1) == 1, *(box.begin() + 2) == 2, and so on. Since I can compute the address, I can compare what I compute with what the find function returns. So, given the above definition

    CHECK(box.find(0) == box.begin());  // address of '0' should be the beginning address


`"So why was assembly language created?"`

Assembly language was created as an exact shorthand for machine level coding, so that you wouldn't have to count 0s and 1s all day. It works the same as machine level code: with instructions and operands.

`"Which one came first?"`

*Wikipedia* has a good article about the History of Programming Languages

`"Why am I studying about assemblers in my computer engineering class?"`

Though it's true, you probably won't find yourself writing your next customer's app in assembly, there is still much to gain from learning assembly.

Today, assembly language is used primarily for direct hardware manipulation, access to specialized processor instructions, or to address critical performance issues. Typical uses are device drivers, low-level embedded systems, and real-time systems.

Assembly language is as close to the processor as you can get as a programmer so a well designed algorithm is blazing -- assembly is great for speed optimization. It's all about performance and efficiency. Assembly language gives you complete control over the system's resources. Much like an assembly line, you write code to push single values into registers, deal with memory addresses directly to retrieve values or pointers. (source: codeproject.com)

---
---

    **Always (!?) be careful about saying "always." (Similar to its cousin, "Never say never.")**

As it turns out, with these specific functions, the compiler needs typename for the ::copy, ::equal, and ::find data types, but ::swap does not. Why?

When writing templates, typename is required, because the formal parameters are Container member types.

These  member types are  dependent upon T e.g., value_type is-a T, and a pointer is a T*, so we call them "dependent qualified names". Name lookup and binding are postponed until the template arguments are known for dependent names. And, the meaning of some constructs may differ from one instantiation to another.

Remember, we are not writing C++ code at the moment, but rather writing a template (or blueprint) for the compiler to automatically generate code. Suffice it to say we're only scratching the surface of C++ templates here. If you want to go further, you could investigate template specialization and template templates.**

---
---
` What is copy_ellision`

**Basically, in certain situations, the compiler is allowed to remove what would normally be a copy or move, and instead just write directly to the return value
In this case, s would just get constructed with the literal "Hello" straight away, instead of a temporary being created and then moved**

Read more: [Copy_elision](https://en.cppreference.com/w/cpp/language/copy_elision)

```c++
std::string f() { return "Hello"; }

//...

std::string s = f(); //RVO is guaranteed to happen, there will be no move

```

---
---
---
---
# <p align="center"> In dept details </p>

## Do not throw an exception and catch it at the same time, it doens't make sense

`We throw it seep inside the system and then we catch it at a (client program) higher level to resolve it.`

Move constuctor - if it go out of scope -> boom it was gone. Since it's going to be destroy why don't we just take it. 

It avoids reallocating memrory and the copy of it. Exchange is function take care of move assignment and leave the donor in stable state.

`std::exchange` 

Return the first argument to initialize the variable when we using exchange
the later argument is what being leave behind or leave in other in order for it to be stable [pa14 move constructor]

`User defined Function - Some random comments`

Functions of the class are not member variables they are just code

And they are not part of the object at all

They aren't data, they don't really "exist" on the object

- They exist in the overaching bundle of all functions, member functions have a hidden first parameter to "this" that gets passed into them, a pointer to the object instance it's supposed to do work on

`What is the point of returning a reference?'`

- For an assignment you return a reference because there's no need to create a new object after an assignment

- In the case of an assignment operator: not causing a copy
the result of an assignment is usually discarded and there is no need to form a new object

- And being able to chain multiple assignments, which you would not be able to do if you returned void

What is returning void you asked?

```c++
    // with overloading operators
    a = b = c;

    // is equivalent to
    a.operator=(b.operator=(c));
```

If the second assignment returned void, you would be trying to form a.operator=(void())
Which is illegal because void objects shall not exist

---
---

`Specifying ::find(par1, par2, par3) `: means that we explicitly want to check the global scope, not the Container or local scope.

The function you called, 
find(par1, par2, par3);
is called within the scope of the Container class.

This means that it will defer to looking in the local scope (Container) before looking in the global scope for symbols (variable names, functions, data types, etc).

It looks for the function name first. If there are multiple overrides of that function, then it will check the parameters.

But since there are not more than just the one Container::find() function defined in the class, it doesn't check the parameters.

---
---


`C++-style static_cast` [[Static]] : allows you to explicitly select the right type of cast.  It also makes it explicit what the cast applies to.

The -> and ()operators bind more tightly than a C-style cast, so the expression

```c++
    (X *)a->b()
    // parses as 
    (X *)(a->b()) 
```

It tries to first call the member function and then cast the result to X *, instead of casting a to X * and then calling the member function like you intended.

---
---
`Check whether an input string is alphanumeric or more uppercase or empty` :

```c++

bool isvalid(const std::string &input){
    if (input.empty()) return false;
    for (int i = 0; i < input.size(); ++i){
        char ch = input[i];
        if ( !((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) ) return false;
    }
    return true;
}

// if you still needed this function for something...
std==string myfunc(const std==string &input){
    if (!isvalid(input)) return "";
    return input;
}

if (!isvalid(input))
    // error, do something
else
    // OK, do something else
```

---
---

[[Const&pointers]]

```c++
Node* head = nullptr;
Node* tail{};              // sets to nullptr by default
Node* newNode = new Node;  // creates a new Node in the heap and stores the address
```

Practicing good pointer hygiene, you must define a pointer at the same time you declare it, even if it's just nullptr:

If practicing good "pointer hygiene", then a list can be deemed empty by having null head pointer. Both pointers are expected to be either nullptr or valid. So, having one pointer nullptr and the other not is deemed undefined behavior

Normally when you delete something from the heap using delete or delete[], the memory is simply marked as available by the heap manager. However, the actual data stored is not zeroed. This is where dangling pointers became particularly nasty: you've officially deleted the node or array (for example), but a dangling pointer may potentially still have access to that memory location. We must practice good "pointer hygiene", ensuring that any type of raw pointer be guarded (by your code) to ensure it only contains a valid address or nullptr. Anything else is flirting with disaster.

Remember automatic local variables are created (on the stack) when entering their scope, and they're destroyed when their scope ends. This includes local pointer variables. If a local pointer variable goes out of scope immediately after use, it isn't necessary to set it to nullptr. However, any pointer that has larger scope, or may get passed to functions, or, is used from another compilation unit, must be handled carefully. As soon as you invalidate such a pointer (e.g., by deleting its memory), you should ensure you set the pointer to nullptr.

So do you need to zero the memory? Not usually. You'd introduce a serious performance hit. But there may be security implications in some areas where memory must be zeroed (wiped) before being deleted.

The pointer is how we access to the link

---
---

# <span style="color:pink">Mid term</span>

```c++
/// Dynamically contiguous array emulating std::vector<T>
template class<T> class MyVector {
public: 
    using value_type = T;
    using size_type  = std::size_t;
    using pointer    = value_type*;
    using reference  = value_type&;

    MyVector() = default;
    .
    .
    .
protected: 
    size_type used     = 0;
    size_type capacity = 0;
    pointer   data     = nullptr;

};
```

`Question 1:` Define a move assignment operator for the MyVector class that replaces the contents with those of other using move semantics.

```c++
template <class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& rhs) {
    if (this != rhs) {
        capacity = std::exchange(rhs.capacity, 0);
        used     = std::exchange(rhs.used, 0);
        data     = std::exchange(rhs.data, nullptr);
    }
}
```

[From pa12 and the rest]

`Quetion 2:` Define a copy constructor 

```c++
template <class T>
MyVector<T>::MyVector(const MyVector<T>& other) 
: MyVector<T>(other.size() {
    used = other.size();
    std::copy(other.begin(), other.end(), begin());
}
```

`Question 3:` Define a move constructor for MyVector Class

```c++
MyVector<T>:: MyVector(MyVector<T>&& other) 
: capacity(std::exchange(other.capacity, 0)),
      used(std::exchange(other.used,0)),
      data(std::exchange(other.data,nullptr)) {}
```

`Question 4:` Define a copy assignment operator for the MyVector

```c++
template <class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs)
{
    if (this != &rhs) 
    {
        // 1. deallocate any memory that myvector is using internally
        if (rhs.size() > capacity) {
            delete [] data;
            capactiy = used = 0;

            // 2. allocate memory to hold the contents of rhs
            data     = new value_type [rhs.size()];
            capacity = rhs.size();
        }

        // 3. copy the value of rhs into this instance (lhs)
        std::copy(rhs.begin(), rhs.end(), begin());

        used = rhs.size();
    }
    return *this;
}
```

    OR

```cpp
/// Replaces the contents of the container with a copy of the contents of rhs.
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    // guard against self-assignment
    if (this != &rhs) {
        // 1. deallocate any memory that Container is using internally
        delete[] data;
        data = nullptr;
        used = 0;
        capacity = 0;

        // 2. allocate memory to hold the contents of rhs
        // 2.5. account for resize just in case
        data = new Container::value_type[rhs.capacity];
        used = rhs.size();

        // 3. copy the values from rhs into this instance
        copy<T>(rhs.data, rhs.data + rhs.size(), data);

        // std::copy(rhs.data, rhs.end(), data);
    }

    // 4. return *this
    return *this;
}
```

The second if statement checks is if we need to resize. capacity is a private member if the this object. A possible scenario that operator= needs to account for is the following:

```c++
vector<int> oldVector;
oldVector.push_back(1);
oldVector.push_back(1);
vector<int> newVector = oldVector // this is the line I'm referencing.
```

- Notice how in the above example, newVector takes the place of the this object, therefore when capacity  is referenced, it is talking about capacity of newVector.  Since newVector is initialized to a default size (0) when created (remember, the compiler reads code in order, line by line from left to right), resizing is needed when we assign it oldVector, which has a size of 2.

`Questions 5:` Define the member function shrink_to_fit for the MyVector class that reduces the capactity to size() to eliminate unused capcatiy.

```c++
template <class T>
void MyVector<T>::shink_to_fit() 
{
    if (capacity > size()) {
        // since we using the same instance(this)
        // thats why we have to create a temp to hold
        // our data, and we modify it with our will

        // here it create the exact memory for size()
        auto temp = new value_type [size()];
        
        // copy stuff to temp, data
        std::copy(begin(), end(), temp);

        // deallocate the current useless memory we have
        delete [] data;

        // now assign the stuff has been modify back
        data = temp;

        // and set what we want
        capacity = size();
    }
}

/// @note shirnki_to_fit does not take any parameters. It reduces the amount of memory required to exactly the number of elemetns being stored. thereby release RAM for other purposes.
```

`Question 6 and 7 and 8:` start at 1000. state its data type [lab12md]

```c++
    auto list = new int [20] = { 10,  20,  30,  40,  50,  60,  70,  80,  90 };
    auto  ip  = list + 4;
```

| Expression     | Data type       |
| -------------  | -------------   |
| `ip         `  | `int* `         |
| `list       `  | `int* `         |
| `*list + 2  `  | `*int `         |
| `*(list + 2)`  | `int  `         |
| `&list[2]   `  | `*int `         |
| `&ip        `  | `int**`         |


| Expression    | Value         | Expression  | Value         |
| ------------- | ------------- | ----------- | ------------- |
| `list`        |       1000    | `ip`        |      1016     |
| `list[2]`     |        30     | `ip[2]`     |      70       |
| `list + 3`    |        1012   | `ip + 4`    |      1048     |
| `*list + 2`   |        12     | `*(ip + 4)` |       0       |
| `*(list + 4)` |        50     | `ip[-2]`    |       50      |
| `&list[1]`    |       1004
| `&list[-3]`   |        988

`Question 9:` How does a compiler treat an inline member function of a class

Inline when used within a class definition means that the function's body (a single state ment) be inserted whenever the function is called, instead actually calling the function. This makes run time execution faster because it avoids overhead of a function call, but at the expense of increasing the size of the executable by the size of the function each time it's used. That's why they need to be small. The rule of "making it fit in a line is arbitrary, designed to keep the fnction as small as it can be.

`Question 10:` Suppose class two is derived from class one. To avoid multiple inclusion of these classes. Which preprocessor directive(s) is/ are used int he defnitions of these classes

```c++
[[ifndef]] IDENTIFIER_H
[[define]] IDENTIFIER_H
...
// class defnition(s)
[[endif]]
```

`Question 11:` Explain the difference between overriding and overloading a member function of a base class in a derived class.

- [ ] `Overriding` is parts of Polymophism when you derived a child class from a base class, the member function in the derived class must have the same name. type and parameter (we passed the same argument in) but the member function will behave differently from the base class. [[Overload_ridden_default#^70330d|Over_ridden]]

***Base class***

```c++
class Base {
   public:
    void himom() {
        cout << "Hi mom, I'm in the base class" << endl;
    }
};
```

***Derived class***

```c++
class Derived : public Base {
   public:
    void print() {
        cout << "Hi mom, I'm in the derived function" << endl;
    }
};

int main() {
    Derived hi;
    hi.himom();
    return 0;
}
```
    Output: Hi mom, I'm in the derived function

`Overloading` allow a dreived class can have multiple member functions with the same name but different in parameters (we will pass different argument in), consequenly the member function will behave differently depend on what parameter we will pass in.  ^420109

[[Overload_ridden_default#^70330d|Overr_stuff]]

    I'll give an example later

`Question 12:` If you define your own exception class, what typically is included in that class?

well, you must have [include] <stdexcept> in there

and the what() function is a must!

`Question 13:` How do you distinguish between the functions to overload the pre- and post- decrement operator for a class a a member function? 

Yet to respond

`Question 14:`
Name two exception handling techniques

1. Try, catch block within the main function we call, catch the exact exception we want and handle the problem
2. The throw, throw the exception within user defined function, or when an expected problem show up.

`Question 15:` Name the base class that is designed to handle the exceptions in C++;

std:: exception

`Question 16:` Explain the difference between a shallow copy and a deep copy of data

- The same memory address have two pointer point to its: shallow copy

- Each pointer point to its own memory address and does not share their data to anyone : deep copy

`Question 17:` What does the operator new do?

Allcoate the memory enough for the variable in type we wanted and return a pointer

`Question 18:` What is the return type of the function that overloads the binary || operator (or) for a class as a member function

bool

`Question 19:` How are std==ifstream and stD==ostream related

They are both derived from basic_ios

`Question 20:` Name five things you should do for classes with pointer member variables

Rule of fives:

1. Copy constructor
2. Move constructor
3. Destructor
4. Copy assignment constructor
5. Move assignment constructor

Rule of threes:
1. Destructor
2. copy constrcutor
3. copy assignment operator

`Question 21:` Name two stituations where the copy constructor executes

When we pass in a left value and we need to keep that value or object, we copied and pass it to the new object created.

Non-sharable reference

`Question 22:` Explain how, in a public inheritance the member of the base class are inherited by a derived class [[Inheritance#^cb5fb8]]

Derived a base class publicly mena we inherited the public members (keep they stay public), the protected members, as well as the private members remained the same property

Or when declared a dervied class. Using the public acess specifiers allow derived class ahve public member access to the base class.

`Question 23:` What is a destructor and what it its purpose

Destructor deallocate memory dynamiclly of the object we created so no memory leak happen, preventing seg fault.

`Question 24:` Whats the differnce between the private and protected members of a class

Private   - members are only accessible within the class defining them

Protected - members are accessible in the class that defines them and inclasses that inherit from that class.

`Question 25:`  What is wrong with the following code

```c++
template <class T> T*foo() 
{
    T value{};
    return &T;
}
```

The function T* foo() must go down the line. 

    THROWN OUT.

`Question 26:` What does the operator delete do?

Delete deallocate the memory of the obkect we no longer needed to delete its memory mostly to prevent memory leak

`Question 27:` What is a constructor? Why would you include a constructor in a class

Construtor used to initalize all the characteristics of an object enter the scope of ours class

It makes sure the object is initialized using the proper constructor and we perform action on the object after it was created.

`Question 28:` Explain why you need both public and private members in a class

Public members are visible outside the class definition, so they can be seen and used by code that makes use of the class. Private members are not visible outside the class definition, so they can only be seen and used by other members of the class. They cannot even be seen by derived classes.


`Question 29:` Explain why you cannot use a range-based for loop on dynamic arrays

The end of the array is unknown to the compie;r at compile time. It's similar to passing an array to a function - all the function knows is the base address. So a range-based loop will fail

`Question 30:` When writing the defnition of the function to overload the asignment operator for a class, why do you use the pointer this?

This is a reserved keyword in C++. It's the object itself, when performing assignment operator, we want to avoid self assignment and return the exact object if so.

`Question 31:` Define the template function is_sorted that returns true if the elemtns in the range (first, last) are sorted in non-descending order.

```c++
template <class Iter>
bool is_sorted(Iter first, Iter last)
{
    bool sorted = true;

    for ( ; sorted && first + 1 < last; ++first) { sorted = *first <= *(first + 1); }

    return sorted;
}
```


The preprocessor expands macros in all lines except preprocessor directives, lines that have a # as the first non-white-space character. It expands macros in parts of some directives that aren't skipped as part of a conditional compilation.

To define preprocessor macros we can use [[define]]. Its syntax is:

[[define]] identifier replacement

When the preprocessor encounters this directive, it replaces any occurrence of identifier in the rest of the code by replacement. This replacement can be an expression, a statement, a block or simply anything. The preprocessor does not understand C++ proper, it simply replaces any occurrence of identifier by replacement.

**`Node*` versus `iterator`**  [[Iterator-List]] ^8db70d

Consider the following two _possible_ MEMBER functions (for illustration - please don't implement these!)

```c++
    size_type physical_count1() const {
        size_type tally{};
        for (Node* pos = head; pos != nullptr; pos = pos->next) { ++tally; }
        return tally;
    }
    
    size_type physical_count2() const {
        size_type tally{};
        for (iterator pos = begin(); pos != end(); ++pos) { ++tally; }
        return tally;
    }
```

---
---

We have access to both the raw Node* as well as iterator within the List class. Since an iterator encapsulates a Node*, we can use either iterators or raw pointers inside the class, almost interchangeably. (The one primary difference is when allocating or deleting Nodes - this can only be done within the class, and can only be used with a Node* variable.)

However, as shown in the earlier example, I can freely use iterators outside the class. Since the Node data type is private to the List class, it is unknown (and inaccessible) from outside the class.

---
---

## Command Lien Arguments 

Essentially, for a given command execution, you have a list of words (a 'word' is typically described as a string of non-whitespace characters, however we can use the `'` character to make multiple words into one argument, like we see in the pa). ie,

```c++
$ ./a.out Hello, World 
./a.out Hello, 
World $ 
./a.out 'Hello, World' 
./a.out 
Hello, World
```

The arguments are parsed by the operating system, and passed to your main function in the form of `argc` and `argv`.

`argc` tells us how many arguments were passed in (this is at least 1 because the program being executed, like `./a.out`, is an argument). `argv` is a 2-dimensional array of characters (ie, an array of c-strings) whose content is populated with the previously mentioned words.

We can read from `argv` just like any other primitive array.

```c++
std::cout << argv[0] << std::endl;
```
You are using growthRate both as a variable name and a function name. The variable hides the function, and then you are trying to use the variable as if it was the function - that is not valid.

Rename the local variable. [reference](https://stackoverflow.com/posts/4412644/timeline)
****