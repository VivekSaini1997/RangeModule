#ifndef _RANGE_H_
#define _RANGE_H_

#include <map>
#include <functional>

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
    void printAll();

    void getUpper(int val);
    void getLower(int val);
};


#endif