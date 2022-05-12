# <span style="color:pink">Inheritance: Thienguen</span>

> <span style="background-color: green">In short:</span> ***The derived class inherits the features from the base class and can have additional features of its own***

> Before we going any further

![inheritance](Pretty%20images/Screenshot%202022-03-30%20021502.png)

Exmaple:

```c++
class Animal {
    // eat() function
    // sleep() function
};

class Dog : public Animal {
    // bark() function
};
```

- Inheritance is an is-a relationship. We use inheritance only if an is-a relationship is present between the two classes.

```c++
// C++ program to demonstrate inheritance

[[include]] <iostream>
using namespace std;

// base class
class me {

   public:
    void himom() {
        cout << "hi mom!" << endl;
    }

    void hi() {
        cout << "hi there" << endl;
    }
};

// derived class
class other_me : public me {
 
   public:
    void depressed() {
        cout << "life is meaning less" << endl;
    }
};

int main() {
    // Create object of the other_me class
    other_me other;

    // Calling members of the base class
    other.himom();
    other.hi();

    // Calling member of the derived class
    other.depressed();

    return 0;
}
```

    Output: 
    hi mom!
    hi there
    life is meaningless

`C++ Protected Members:` Protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.

Example:

```c++
// C++ program to demonstrate protected members

[[include]] <iostream>
[[include]] <string>
using namespace std;

// base class
class Animal {

   private:
    string color;

   protected:
    string type;

   public:
    void eat() {
        cout << "I can eat!" << endl;
    }

    void sleep() {
        cout << "I can sleep!" << endl;
    }

    void setColor(string clr) {
        color = clr;
    }

    string getColor() {
        return color;
    }
};

// derived class
class Dog : public Animal {

   public:
    void setType(string tp) {
        type = tp;
    }

    void displayInfo(string c) {
        cout << "I am a " << type << endl;
        cout << "My color is " << c << endl;
    }

    void bark() {
        cout << "I can bark! Woof woof!!" << endl;
    }
};

int main() {
    // Create object of the Dog class
    Dog dog1;

    // Calling members of the base class
    dog1.eat();
    dog1.sleep();
    dog1.setColor("black");

    // Calling member of the derived class
    dog1.bark();
    dog1.setType("mammal");

    // Using getColor() of dog1 as argument
    // getColor() returns string data
    dog1.displayInfo(dog1.getColor());

    return 0;
}
```

Output:

    I can eat!
    I can sleep!
    I can bark! Woof woof!!
    I am a mammal
    My color is black

- We can see this as we have initialized type in the Dog class using the function setType().

- On the other hand the private variable color cannot be initialized in Dog.

```c++
class Dog : public Animal {

    public:
      void setColor(string clr) {
          // Error: member "Animal::color" is inaccessible
          color = clr; 
      }
};
```

> Also, since the protected keyword hides data, we cannot access type directly from an object of Dog or Animal class.

```c++
// Error: member "Animal::type" is inaccessible
dog1.type = "mammal";
```

---
---

## Public, protected, and private inheritance have the following features

---
---

- public inheritance makes public members of the base class public in the derived class, and the protected members of the base class remain protected in the derived class.
 ^cb5fb8
- protected inheritance makes the public and protected members of the base class protected in the derived class.

- private inheritance makes the public and protected members of the base class private in the derived class.


```c++
class Base {
    public:
        int x;
    protected:
        int y;
    private:
        int z;
};

class PublicDerived: public Base {
    // x is public
    // y is protected
    // z is not accessible from PublicDerived
};

class ProtectedDerived: protected Base {
    // x is protected
    // y is protected
    // z is not accessible from ProtectedDerived
};

class PrivateDerived: private Base {
    // x is private
    // y is private
    // z is not accessible from PrivateDerived
}
```

`Example 1: C++ public Inheritance`

```c++
// C++ program to demonstrate the working of public inheritance

[[include]] <iostream>
using namespace std;

class Base {
   private:
    int pvt = 1;

   protected:
    int prot = 2;

   public:
    int pub = 3;

    // function to access private member
    int getPVT() {
        return pvt;
    }
};

class PublicDerived : public Base {
   public:
    // function to access protected member from Base
    int getProt() {
        return prot;
    }
};

int main() {
    PublicDerived object1;
    cout << "Private = " << object1.getPVT() << endl;
    cout << "Protected = " << object1.getProt() << endl;
    cout << "Public = " << object1.pub << endl;
    return 0;
}

// Out put
// Private = 1
// Protected = 2
// Public = 3
```

Since private and protected members are not accessible from main(), we need to create public functions getPVT() and getProt() to access them:

```c++
// Error: member "Base::pvt" is inaccessible
cout << "Private = " << object1.pvt;

// Error: member "Base::prot" is inaccessible
cout << "Protected = " << object1.prot;
```

