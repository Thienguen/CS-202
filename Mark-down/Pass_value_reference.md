# Thien Guen, for Obsidian

`When do we use pass by reference and pass by value.? `

- If you are going to make a copy anyway you can pass-by-value and move, if its a small and trivial type you can also pass-by value,
- But if you don't need to own a copy and are just "borrowing" a value for the function you do pass-by-reference

` My key takeaway is :`

1. Is the type small and trivial? pass-by-value

2. Are you going to make a copy anyway? pass-by-value and std::move
Do you need to borrow the object for the function call? pass-by-(const) reference 

1. There are also other factors in play when deciding but that is how I generally decide how to specify parameters

`Advantages of pass-by-value and advantages of std::move over pass-by-reference`

**Please remember that mname is what being initialized**

**Same warning, name and moved_name is what being passed in**

```c++
/* (0) */ 
Creature(const std::string &name) : m_name{name} { }
```

-A passed lvalue binds to name, then is copied into m_name.

- A passed rvalue binds to name, then is copied into m_name.

```c++
/* (1) */ 
Creature(std==string name) : m_name{std==move(name)} { }
```

- A passed lvalue is copied into name, then is moved into m_name.

- A passed rvalue is moved into name, then is moved into m_name.

```c++
/* (2) */ 
Creature(const std::string &name) : m_name{name} { }
Creature(std==string &&moved_name) : m_name{std==move(moved_name)} { }
```

- A passed lvalue binds to name, then is copied into m_name.

- A passed rvalue binds to moved_name, then is moved into m_name.

---
---     
- As move operations are usually faster than copies, (1) is better than (0) if you  
  pass a lot of temporaries. (2) is optimal in terms of copies/moves, but requires code repetition.

- The code repetition can be avoided with perfect forwarding: 

```c++
/* (3) */
template <typename T,
          std::enable_if_t<
              std==is_convertible_v<std==remove_cvref_t<T>, std::string>, 
          int> = 0
         >
Creature(T&& name) : m_name{std::forward<T>(name)} { }
```

- You might optionally want to constrain T in order to restrict the domain of types that this constructor can be instantiated with (as shown above). C++20 aims to simplify this with [Concepts](https://en.cppreference.com/w/cpp/language/constraints).

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