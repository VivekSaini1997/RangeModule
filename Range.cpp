#include "Range.h"
#include <map>
#include <iostream>

// nothing to do for constructor or destructor
Range::Range() {

}

Range::~Range() {

}

// adds a range to the data structure
void Range::addRange(int start, int end){
    auto v1 = table.upper_bound(start);
    auto v2 = table.lower_bound(end);
    // if the end of the range is less than what exists in the table
    // insert normally
    if (v1 == table.end()){
        table.insert(std::make_pair(start, end));
        return;
    }
    // handle if both v1 and v2 reference the same point
    // these are simple cases
    if (v1 == v2){
        // if they are before an end point i.e. overlapping
        // do nothing
        if (start < v1->second && end < v1->second){
            // pass
        }
        // if the new interval start lies in an existing interval
        // while the new end does not, need to update the existing elements end
        if (start < v1->second && end > v1->second){
            v1->second = end;
        }
        // if they're both after an end point
        // add a new interval
        if (start > v1->second){
            table.insert(std::make_pair(start, end));
        }
        return;
    } else {
        // like wise if they're between values
        // it->key is the start of the range and it->val is the end
        if (start > v1->second && end >= v2->second){
            // if they don't both lie in an interval and are different, then 
            // we must keep removing elements
            // for now just print to make sure i'm doing this correctly
            table.erase(v2, v1);
            table.insert(std::make_pair(start, end));
        }
    }
}

void Range::deleteRange(int start, int end){

}

void Range::getRange(int start, int end){

}

void Range::getUpper(int val){
    std::cout << table.upper_bound(val)->first << std::endl;
}

void Range::getLower(int val){
    std::cout << table.lower_bound(val)->first << std::endl;
}


void Range::printAll(){
    for (auto&& elem : table){
        std::cout << elem.second << std::endl << elem.first << std::endl;
    }
}