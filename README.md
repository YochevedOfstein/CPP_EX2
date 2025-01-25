

# System Programing 2 - assignmant 2

This project is a continuation of the previous assignment, adding functionality for various graph operations such as addition, subtraction, and multiplication. It also includes comparison operators and other utility functions for working with graphs.

## Graph
As in the previous assignment, the graph is represented using an adjacency matrix. The implementation includes various algorithms which are all in the class `Graph.cpp`. Additionally, in this assignment we incorporate several operations on graphs in this class.

### Operators
**Arithmetic operators:**
* *Addition* `+`: addition of two graphs, where each corresponding edge weight is added together to form a new graph (both graphs must be the same size - same amount of verticies). 
* *Subtraction* `-`: subtraction of one graph from another, where each corresponding edge weight is subtracted to form a new graph (both graphs must be the same size - same amount of verticies). .
* *Multiplication* `*`: 
    1. multiplication of two graphs, where each corresponding edge weight is multiplied together to form a new graph.
    2. multiplication of an scaler with a graph - the weight of every edge a the graph.

**Assignment Operators:**
* *Compound Addition* `+=`: the current graph is modified by adding another graph to it.
* *Compound Subtraction* `-=`: the current graph is modified by subtracting another graph from it.
* *Compound Multiplication* `*=`: the current graph is modified by multiplying it with another graph or scaler.
* *Compound Division* `/=`: the current graph is modified by dividing it by a scaler.

**Unary operators:**
* *Unary Plus* `+graph`: returns a copy of the graph as is.
* *Unary Minus* `-graph`: returns a copy of the graph with all edge weights negated.

**Increment and Decrement Operators:**
* *Prefix*:
    1. Prefix increment `++graph` - increments all edge weights of the graph by 1 and returns a reference to the modified graph.
    2. Prefix decrement - `--graph` decrements all edge weights of the graph by 1 and returns a reference to the modified graph.
* *Postfix*:
    1. Postfix increment `graph++` - increments all edge weights of the graph by 1 but returns a copy of the graph before the increment.
    2. Postfix decrement `graph--` - decrements all edge weights of the graph by 1 but returns a copy of the graph before the decrement.

**Comparison operators:**
* *Equality* `==`: checks if two graphs are equal, if they have the same number of vertices and corresponding edge weights.
* *Inequality* `!=`: checks if graphs are not equal.
* *Greater Than* `>`: checks if the graph is greater than the other by comparing the number of vertices and edge weights.
* *Less Than* `<`: checks if the graph is less than the other by comparing the number of vertices and edge weights.
* *Greater Than or Equal To* `>=`: checks if the the graph is greater or equal to another garph.
* *Less Than or Equal To* `<=`: checks if the the graph is less or equal to another garph.

**Stream insersion operator:**
* `<<` : enables printing the adjacancy matrix of a graph.

## Tests
The project includes tests written using the `doctest.h` framework. All of the tests are in `Test.cpp`, inclusing the tests from last assignment. These tests ensure the correctness and robustness of the implemented graph algorithms and graph operations.




