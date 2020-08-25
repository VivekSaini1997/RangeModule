#ifndef _RANGE_H_
#define _RANGE_H_

#include <map>
#include <functional>
#include <vector>

class Range
{
private:
    std::map<int, int, std::greater<int>> table;
public:
    Range(/* args */);
    ~Range();

    void addRange(int, int);
    void deleteRange(int, int);
    void getRange(int, int);

    // print everything
    void printAll() const;

    void getUpper(int val);
    void getLower(int val);

    // serializes range into a list of points
    // used for testing
    std::vector<int> toVec() const;
};


#endif