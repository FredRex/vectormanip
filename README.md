# Vector Manipulation Program
## Submission for VolHacks2019

This is a simple terminal terminal program that can manipulate multiple [mathematical vectors](https://en.wikipedia.org/wiki/Vector_\(mathematics_and_physics\)).

## Build
To build the program, compile `main.cpp` and `vector.cpp` together.

## Usage
Once executed, you will be given a prompt. You define vectors in terms of a capital letter
The available commands are:
```
Commands:
q - quit
c - create
r - remove
l - list
w - write
f - load file
a - assign
d - dot product
h - help
```
If you see that the prompt has `!> `, that means you made an error, and nothing has changed.

### Create
Create a new vector. The syntax is `c <letter> {<x>i <y>j} | {<m> <d>(r)}`.
This program allows for creating vectors in two different formats: components or magnitude/direction. Examples:
```
 > c A 3.6i 24.1j   //3.6 right plus 24.1 up
 > c Q 64 30        //64 units in the direction of 30 degrees
 > c T 40 1.51r     //40 units in the direction of 1.51 radians
```

### Remove
Removes a vector from the map
```
 > r G
```
G is removed here

### List
Prints a list of all the vectors in the map
```
 > l
```

### Write
Write out the current vectors in memory to a file that can be loaded later
```
 > w file.txt
```

### Load File
Takes a file made from "write" and overwrites the map with the vectors in the file
```
 > f file.txt
```
This redefines the current map with the map in the file "file.txt"

### Assign
Defines a vector in terms of vectors already in the map, you can use coefficients to scale vectors as you write them, you ***MUST*** use a sign at the beginning of each vector. No spaces are legal in the expression
```
 > a H -2.092A+3.278B
 > a A -A
 > a E +A+B+C+D
 > a W -0.9W
```

### Dot Product
Prints out the [dot product](https://en.wikipedia.org/wiki/Dot_product) of two vectors.
```
 > d AB
```


Feel free to submit any PRs but I might not pay attention to this repository.