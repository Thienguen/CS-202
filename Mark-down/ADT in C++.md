# <span style="color:pink">C++ ADT. ThienGuen, bored</span>

## <span style="color:pink">Implicit *this</span>

Since member variables and member functions are both located within the scope of a class, C++ allows us to refer to members from within a member function without the explicit this-> syntax. The compiler automatically inserts the member dereference for us

```c++
class Triangle {
    double a;
    double b;
    double c;

    ...

    double side1() const {
        return a;
    }

    double side2() const {
        return b;
    }

    double side3() const {
        return c;
    }

    double perimeter() const {
        return side1() + side2() + side3();
        // Equivalent to: this->side1() + this->side2() + this->side3()
    }
};
```

## <span style="color:pink">Information Hiding.</span>

- Good abstraction design uses encapsulation, which groups together both the data and functions of an ADT. With a class, we get encapsulation by defining both member variables and member functions.

- A proper abstraction also provides information hiding, which separates interface from implementation. Access specifiers such as private allow us to prevent the outside world from accessing implementation details.

## <span style="color:pink">Abstract Classes and Interfaces</span>

In some cases, there isn’t enough information in a base class to define a particular member function, but we still want that function to be part of the interface provided by all its derived classes. In the case of Bird, for example, we may want a get_wingspan() function that returns the average wingspan for a particular kind of bird. There isn’t a default value that makes sense to put in the Bird class. Instead, we declare get_wingspan() as a pure virtual function, without any implementation in the base class:

```c++
class Bird {
  ...
  virtual int get_wingspan() const = 0;
};
```

- The syntax for declaring a function as pure virtual is to put = 0; after its signature. This is just syntax – we aren’t actually setting its value to 0.

---
---

Since Bird is now missing part of its implementation, we can no longer create objects of Bird type. The Bird class is said to be abstract. We can still declare Bird references and pointers, however, since that doesn’t create a Bird object. We can then have such references and pointers refer to derived-class objects:

```c++
Bird bird("Big Bird");      // ERROR: Bird is abstract
Chicken chicken("Myrtle");  // OK, as long as Chicken is not abstract
Bird &bird_ref = chicken;   // OK
Bird *bird_ptr = &chicken;  // OK
```

In order for a derived class to not be abstract itself, it must provide implementations of the pure virtual functions in its base classes:

```c++
class Chicken : public Bird {
    ...
    int get_wingspan() const override {
        return 20;  // inches
    }
};
```

With a virtual function, a base class provides its derived classes with the option of overriding the function’s behavior. With a pure virtual function, the base class requires its derived classes to override the function, since the base class does not provide an implementation itself. If a derived class fails to override the function, the derived class is itself abstract, and objects of that class cannot be created.

We can also define an interface, which is a class that consists only of pure virtual functions. Such a class provides no implementation; rather, it merely defines the interface that must be overridden by its derived classes. The following is an example:

```c++
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void scale(double s) = 0;
};
```

### With subtype polymorphism, we end up with two use cases for inheritance:

1. Implementation inheritance, where a derived class inherits functionality from a base class

2. Interface inheritance, where a derived class inherits the interface of its base class, but not necessarily any implementation

### size_t

The size_t type represents only nonnegative integers, and the C++ standard guarantees that it is large enough to hold the size of any object. Since it does not represent negative integers, we could have used it for num_elements rather than defining 0 <= num_elements as a representation invariant. We would then also use size_t as the return type for size(), which is what the standard-library containers do.

C++ has integral types that are unsigned, which do not represent negative numbers, and size_t is just one example. The int type is signed (unless it is preceded by the unsigned keyword). Unsigned integers can lead to subtle programming errors. The following is an example that compares a signed and unsigned integer:

```c++
int main() {
    size_t s = 3;
    int i = -1;
    cout << (s < i) << endl;   // prints 1 (true)
}
```

Perhaps non-intuitively, the comparison s < i is true, even though s is positive but i is negative. This is because the compiler converts i to a size_t in doing the comparison, and the data that represents a negative signed integer actually represents a very large unsigned integer.

 - Another common error is incorrectly iterating backwards over a sequence:

```c++
int main() {
    vector<int> vec = { 1, 2, 3 };
    for (size_t i = vec.size() - 1; i >= 0; --i) {
        cout << vec[i] << endl;
    }
}
```

This code goes off the end of the vector, resulting in undefined behavior. The reason is that a size_t is always greater than or equal to 0, and when i is equal to 0 and decremented, its value wraps around to the largest possible size_t value. The following iteration correctly avoids this problem:

```c++
int main() {
    vector<int> vec = { 1, 2, 3 };
    for (size_t i = vec.size(); i > 0; --i) {
        cout << vec[i - 1] << endl;
    }
}
```

## <span style="color:pink">Sorted Representation</span>

```c++
void SortedIntSet::insert(int value) {
    assert(size() < MAX_SIZE);
    // only for unique value
    if (!contains(value))
    {
        int index = num_elements;
        while (index > 0 && elements[index - 1] > value) 
        {
            elements[index] = elements[index - 1];
            --index;
        }

        elements[index] = value;
        ++num_elements;
  }
}
```

Similarly, to remove an item, we must shift the remaining elements leftward in order to maintain our representation invariants.

```c++
void SortedIntSet::remove(int value) {
    int index = indexOf(value);
    if (index != -1) {
        for (; index < num_elements - 1; ++index) {
        elements[index] = elements[index + 1];
        }
        --num_elements;
    }
}
```

---
---
- A Binary search for a sorted set (unique num) ^eb64d9

```c++
int SortedIntSet::indexOf(int value) const {
    int start = 0;
    int end = num_elements;
    while (start < end) {
        
        // start from middle
        int middle = start / 2 + end / 2;

        // execution
        if (value == elements[middle]) { return middle;} 
            else if (value < elements[middle]) { end = middle; }
                else { start = middle + 1; }
    }
    return -1;
}
```

The Algorithm goes like this.

- Compare the value we are looking for to the middle element among the remaining items.

- If the value is equal to the middle element, we have found its index.

- If the value is less than the middle element, we know it must be to the left, if it is in the set. Thus, we need only repeat the search on the items in the first half.

- If the value is greater than the middle element, we know it must be to the right, if it is in the set. Thus, we need only repeat the search on the items in the second half.

- If we have run out of elements to search, the value is not in the set.