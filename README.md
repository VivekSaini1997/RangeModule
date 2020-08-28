# Range Module

## Summary 
An implementation of the Range Module. Supports Adding, Deleting, and Getting Ranges as specified by PDF. Can be used as a standalone project or as a module for another. Standalone variant also runs a suite of testcases to verify functionality.

## Dependancies
 - g++ (if running standalone)
 - make (if running standalone)
 
## Build
### As a standalone project
In order to compile the program for standalone usage, run `make` or `make install`.

### As part of another program
The only files required for external operation are Range.h and Range.cpp. No special compiler options neccessary.
 
## Usage
### As a standalone project
The standalone variant runs a myriad of different test cases verifying the correctness of the algorithm. To run, execute the following after building:
```
./range
```
For a given test, the program will output:
```
--------------------------------------
Test for #<testcasename> : <status>
--------------------------------------
```
where `testcasename` is the name of the function called in Tests.cpp and `status` is one of `SUCCESS` or `FAILURE`. In the event of a `FAILURE`, the program output and expected output are displayed to screen as well.


### As part of another program
Include the Range.h header file into your project and place both the Range.h header file and Range.cpp source file in suitable locations before building, then use as you would any other C++ library.

## Time Complexities 
Where N is the number of elements in the data structure

### Add: O(N)
It is possible that you have to remove all of the existing elements in the data structure before inserting a new one. This is done through the use of an iterator through all the elements, which takes O(N) time. Therefore the time taken is O(N).

### Delete: O(N)
Similar to above, it is possible that you have to remove all of the existing elements in the data structure. Therefore the time taken is O(N).

### Get: O(N)
Similar to above, it is possible that you have to traverse all of the existing elements in the data structure. Therefore the time taken is O(N).

## Space Complexity
### O(N)
Each element in the data structure takes a constant amount of space, so N of them will take up O(N) space.
