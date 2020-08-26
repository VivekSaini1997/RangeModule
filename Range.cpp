#include "Range.h"
#include <map>
#include <iostream>
#include <algorithm>

// nothing to do for constructor or destructor
Range::Range() {

}

Range::~Range() {

}

// adds a range to the data structure
void Range::addRange(int start, int end){
    auto v1 = table.lower_bound(start);
    auto v2 = table.lower_bound(end);
    // if the end of the range is less than what exists in the table
    // insert normally
    if (v2 == table.end()){
        table.insert(std::make_pair(start, end));
        return;
    }
    // handle if both v1 and v2 reference the same point
    // these are simple cases
    if (v1 == v2){
        // if they are before an end point i.e. overlapping
        // do nothing
        if (start <= v1->second && end <= v1->second){
            // pass
        }
        // if the new interval start lies in an existing interval
        // while the new end does not, need to update the existing elements end
        if (start <= v1->second && end > v1->second){
            v1->second = end;
        }
        // if they're both after an end point
        // add a new interval
        if (start > v1->second){
            table.insert(std::make_pair(start, end));
        }
        return;
    } else {
        #if 0 
        // like wise if they're between values
        // it->key is the start of the range and it->val is the end
        if ((v1 == table.end() || start > v1->second) && end >= v2->second){
            // if they don't both lie in an interval and are different, then 
            // we must keep removing elements
            // for now just print to make sure i'm doing this correctly
            table.erase(v2, v1);
            table.insert(std::make_pair(start, end));
        }
        // if the start of the new region lies in an existing region
        // and the end of the new region does not, we need to remove the 
        // interval the start region lies in and create a new interval that starts
        // where that region started and ends at "end"
        else if (start <= v1->second && end >= v2->second){
            int w1 = v1->first;
            table.erase(v2, ++v1);
            table.insert(std::make_pair(w1, end));
        }
        // if the end of the new region lies in an existing region
        // while the start does not, we need to remove the interval the 
        // ending region lies in and create a new interval that starts at "start"
        // and ends where the new region ended
        else if ((v1 == table.end() || start > v1->second) && end < v2->second){
            int w2 = v2->second;
            table.erase(v2, v1);
            table.insert(std::make_pair(start, w2));
        }
        // and if both occur, we do both
        else if (start <= v1->second && end < v2->second){
            int w1 = v1->first;
            int w2 = v2->second;
            table.erase(v2, ++v1);
            table.insert(std::make_pair(w1, w2));
        }
        #else 
        if (start <= v1->second && v1 != table.end()){
            start = v1->first;
            v1++;
        }
        if (end < v2->second){
            end = v2->second;
        }
        table.erase(v2, v1);
        table.insert(std::make_pair(start, end));
        #endif
    }
}
// deletes a range from the 
void Range::deleteRange(int start, int end){
    auto v1 = table.lower_bound(start);
    auto v2 = table.lower_bound(end);
    // if the end of the range is less than what exists in the table
    // there is nothing to delete
    if (v2 == table.end()){
        return;
    }
    // handle if both v1 and v2 reference the same point
    // these are simple cases
    if (v1 == v2){
        // if they are before an end point i.e. overlapping
        // then split it up into sections
        if (start <= v1->second){
            int w1 = v1->first;
            int w2 = v1->second;
            // first erase the existing entry
            table.erase(v1);
            // if the start isn't on the boundary,  
            // then add a left entry from w1 to start of deletion range
            if (start != w1){
                table.insert(std::make_pair(w1, start));
            }
            // likewise for end and a right entry
            // if the endpoint of removal lies within this interval and not on the boundary
            // reinsert
            if (end < w2){
                table.insert(std::make_pair(end, w2));
            }
        }
        // otherwise 
        return;
    } else {
        // otherwise, if they cover more than one range, handle that as well
        int w1 = v1->first;
        int w2 = v2->second;
        // erase every interval between and including the ones 
        // containing start and end
        // need to create a temporary iterator and increment it in order 
        // to include the interval of v1 when erasing
        auto vt = v1;
        if (vt != table.end()){
            vt++;
        }
        table.erase(v2, vt);
        // if the start isn't on the boundary,  
        // then add a left entry from w1 to start of deletion range
        if (start != w1 && v1 != table.end()){
            table.insert(std::make_pair(w1, start));
        }
        // likewise for end and a right entry
        // if the endpoint of removal lies within this interval and not on the boundary
        // reinsert
        if (end < w2){
            table.insert(std::make_pair(end, w2));
        }
    }
}

std::vector<std::pair<int, int>> Range::getRange(int start, int end){
    // need to go through the map in reverse because of how it's organized
    auto v1 = table.lower_bound(start);
    auto v2 = table.lower_bound(end);

    std::vector<std::pair<int, int>> ret;
    // if they're both part of the same interval
    if (v1 == v2){
        // if the starting point lies in the interval,
        // then there is something to return
        // otherwise there is nothing
        if (v1 != table.end() && start < v1->second){
            ret.push_back(std::make_pair(start, std::min(end, v1->second)));
        }
        return ret;
    }
    
    // first account for the first interval 
    if (start >= v1->second || v1 == table.end()){
        v1--;
        start = v1->first;
    }
    // std::cout << start << std::endl;
    auto it = v1;
    if (start != it->first){
        std::cout << start << ", " << it->second << std::endl;
        ret.push_back(std::make_pair(start, it->second));
        it--; 
    }
    for (; it != v2; it--){
        std::cout << it->first << ", " << it->second << std::endl;
        ret.push_back(std::make_pair(it->first, it->second));

    }
    ret.push_back(std::make_pair(it->first, std::min(it->second, end)));
    
    return ret;
    
}

void Range::getUpper(int val){
    std::cout << table.upper_bound(val)->first << std::endl;
}

void Range::getLower(int val){
    std::cout << table.lower_bound(val)->first << std::endl;
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