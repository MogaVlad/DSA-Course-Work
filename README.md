# DSA-Course-Work

Data structures and abstract data types (ADTs) implemented **from scratch in C++** for the first-year Data Structures & Algorithms course at Babeș-Bolyai University. Each assignment implements a container ADT on top of a specific underlying representation, with its own iterator and a test suite. The core structures are built by hand rather than relying on STL containers.

## Assignments

### Assignment 1 — Bag (Dynamic Array)
ADT **Bag** (multiset) implemented using **two parallel dynamic arrays**: one storing unique elements (`U`) and one storing their frequencies (`P`). Supports add, remove, frequency lookup, and membership, with amortized dynamic resizing.

### Assignment 2 — Priority Queue (Doubly-Linked List)
ADT **Priority Queue** implemented on a **doubly-linked list (DLL)**. Elements are dequeued by priority.

### Assignment 3 — MultiMap (Doubly-Linked List on Array)
ADT **MultiMap** implemented using a **doubly-linked list on array (DLLA)** with unique keys — a linked list whose nodes live in a contiguous array with explicit `next`/`prev` index links rather than pointers, managing its own free list.

### Assignment 4 — Map (Hashtable, Open Addressing)
ADT **Map** implemented using a **hashtable with open addressing and quadratic probing**. Includes a map iterator and both short and extended test suites.

### Assignment 5 — Matrix (Binary Search Tree)
ADT **Matrix** with its non-zero elements stored in a **binary search tree (BST)** using a linked representation with dynamic allocation.

## Structure

Each assignment folder contains an `include/` directory (headers, iterator, tests) and a `src/` directory (implementations).
