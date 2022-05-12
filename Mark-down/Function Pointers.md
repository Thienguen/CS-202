```c++

// 1. empty?
//    head = tail = new Node
// 2. insert at the front before 
//    head = new Node {value, nullptr, head }
// 3. insert at the end of the linked list
//    newnode = new Node{value}
//    newnode->prev = tail
//    tail = newnode
// 4. in the middle of the list
//    newnode = new Node{vakue}
//    newnode->next = pos->prev->next
//    newnode->prev = pos->prev

//    pos->prev->next = newnode
//    pos->prev = newnode

// 1. is empty or it is a default
// dothing thing, or throw shit

// 2. is it the beginining node
//     head = head->next
//     if (head != nullptr)
//         head->prev = nullptr
//     else 
//         tail = pos->prev
//     delete

//     else it's somewhere in thelist
//     connect previous node to the pos->nest

//     pos->prev->next = pos->next

//     if (pos->next != nullptr)
//     pos->next->prev = pos->next

//     pos == tail
//     update tail pointer
//     tail = pos->prev

// delete pos
```