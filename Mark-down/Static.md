# Thien Guen, Keyword: Static
[[Storage-Class]]

`Keyword: Static` is what makes the variable shared across all instances of the class. inline (when applied to a static member variable) makes it so the declaration is also a definition.  Without inline a separate definition is needed outside the class ^e504c2

Generally - it needs to go

(1) before the class (and then everything within the class definition is automatically a template, and

(2) before the definition of out-of-line member definitions, and

(3) before the prototype and definition of non-member functions.

`Stack objects` only live within the scope they were created, when you leave that scope, the object is destroyed. Therefore, if a member variable lives in the scope of the function, a new copy needs to be created and put into some location as defined by the caller. That returned value isn't "temporary", it's the version that's going to live on and do whatever the caller wanted to do with it

---
---

## Keyword Static: <mark>ThienGuen</mark>

- Static: the lifetime is essentially the whole program

- Automatic (also called local): the lifetime is tied to a particular scope, such as a block of code

- Dynamic: the object is explicitly created and destroyed by the programmer


Static is a keyword in C++ used to give special characteristics to an element. Static elements are allocated storage only once in a program lifetime in static storage area. And they have a scope till the program lifetime. Static Keyword can be used with following

1. Static variable in functions ^a4194b
2. Static Class Objects ^44b7ca
3. Static member Variable in class
4. Static Methods in class

---
---
**C++ is honestly not the purest OOP language, languages like C# and Java make this example way cleaner and simpler
at the cost of obscuring some memory-related aspects**

It's C with classes:

1. public - anyone can access them, within or from outside the class.
2. private - only the member functions within that class can access them. ^c06d29
3. protected - derived classes can access those memebrs

`Extra explanation`

- Private members are only accessible within the class defining them.

- Protected members are accessible in the class that defines them and in classes that inherit from that class.
