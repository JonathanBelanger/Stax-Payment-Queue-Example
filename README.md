# Stax-Payment-Queue-Example

The code in this repository was written as an example of my C++ coding and unit testing style.  The original request stated the following:

> Create a C++ program that implements a linked list. The linked list should be a doubly linked list, allowing movement forward and backward. This program should allow you to add and remove nodes from the list. Each node should contain a reference to application data. The program does not have to provide user interaction. Please include units tests for the program. The program can be submitted by including a link to your solution in Github.

*Code and other information*:

* src/Queue.hxx - Contains 2 template classes, `Node` and `QueueHead`.
* test/TestQueue.cxx - Contains the Unit Testing code to fully test the `Node` and `QueueHead` classes.
* TestResults.txt - Contains the results of a run of the Unit Tests

> *Note*:
> * The src/Queue.hxx does not contain any include statements.  Therefore, it can be used in just about any installation with a C++ compiler.
> * The code was implemented and tested using the C++20 standard.  It may work with other standards with little or not code changes.