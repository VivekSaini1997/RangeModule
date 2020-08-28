#ifndef _RANGE_H_
#define _RANGE_H_

#include <map>
#include <functional>
#include <vector>

class Range
{
private:
    // the map used to contain information about ranges
    // each key maps to a given range's start and the corresponding value
    // maps to said range's end
    std::map<int, int, std::greater<int>> table;
public:
    Range();
    ~Range();

    /*
        Adds a range to the data structure, merging together existing 
        ranges if neccessary
        
        start: The start of the selection range
        end: The end of the selection range
        Time Complexity: O(logn)
    */
    void Add(int, int);
    /*
        Removes ranges that exist within the data structure
        that intersect with the selection range

        start: The start of the selection range
        end: The end of the selection range
        Time Complexity: O(logn)
    */
    void Delete(int, int);

    /*
        Returns a list of ranges that exist within the data structure
        that intersect with the selection range

        start: The start of the selection range
        end: The end of the selection range
        Time Complexity: O(n)
    */
    std::vector<std::pair<int, int>> Get(int, int);

    /*
        Convenience function to print the start and endpoints of the range in reverse order.
        Returns nothing, but prints to stdout.
        Used for Debugging.
    */ 
    void printAll() const;

    /*
        Convenience function to serialize the range into a list of start and end points.
        Returns a list in reverse order.
        Used for Testcase Verification.
    */ 
    std::vector<int> toVec() const;
};
#endif