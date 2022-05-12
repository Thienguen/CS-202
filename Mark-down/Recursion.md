# Keyword Recursion: ~~ThienGuen~~

A function that calls itself is known as a recursive function. And, this technique is known as recursion.

Non-Tail Recursion: smoller problems then base case

<span style="background-color: green">Example:</span>

```c++

// Factorial of n = 1*2*3*...*n

[[include]] <iostream>
using namespace std;

int factorial(int);

int main() {
    int n, result;

    cout << "Enter a non-negative number: ";
    cin >> n;

    result = factorial(n);
    cout << "Factorial of " << n << " = " << result;
    return 0;
}

int factorial(int n) 
{   // if we switch n and factorial position even
    // if we know it's commutaiive,
    // it no longer a tail recurisve function
    // left to right associative evaluated by the compiler
    if (n > 1) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}

```

![Factorial](Pretty%20images/Screenshot%202022-04-05%20225126.png)

Output:

Enter a non-negative number: 3

Factorial of 3 = 6

[Recursion](Pretty%20images/cpp-function-recursion-example.webp)

Print a reverse list

```c++
void reverse(Node *first)
{
    if (first != nullptr)
    {
        reverse(first->link);
        std::cout << first->info << ", ";
    }

}
```

## <span style="color:pink">In general, a recursive abstraction requires the following:</span>

- *base cases*, which are cases we can implement directly without recursion

- *recursive cases*, where we break down the problem into subproblems that are similar to the problem but “smaller,” meaning closer to a base case

---
---
Another non-math example, we write a recursive function to reverse the contents of an array. For an empty array or an array with one element, nothing needs to be done, constituting the base case. Otherwise, we reverse a smaller array, one that excludes the ends, and then swap the two ends:

```c++
// EFFECTS: Reverses the array starting at 'left' and ending at
//          (and including) 'right'.
void reverse(int *left, int *right) 
{
    if (left < right) 
    {
        reverse(left + 1, right - 1);
        int temp = *left;
        *left = *right;
        *right = temp;
    }
}
```

## <span style="color:	rgb(135,206,250)">Tail Recurrsion </span>

Now consider the efficiency of the reverse() function above. For an array of size n, it performs ` ⌊n/2⌋ swap operations, taking O(n) time `. The algorithm also uses O(n) space: each recursive call has an activation record, and there are **⌊n/2⌋+1** total calls.

The fundamental difference is that this `algorithm solves the subproblem after` doing the extra work for the original problem, i.e. swapping the two ends. An equivalent recursive implementation would be the following:

```c++
// EFFECTS: Reverses the array starting at 'left' and ending at
//          (and including) 'right'.
void reverse(int *left, int *right) 
{
    if (left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;
        reverse(left + 1, right - 1);
    }
}
```

Here, the recursive call is a tail call, meaning that the call is the last thing that happens in the function, and no work is done after the tail call returns. Since no work is done after the tail call, there is no need to retain the activation record of the caller, and it can be discarded.

```c++
static int factorial_helper(int n, int resultSoFar) 
{
    if (n == 0 || n == 1) 
    {
        return resultSoFar;
    }
    else 
    {
        return factorial_helper(n - 1, n * resultSoFar);
    }
}

int factorial(int n) 
{
    return factorial_helper(n, 1);
}
```

## <span style="color:	rgb(135,206,250)">Kinds of Recursion</span>

A function is tree recursive if a single invocation of the function can make more than one recursive call. 

Such a function subdivides a recursive case into multiple subproblems. 

The num_ducks() function above is tree recursive. Drawing out the recursive call graph for a tree-recursive function, we end up with a branching structure that resembles a tree, explaining the nomenclature.

![Tree recursion](Pretty%20images/Screenshot%202022-04-05%20233140.png)

---
---

## <span style="color:	rgb(135,206,250)">Structural Recursion</span>

### Recrusive Lists

```c++
struct Node {
    int data;
    Node *next;
};
```

This representation satisfies the requirements for a recursive abstraction:

The empty list is the base case, represented by a null pointer.

A non-empty list is a recursive case; it can be subdivided into the first node and the rest of the list, which represents a list in its own right.

Independent of its representation, a linked list can actually be defined recursively as either an empty list, or a data followed by a smaller list.

![recursive def for a list](Pretty%20images/Screenshot%202022-04-05%20233605.png)

As an <span style="color: rgb(127,255,0)">example</span>, the following is a recursive function to compute the `length` of a list:

```c++
// REQUIRES: node represents a valid list
// EFFECTS:  Computes the length of the list that starts at the
//           given node.
int length(const Node *list)
{
    if (list == nullptr) 
    {   // empty list
        return 0;
    } 
    else 
    {   // non-empty list
        return 1 + length(list->next);      // list->next is a smaller list
    }
}
```

---
---

As an <span style="color: rgb(127,255,0)">example</span>, the following is a recursive function to compute the `maximum element` of the list:

```c++
// REQUIRES: node represents a valid, non-empty list
// EFFECTS:  Returns the maximum element in the list that starts at
//           the given node.
int list_max(const Node *list) 
{
    if (list->next == nullptr) 
    {   // list has only one element
        return list->data;
    } 
    else
    {   // list has more than one element
        // compare first data to
        // max of rest of lest
        return std::max(list->data, list_max(list->next));  
    }
}
```

The base case is a list with one element. Such a list has an empty next list, so we check for that and return the list’s lone data. 

The recursive case computes the max of the rest of the list and then uses `std::max()` to determine the maximum of that item and the first item in the list. 

As always, we take the recursive leap of faith, assuming that the recursive call to `list_max()` computes the right answer for the smaller list.

---
---

## <span style="color: rgb(135,206,250)">Tree</span>

A tree is a data structure that is, naturally, tree recursive. A non-empty tree is subdivided into a data and several smaller trees. In this course, we only consider binary trees, where non-empty trees are subdivided into exactly two smaller trees.

![recrusive tree](Pretty%20images/recrusivetree.png)

Its characteristics:

1. The root is the node that originates the branching structure. In our diagrams, the root is pictured at the top of the tree.

2. A non-empty tree consists of a parent node and two child nodes. For a binary tree, there is a left child and a right child. Nodes that have the same parent are siblings.

3. A node whose children are all empty is a leaf.

4. The size of a tree is the number of elements it contains.

5. The height of a tree is the number of levels at which it has elements. Equivalently, it is the length of the longest path from the root to a leaf node.

---
---

### As an example, the following algorithm computes the size of a tree:

```c++
struct Node 
{
    int data;
    Node *left;
    Node *right;
};
```

![repre of a tree](Pretty%20images/repre%20of%20a%20tree.png)

```c++
// REQUIRES: node represents a valid tree
// EFFECTS:  Returns the number of elements in the tree represented
//           by the given node.
int size(const Node *tree) 
{
    if (!tree) 
    {   // empty tree
        return 0;
    }
    else 
    {   // non-empty tree
        return 1 + size(tree->left) + size(tree->right);
    }
}
```

The height of a tree is the number of levels it contains. An empty tree contains no levels, so its height is zero.

For a non-empty tree, we exploit the alternate definition of height, that it is the length of the longest path from root to leaf.

The longest such patch is just one node longer than the longest path in the child subtrees, since the root adds one additional node to the part of the path contained in a child. Thus, we compute the height as follows

```c++
// REQUIRES: node represents a valid tree
// EFFECTS:  Returns the height of the tree represented by the given
//           node.

int height(const Node *tree) {
    if (!tree) 
    {   // empty tree
        return 0;
    } 
    else 
    {   // non-empty tree
        return 1 + std::max(height(tree->left), height(tree->right));
    }
}

/// We use std::max() to obtain the longer path from the two child trees, then add one to the result to account for the root node.
```

---
---

## <span style="color:	rgb(135,206,250)">Tree Traversals</span>

>This algorithm processes a root data before processing any of the data in the children. It thus implements a preorder traversal.

```c++
// REQUIRES: node represents a valid tree
// MODIFIES: cout
// EFFECTS:  Prints each element in the given tree to standard out,
//           with each element followed by a space.

void print(const Node *tree) 
{
    if (tree) 
    {   // non-empty tree
        cout << tree->data << " ";
        print(tree->left);
        print(tree->right);
    }
}
```

Moving the print statement results in alternate orderings. The following implements an inorder traversal:

```c++
if (tree) 
{   // non-empty tree
    print(tree->left);
    cout << tree->data << " ";
    print(tree->right);
}
```

>The data in the left child is processed first, then the root data, then the data in the right child.

---
---

## <span style="color: rgb(0,255,0)">Binary Search Tree (BSTs)</span>

A `binary search tree (BST)` is a binary tree whose elements are stored in an order that maintains a sorting invariant. Specifically, a binary search tree is either:

1. Empty, or

2. A root data with two subtrees such that:

- The two subtrees are themselves binary search trees.

- Every element in the left subtree is strictly less than the root data.

- Every element in the right subtree is strictly greater than the root data.

![BST](Pretty%20images/BS.png)

More generally, the following algorithm determines whether or not a BST contains a particular value: `containst()`

- If the tree is empty, it does not contain the value.

- Otherwise, if the root data is equal to the value, the tree contains the element.

- If the value is less than the root element, it must be in the left subtree if it is in the tree, so we repeat the search on the left subtree.

- Otherwise, the value is greater than the root element, so it is in the right subtree if it is in the tree at all. Thus, we repeat the search on the right subtree.

The `first two cases` above are `base cases`, since they directly compute an answer. The latter two are `recursive cases`, and we take the recursive leap of faith that the recursive calls will compute the correct result on the subtrees.

```c++
// REQUIRES: node represents a valid binary search tree
// EFFECTS:  Returns whether or not the given value is in the tree
//           represented by node.
bool contains(const Node *node, int value) 
{
    if (!node) 
    {   // empty tree
        return false;
    } 
    else if (node->data == value) 
    {   // non-empty tree, equal to root
        return true;
    } 
    else if (value < node->data) 
    {   // less than root
        return contains(node->left, value);
    } 
    else 
    {   // greater than root
        return contains(node->right, value);
    }
}
```

This implementation is linear recursive, since at most one recursive call is made by each invocation of `contains()`.

Furthermore, every recursive call is a tail call, so the implementation is tail recursive. 

This example illustrates that the body of a linear- or tail-recursive function may contain more than one recursive call, as long as at most one of those calls is actually made.

---
---

we have the following algorithm:

- If the right subtree is empty, then the root is the maximum.

- Otherwise, the maximum item is the maximum element in the right subtree

```c++
// REQUIRES: node represents a valid non-empty binary search tree
// EFFECTS:  Returns the maximum element in the tree represented by
//           node.
int tree_max(const Node *node) 
{
    if (!node->right) 
    {   // base case
        return node->datum;
    } 
    else 
    {   // recursive case
        return tree_max(node->right);
    }
}
```

`tree_max()` is tail recursive, and it runs in time proportional to the height of the tree.

## <span style="color: rgb(0,255,0)">Binary Search Tree Interface</span>

The ` BinarySearchTree ` Interface

```c++
template <typename T>
class BinarySearchTree 
{
public:
    // EFFECTS:  Constructs an empty BST.
    BinarySearchTree();

    // EFFECTS:  Constructs a copy of the given tree.
    BinarySearchTree(const BinarySearchTree &other);

    // EFFECTS:  Replaces the contents of this tree with a copy of the
    //           given tree.
    BinarySearchTree & operator=(const BinarySearchTree &other);

    // EFFECTS:  Destructs this tree.
    ~BinarySearchTree();

    // EFFECTS:  Returns whether this tree is empty.
    bool empty() const;

    // EFFECTS:  Returns the number of elements in this tree.
    int size() const;

    // EFFECTS:  Returns whether the given item is contained in this
    //           tree.
    bool contains(const T &value) const;

    // REQUIRES: value is not in this tree
    // EFFECTS:  Inserts the given item into this tree.
    void insert(const T &value);

private:
    // Represents a single node of a tree.
    struct Node 
    {
        T datum;
        Node *left;
        Node *right;
        // INVARIANTS: left and right are either null or pointers to
        //             valid Nodes
    };

    // The root node of this tree.
    Node *root;
    // INVARIANTS: root is either null or a pointer to a valid Node
};  
```

The `contains()` member function differs from the one we defined before; the member function just takes in a data item, while our previous definition operates on a node as well.

```c++
template <typename T>
class BinarySearchTree 
{
    ...
public:
    bool contains(const T &value) const 
    {
        return contains(root, value);
    }

private:
    static bool contains(const Node *node, const T &value) 
    {
        if      (!node)                { return false; }
        else if (node->datum == value) { return true;  } 
        else if (value < node->datum)  { return contains(node->left, value);  } 
        else                           { return contains(node->right, value); }
    }

    Node *root;
};

```

Observe that `contains()` does not refer to a BinarySearchTree or any of its members. Thus, there is no need for it to have a `this` pointer to a `BinarySearchTree` object. We can declare the function as a `static` member function to eliminate the this pointer.

A static member function is also not associated with an individual object, and it cannot refer to non-static member variables.

## <span style="color: rgb(0,255,0)">BST-Based Set</span>

```c++
template <typename T>
class BSTSet 
{
public:
    // EFFECTS: Inserts the given value into this set, if it is not
    //          already in the set.
    void insert(const T &value)  { if (!elts.contains(value)) { elts.insert(value); } }

    // EFFECTS: Returns whether value is in this set.
    bool contains(const T &value) const { return elts.contains(value); }

    // EFFECTS: Returns the size of this set.
    int size() const  { return elts.size(); }

    private:
    BinarySearchTree<T> elts;
};

```

Unfortunately, our BST implementation does not guarantee that it will be balanced. In fact, inserting items in increasing order results in a maximally unbalanced tree as in Figure 88, resembling a list rather than a tree structure.

![Unbalanced tree](Pretty%20images/Ubnbalanced%20tree.png)

Inserting elements into a non-balancing binary search tree in order results in a linear structure, with height equal to the number of elements.


## <span style="color: rgb(135,206,250)">Maps and Pairs</span>

A map is a data structure that maps keys to values. It is thus an associative data structure, since it associates a value with each key. As an example, we may want to associate exam scores with individual test takers:

```c++
std::map<std::string, int> scores;
scores["aliceywu"]   = 100;
scores["akamil"]     = 23;
scores["taligoro"]   = 100;
scores["jjuett"]     = 73;
cout << scores["akamil"] << endl;    // prints 23
cout << scores["aliceywu"] << endl;  // prints 100
```

![map1](Pretty%20images/map1.png)

The `map` class template has two required `template parameters`, the first for the `key type` and the second for the `value type`. We are mapping string IDs to integer scores, so we use a `map<string, int>`

---
---
---

## <span style="color: rgb(135,206,250)">Solving problem with Recursion</span>


```c++


```

---
---