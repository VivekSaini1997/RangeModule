#include "Range.h"
#include <map>
#include <iostream>
#include <algorithm>

// nothing to do for constructor or destructor
Range::Range() {

}

Range::~Range() {

}

/*
    Adds a range to the data structure, merging together existing 
    ranges if neccessary
    
    start: The start of the selection range
    end: The end of the selection range
    Time Complexity: O(logn)
*/
void Range::Add(int start, int end){
    // find the maximal ranges whose starting point is less than or equal to that of
    // the "start" and "end" points
    auto startIter = table.lower_bound(start);
    auto endIter = table.lower_bound(end);
    // if "end" is less than every range in the table
    // this range is before the beginning, 
    // so insert a new range there
    if (endIter == table.end()){
        table.insert(std::make_pair(start, end));
    // if there is no entire existing range in between "start" and "end"
    } else if (startIter == endIter){
        // if "start" lies in an existing range while "end" does not, 
        // then we update the existing range to go up to "end"
        // i.e. the union of the existing range and the new range 
        // defined by "start" and "end"
        if (start <= startIter->second && end > startIter->second){
            startIter->second = end;
        }
        // if both "start" and "end" lie outside of an existing range
        // then insert a new range into the data structure from "start" to "end"
        else if (start > startIter->second){
            table.insert(std::make_pair(start, end));
        }
    // otherwise, there are one or more entire ranges between "start" and "end"
    // in this case, delete all the ranges between "start" and "end", as well as 
    // potentially the ranges they lie in
    // and add a new range that is the union of all the ranges deleted and 
    // the range formed by "start" and "end"  
    } else {
        // if "start" lies in an existing range
        // move the "start" value to the beginning of the existing range
        // also include this range when deleting (by incrementing the iterator)
        if (start <= startIter->second && startIter != table.end()){
            start = startIter->first;
            startIter++;
        }
        // if "end" lies in an existing range
        // move the "end" value to the end of the existing range
        // this range will always be included for deletion 
        if (end < endIter->second){
            end = endIter->second;
        }
        // delete the neccessary ranges from the data structure
        // and replace them with the union of those ranges and the new range
        table.erase(endIter, startIter);
        table.insert(std::make_pair(start, end));
    }
}

/*
    Removes ranges that exist within the data structure
    that intersect with the selection range

    start: The start of the selection range
    end: The end of the selection range
    Time Complexity: O(logn)
*/
void Range::Delete(int start, int end){
    // find the maximal ranges whose starting point is less than or equal to that of
    // the "start" and "end" points
    auto startIter = table.lower_bound(start);
    auto endIter = table.lower_bound(end);
    // if "end" is less than every range in the table
    // this range is before the beginning, 
    // so there is nothing to do but return
    if (endIter == table.end()){
        return;
    }
    // only try to delete if there exist ranges between "start" and "end"
    // if startIter == endIter and start > startIter->second, that means
    // "start" and "end" are between ranges, so nothing needs to be done
    if ((startIter == endIter && start <= startIter->second) || startIter != endIter){
        // store the start and end points of the ranges that "start" and "end" point to
        int oldStart = startIter->first;
        int oldEnd = endIter->second;
        // erase every interval between and including the ones containing "start" and "end"
        // only include "start" if lies in an existing range
        // need to create a temporary iterator and increment it in order 
        // to possibly include the interval of startIter when erasing            
        auto vt = startIter;
        if (vt != table.end() && start < vt->second){
            vt++;
        }
        table.erase(endIter, vt);
        // then if "start" isn't on the boundary, i.e. not the same as the old range's start  
        // then insert a range from the old range's start to "start"
        if (start != oldStart && startIter != table.end()){
            table.insert(std::make_pair(oldStart, start));
        }
        // likewise, if "end" existed in the old range
        // then insert a range from "end" to the old range's end
        if (end < oldEnd){
            table.insert(std::make_pair(end, oldEnd));
        }
    }
}

/*
    Returns a list of ranges that exist within the data structure
    that intersect with the selection range

    start: The start of the selection range
    end: The end of the selection range
    Time Complexity: O(n)
*/
std::vector<std::pair<int, int>> Range::Get(int start, int end){
    // need to go through the map in reverse because of how it's organized
    auto startIter = table.lower_bound(start);
    auto endIter = table.lower_bound(end);

    std::vector<std::pair<int, int>> ret;
    // if they're both part of the same range
    if (startIter == endIter){
        // if "start" lies in the range,
        // then there is something to return
        // otherwise there is nothing
        if (startIter != table.end() && start < startIter->second){
            ret.push_back(std::make_pair(start, std::min(end, startIter->second)));
        }
    // otherwise "start" and "end" lie in different ranges
    } else {
        // first account for the range that startIter points to,
        // if "start" lies in said range, add the interval from "start" to
        // the end of said range to our return list 
        auto iter = startIter;
        if (start < iter->second && iter != table.end()){
            ret.push_back(std::make_pair(start, iter->second));
        }
        iter--;
        // add add the ranges that lie between "start" and "end" to the return list,
        // excluding the ranges that startIter and endIter point to
        for (; iter != endIter; iter--){
            ret.push_back(std::make_pair(iter->first, iter->second));
        }
        // now add the range that endIter points to
        // the end of this added range is the minimum of "end" and its own end
        ret.push_back(std::make_pair(iter->first, std::min(iter->second, end)));
    }
    // return the list of ranges
    return ret;
    
}

/*
    Convenience function to print the start and endpoints of the range in reverse order.
    Returns nothing, but prints to stdout.
    Used for Debugging.
*/ 
void Range::printAll() const{
    for (auto&& elem : table){
        std::cout << elem.second << ", " << elem.first << ", ";
    }
    std::cout << std::endl;
}


/*
    Convenience function to serialize the range into a list of start and end points.
    Returns a list in reverse order.
    Used for Testcase Verification.
*/ 
#include <vector>
std::vector<int> Range::toVec() const{
    std::vector<int> vec;
    for (auto&& elem : table){
        vec.push_back(elem.second);
        vec.push_back(elem.first);
    }
    return vec;
}