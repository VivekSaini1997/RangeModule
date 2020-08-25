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
    auto v1 = table.lower_bound(start);
    auto v2 = table.upper_bound(end);
    // if the start of the range is greater than what exists in the table
    // insert normally
    if (v1 == table.end()){
        table.insert(std::make_pair(end, start));
    }
    // like wise if they're between values
    // it->key is the start of the range and it->val is the end

}

void Range::deleteRange(int start, int end){

}

void Range::getRange(int start, int end){

}

void Range::printAll(){
    for (auto&& [key, val] : table){
        std::cout << key << std::endl;
    }
}