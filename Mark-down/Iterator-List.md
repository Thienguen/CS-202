# <span style="color:pink">Iterators Thien Nguyen, bored </span>

Linked lists do not provide random access; since they are not array-based, accessing an element in the middle of the list cannot be done with pointer arithmetic, but must traverse from the start of the list as in print(). Thus, traversal by index is not an appropriate pattern for a linked list.

Traversal by pointer, on the other hand, starts with a pointer to the beginning of a sequence and iterates by moving that pointer forward to each subsequent element, until that pointer reaches past the end of the sequence:

---
---
We use an object called an iterator to iterate over the elements. and it is a generalization of traversal by pointer.

**In addition, the container itself must provide two member functions:**
in order to traverse with an iterator, it must provide the following operations: 

> 1. Dereference     (prefix *)
> 2. Increment       (prefix ++)
> 3. Equality checks (== and !=)
> 4. begin() returns an iterator to the start of the sequence
> 5. end() returns a “past-the-end” iterator

Before we proceed to implement Iterator, observe the following issues with its definition:

- Node is not a top-level type, but a member of the List class template, so it cannot be named from the outside without the scope-resolution operator.

- The Node struct is private, so it cannot be accessed from outside code.

- The iterator type is associated with List, so it should be encapsulated within the List template.

Then the solution should be as simple as defining Iterator as a member of the List template:

```c++
template <typename T>
class List {
    ...
private:
    struct Node {
        int data;
        Node *next;
    };

public:
    class Iterator {
    public:
        T & operator*() const;

        Iterator &operator++();

        bool operator==(Iterator rhs) const;

        bool operator!=(Iterator rhs) const;
    private:
        Node *node_ptr;
    };

private:
    Node *first;
    Node *last;
};
```

Now, we can write the definition of our overloaded functions:

`Dereference and Increment Operators`

```c++
// REQUIRES: this is a dereferenceable iterator
// EFFECTS:  Returns the element that this iterator points to.
template <typename T>
T& List<T>==Iterator==operator*() const {
    assert(node_ptr);  // check whether this is a past-the-end iterator
    return node_ptr->data;
}
```

The dereference operator does not modify the iterator. In addition, while the function returns an object by reference to non-const, modifying that object does not modify the iterator, since the object is not a member of the iterator itself. Thus, the dereference operator can be declared as a const member function.

---
---
`The operator++()`

Function modifies the iterator by moving it to “point to” the next element, so it cannot be declared as const. As with dereference, the past-the-end iterator cannot be incremented – node_ptr would be null, and there wouldn’t be a next pointer to move the iterator to.

```c++
// REQUIRES: this is a dereferenceable iterator
// EFFECTS:  Returns the element that this iterator points to.
template <typename T>
typename List<T>==Iterator & List<T>==Iterator::operator++() {
    assert(node_ptr);  // check whether this is a past-the-end iterator
    node_ptr = node_ptr->next;
    return *this;
}
```

>The postfix increment operator can be overloaded as well. To distinguish its signature from prefix, C++ uses a dummy int parameter for postfix:

```c++
template <typename T>
typename List<T>==Iterator List<T>==Iterator::operator++(int) {
    assert(node_ptr);  // check whether this is a past-the-end iterator
    Iterator tmp = *this;               // make a copy of this iterator
    node_ptr = node_ptr->next;
    return tmp;                                      // return the copy
}
```

---
---

## The typename Keyword

The return type of `operator++()` is a reference to `List<T>::Iterator;` `Iterator` is a member of a template that is dependent on the template parameter `T`. C++ requires the typename keyword before a dependent name that refers to a type, so that the compiler knows that it is a type and not a value.

---
---
`Equality Comparisons`

Two iterators are defined as equal if either they are both past the end, or they “point to” the same element in the same list. Thus, they are equal exactly when their node_ptr members point to the same node.

```c++
template <typename T>
bool List<T>==Iterator==operator==(Iterator rhs) const {
    return node_ptr == rhs.node_ptr;
}

template <typename T>
bool List<T>==Iterator==operator!=(Iterator rhs) const {
    return node_ptr != rhs.node_ptr;
}
```

---
---

```c++
void print_links(const List<int>& list, std==ostream& output = std==cout) {
    constexpr int CW{ 11 };  // column width

    output << "┌─────────────┬─────────────┬─────────────┬─────────────┐\n"
              "│ data        │    previous │        node │        next │\n"
              "├─────────────┼─────────────┼─────────────┼─────────────┤\n";

    for (auto it = list.begin(); it != list.end(); ++it) {
        output << "│ "  << std==left << std==setw(CW) << *it << std::right
               << " │ " << std::setw(CW) << it->prev
               << " │ " << std::setw(CW) << it.operator->()
               << " │ " << std::setw(CW) << it->next << " │\n";
    }

    output << "└─────────────┴─────────────┴─────────────┴─────────────┘\n";
}

```

`Possible output:`  

```
┌─────────────┬─────────────┬─────────────┬─────────────┐
│ data        │    previous │        node │        next │
├─────────────┼─────────────┼─────────────┼─────────────┤
│ 9           │         0x0 │ 0x101210640 │ 0x101210200 │
│ 7           │ 0x101210640 │ 0x101210200 │ 0x1012101c0 │
│ 5           │ 0x101210200 │ 0x1012101c0 │ 0x101210180 │
│ 3           │ 0x1012101c0 │ 0x101210180 │ 0x101210140 │
│ 1           │ 0x101210180 │ 0x101210140 │ 0x101210120 │
│ 0           │ 0x101210140 │ 0x101210120 │ 0x101210160 │
│ 2           │ 0x101210120 │ 0x101210160 │ 0x1012101a0 │
│ 4           │ 0x101210160 │ 0x1012101a0 │ 0x1012101e0 │
│ 6           │ 0x1012101a0 │ 0x1012101e0 │ 0x101210620 │
│ 8           │ 0x1012101e0 │ 0x101210620 │         0x0 │
└─────────────┴─────────────┴─────────────┴─────────────┘
```

Remember, an iterator stores a pointer to a node. Use the arrow operator when you want to dereference a pointer to a Node in lieu of using the member access operator, e.g.

```c++
List<int> list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
List<int>::iterator it = list.begin();
cout << "Previous link: " << (*it).prev << endl;  // clunky
cout << "Next link:"    " << it->next << endl;    // much better
cout << "Info stored:   " << *it      << endl;    // just like a pointer
```

## Why Iterator? [[202Comments#^8db70d|here's why]]

---
---

If you re-use existing functionality in your code (you did test it, right?), then we can use that to abstract away the complexity. Copying a list can be reduced to just:

```c++
List<int> src { 1, 2, 3 };
List<int> dest{};

for (auto& item : src) {
    dest.insert(dest.end(), item);
}

assert(src == dest);
```

Note that you cannot use std::copy to copy a List except under very specific circumstances we cannot be assured of having.