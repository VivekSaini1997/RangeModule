#ifndef _RANGE_H_
#define _RANGE_H_

#include <map>

class Range
{
private:
    std::map<int, int> table;
public:
    Range(/* args */);
    ~Range();

    void addRange(int, int);
    void deleteRange(int, int);
    void getRange(int, int);

    // print everything
    void printAll();
};


#endif