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
    Adds a range to the data structure
    Time Complexity: O(logn)
*/
void Range::addRange(int start, int end){
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
    // in this case, remove all the ranges between "start" and "end", as well as 
    // potentially the ranges they lie in
    // and add a new range that is the union of all the ranges removed and 
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
        // remove the neccessary ranges from the data structure
        // and replace them with the union of those ranges and the new range
        table.erase(endIter, startIter);
        table.insert(std::make_pair(start, end));
    }
}

/*
    Removes a range to the data structure
    Time Complexity: O(logn)
*/
void Range::deleteRange(int start, int end){
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
    // if there is no entire existing range in between "start" and "end"
    if (startIter == endIter){
        // if "start" lies in an existing range
        if (start <= startIter->second){
            // store the start and end points of the ranges that "start" and "end" point to
            int oldStart = startIter->first;
            int oldEnd = endIter->second;
            // first erase the existing range
            table.erase(startIter);
            // then if "start" isn't on the boundary, i.e. not the same as the old range's start  
            // then insert a range from the old range's start to "start"
            if (start != oldStart){
                table.insert(std::make_pair(oldStart, start));
            }
            // likewise, if "end" existed in the old range
            // then insert a range from "end" to the old range's end
            if (end < oldEnd){
                table.insert(std::make_pair(end, oldEnd));
            }
        }
    } else {
        // otherwise, if they cover more than one range, handle that as well
        int oldStart = startIter->first;
        int oldEnd = endIter->second;
        // erase every interval between and including the ones containing "start" and "end"
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

std::vector<std::pair<int, int>> Range::getRange(int start, int end){
    // need to go through the map in reverse because of how it's organized
    auto startIter = table.lower_bound(start);
    auto endIter = table.lower_bound(end);

    std::vector<std::pair<int, int>> ret;
    // if they're both part of the same interval
    if (startIter == endIter){
        // if the starting point lies in the interval,
        // then there is something to return
        // otherwise there is nothing
        if (startIter != table.end() && start < startIter->second){
            ret.push_back(std::make_pair(start, std::min(end, startIter->second)));
        }
     // otherwise start and end lie in different intervals
    } else {
        // first account 
        if (start < startIter->second && startIter != table.end()){
            ret.push_back(std::make_pair(start, startIter->second));
        }
        startIter--;
        for (; startIter != endIter; startIter--){
            ret.push_back(std::make_pair(startIter->first, startIter->second));

        }
        ret.push_back(std::make_pair(startIter->first, std::min(startIter->second, end)));
    }
    return ret;
    
}

void Range::printAll() const{
    for (auto&& elem : table){
        std::cout << elem.second << ", " << elem.first << ", ";
    }
    std::cout << std::endl;
}

#include <vector>
std::vector<int> Range::toVec() const{
    std::vector<int> vec;
    for (auto&& elem : table){
        vec.push_back(elem.second);
        vec.push_back(elem.first);
    }
    return vec;
}