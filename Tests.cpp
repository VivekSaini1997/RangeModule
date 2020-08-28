#include "Tests.h"
#include "Range.h"
#include <assert.h>
#include <iostream>

// macro used to declutter output with success messages
// only prints out failed testcases if enabled
#define ONLY_PRINT_FAILURES 0


/*
    Function used to verify correctness of the addRange and removeRange functions
    Checks input "range" against "ans" and prints message dependant on whether they match or not

    range: Range object to be verified
    ans: expected output from toVec() called on Range object
    funcname: name of function calling verifyAnswer
*/
void verifyAnswer(const Range& range, const std::vector<int>& ans, const char* funcname){
    bool success = (range.toVec() == ans);
#if ONLY_PRINT_FAILURES 
    if (success){
        return;
    }
#endif
    // if testcase succeeded, just print success
    std::cout << "Test for #" << funcname << " : ";
    if (success){
        std::cout << "SUCCESS" << std::endl;
    // otherwise, print the recieved value and the expected value
    } else {
        std::cout << "FAILURE" << std::endl;
        std::cout << "Output : ";
        range.printAll();
        std::cout << "Expected : ";
        for (auto&& elem: ans){
            std::cout << elem << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

/*
    Function used to verify correctness of the getRange function
    Checks input "actual" against "expected" and prints message dependant on whether they match or not

    actual: actual output from getRange function
    ans: expected output from getRange function 
    funcname: name of function calling verifyAnswer
*/
void verifyAnswer(const std::vector<std::pair<int, int>>& actual, 
    const std::vector<std::pair<int, int>>& expected, const char* funcname){
    bool success = (actual == expected);
#if ONLY_PRINT_FAILURES 
    if (success){
        return;
    }
#endif
    std::cout << "Test for #" << funcname << " : ";
    // if testcase succeeded, just print success
    if (success){
        std::cout << "SUCCESS" << std::endl;
    // otherwise, print the recieved value and the expected value
    } else {
        std::cout << "FAILURE" << std::endl;
        std::cout << "Output : ";
        for (auto&& elem : actual){
            std::cout << "(" << elem.first << ", " << elem.second << "), ";
        }
        std::cout << std::endl;
        std::cout << "Expected : ";
        for (auto&& elem: expected){
            std::cout << "(" << elem.first << ", " << elem.second << "), ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

// tests adding a range that is already contained in another
// should add nothing to data structure
void addIntoExistingRegion()
{
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(2, 8);
    std::vector<int> ans = {10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range into an empty region
// should add normally to data structure
void addIntoEmptyRegion()
{
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(11, 20);
    std::vector<int> ans = {20, 11, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that overlaps an existing one
// should extend existing range's start and end
void addOverExistingRegion()
{
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(15, 35);
    std::vector<int> ans = {50, 40, 35, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that overlaps an existing one but has the same start point
// should extend existing range's end
void addOverExistingRegionLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(20, 35);
    std::vector<int> ans = {50, 40, 35, 20, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that overlaps an existing one but has the same end point
// should extend existing range's start 
void addOverExistingRegionRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(15, 30);
    std::vector<int> ans = {50, 40, 30, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that overlaps multiple existing ranges
// should merge into the union of all ranges involved
void addOverMultipleRegions(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(60, 70);
    range.addRange(80, 90);

    range.addRange(15, 75);
    std::vector<int> ans = {90, 80, 75, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that contains an existing range and partially contains another
// should merge all existing ranges
void addPartialOverlapLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(5, 35);
    std::vector<int> ans = {35, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// also tests adding a range that fully contains an existing range and partially contains another
// should merge all existing ranges
void addPartialOverlapRight(){
    Range range = Range();
    range.addRange(10, 20);
    range.addRange(30, 40);
    range.addRange(5, 35);
    std::vector<int> ans = {40, 5};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that partially contains two ranges
// should merge all existing ranges
void addPartialOverlapBoth(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(5, 35);
    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding range that overlaps leftmost existing range
// should extend that range both ways
void addOverLeftMostRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(-5, 15);
    std::vector<int> ans = {50, 40, 30, 20, 15, -5};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding range that overlaps rightmost existing range
// should extend that range both ways
void addOverRightMostRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(35, 55);
    std::vector<int> ans = {55, 35, 30, 20, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding range that overlaps existing range in the middle
// should extend that range both ways
void addOverMiddleRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30); 
    range.addRange(40, 50);
    range.addRange(15, 35);
    std::vector<int> ans = {50, 40, 35, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests adding a range that contains an existing range and partially contains another
// also starts at the same start point as the existing range
// should merge all ranges
void addPartialOverlapBoundaryLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(0, 35);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

// tests adding a range that contains an existing range and partially contains another
// also ends at the same end point as the existing range
// should merge all ranges
void addPartialOverlapBoundaryRight(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(5, 40);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

// tests adding a range that contains two existing ranges fully
// new range starts at the same start point as one of the existing ranges and 
// ends at the same end point as the other existing range
// should merge all ranges
void addFullOverlapBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(0, 40);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

// tests adding an already existing range to data structure
// should not change existing ranges
void addDuplicateRanges(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(0, 10);

    std::vector<int> ans = {10, 0};
    verifyAnswer(range, ans, __FUNCTION__);      
}

// tests extending an existing range to the left
// should extend existing range
void addExtendLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(-10, 5);
    
    std::vector<int> ans = {10, -10};
    verifyAnswer(range, ans, __FUNCTION__);  
}

// tests extending an existing range to the right
// should extend existing range
void addExtendRight(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(5, 20);
    
    std::vector<int> ans = {20, 0};
    verifyAnswer(range, ans, __FUNCTION__);  
}

/*
    Runs all of the test cases pertaining to the addRange function
*/
void addTests()
{
    addIntoExistingRegion();
    addIntoEmptyRegion();

    addOverExistingRegion();
    addOverExistingRegionLeftBoundary();
    addOverExistingRegionRightBoundary();
    addOverMultipleRegions();
    addDuplicateRanges();
    addExtendLeft();
    addExtendRight();

    addOverLeftMostRegion();
    addPartialOverlapLeft();
    addPartialOverlapRight();
    addPartialOverlapBoth();
    addPartialOverlapBoundaryLeft();
    addPartialOverlapBoundaryRight();
    addFullOverlapBoundary();
}

// tests removing from an empty data structure
// should do nothing
void removeNothing(){
    Range range = Range();
    range.deleteRange(-5, 15);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing part of an existing range
// should remove middle part of range and leave sides in tact
void removeNormal(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(5, 15);
    std::vector<int> ans = {20, 15, 5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);
}


// tests removing part of an existing range
// should remove left side of range and leave right side in tact
void removeLeftBoundary(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(0, 15);
    std::vector<int> ans = {20, 15}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing part of an existing range
// should remove right side of range and leave left side in tact
void removeRightBoundary(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(5, 20);
    std::vector<int> ans = {5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing multiple ranges from data structure
// should render data structure empty
void removeMultipleIntervals(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(-5, 55);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing multiple ranges from data structure
// selection includes start point of leftmost range
// should render data structure empty
void removeMultipleIntervalsLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(0, 55);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}
// tests removing multiple ranges from data structure
// selection includes end point of rightmost range
// should render data structure empty
void removeMultipleIntervalsRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(-5, 50);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing multiple ranges from data structure
// selection includes end point of rightmost range 
// and start point of leftmost ranges
// should render data structure empty
void removeMultipleIntervalsBothBoundaries(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(0, 50);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing multiple times from same range
// should leave holes in range where deletion occured
void removeMultipleFromInterval(){
    Range range = Range();
    range.addRange(0, 40);
    range.deleteRange(5, 15);
    range.deleteRange(25, 35);
    std::vector<int> ans = {40, 35, 25, 15, 5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);    
}

// tests removing multiple times from multiple ranges
// should leave holes where deletion occured
void removeMultipleTimesMultipleIntervals(){
    Range range = Range();
    range.addRange(0, 20);
    range.addRange(40, 60);
    range.addRange(80, 100);
    range.deleteRange(10, 45);
    range.deleteRange(55, 90);
    std::vector<int> ans = {100, 90, 55, 45, 10, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);     
}

// tests removing leftmost existing range
// should remove leftmost existing range
void removeLeftMostRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(-5, 15);
    std::vector<int> ans = {50, 40, 30, 20};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing rightmost existing range
// should remove righrmost existing range
void removeRightMostRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(35, 55);
    std::vector<int> ans = {30, 20, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

// tests removing leftmost existing range
// should remove leftmost existing range
void removeMiddleRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(15, 35);
    std::vector<int> ans = {50, 40, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}


void removeTests()
{
    removeNothing();
    removeNormal();
    removeLeftBoundary();
    removeRightBoundary();
    removeMultipleFromInterval();

    removeMultipleIntervals();
    removeMultipleIntervalsLeftBoundary();
    removeMultipleIntervalsRightBoundary();
    removeMultipleIntervalsBothBoundaries();
    removeMultipleTimesMultipleIntervals();

    removeLeftMostRegion();
    removeRightMostRegion();
    removeMiddleRegion();
}

// tests getting an empty range
// should return nothing
void getEmptyInterval(){
    Range range = Range();
    auto res = range.getRange(-10, 10);
    std::vector<std::pair<int, int>> ans = {}; 
    verifyAnswer(res, ans, __FUNCTION__);    
}

// tests getting a range with overlap on both sides
// should return the entire range in the data structure
void getIntervalOvelappingBothSides(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(-5, 15);
    std::vector<std::pair<int, int>> ans = {{0, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting a range that is contained inside of existing range
// should return part of the range
void getPartialInterval(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(2, 8);
    std::vector<std::pair<int, int>> ans = {{2, 8}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting a range that is contained inside of existing range
// selection includes start point of range
// should return part of the range
void getPartialIntervalLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(0, 8);
    std::vector<std::pair<int, int>> ans = {{0, 8}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting a range that is contained inside of existing range
// selection includes endpoint of range
// should return part of the range
void getPartialIntervalRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(2, 10);
    std::vector<std::pair<int, int>> ans = {{2, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting multiple disjoint ranges with selection overlapping ranges
// should return list of all ranges in data structure
void getMultipleIntervalsOver(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(-10, 40);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting multiple disjoint ranges with exact selection
// should return list of all ranges in data structure
void getMultipleIntervalsBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(0, 30);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting an entire range and part of another
// should return one whole range and one partial range
void getMultipleIntervalsLeftPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(5, 30);
    std::vector<std::pair<int, int>> ans = {{5, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// also tests getting an entire range and part of another
// should return one whole range and one partial range
void getMultipleIntervalsRightPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(0, 25);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 25}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

// tests getting an parts of two ranges
// should return two partial ranges
void getMultipleIntervalsBothPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(5, 45);
    std::vector<std::pair<int, int>> ans = {{5, 10}, {20, 30}, {40, 45}}; 
    verifyAnswer(res, ans, __FUNCTION__);    
}

// tests getting the leftmost range in the data structure
// should return the leftmost range in the data structure
void getLeftMostInterval(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(-5, 15);
    std::vector<std::pair<int, int>> ans = {{0, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);        
}

// tests getting the rightmost range in the data structure
// should return the rightmost range in the data structure
void getRightMostInterval(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(35, 55);
    std::vector<std::pair<int, int>> ans = {{40, 50}}; 
    verifyAnswer(res, ans, __FUNCTION__);        
}

// tests getting the middle range in the data structure
// should return the middle range in the data structure
void getMiddleInterval(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(20, 30);
    std::vector<std::pair<int, int>> ans = {{20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);        
}

void getTests()
{
    getEmptyInterval();
    getPartialInterval();
    getPartialIntervalLeftBoundary();
    getPartialIntervalRightBoundary();
    getIntervalOvelappingBothSides();

    getMultipleIntervalsLeftPartial();
    getMultipleIntervalsRightPartial();
    getMultipleIntervalsOver();
    getMultipleIntervalsBoundary();
    getMultipleIntervalsBothPartial();

    getLeftMostInterval();
    getMiddleInterval();
    getRightMostInterval();
}

void runTests()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Testing Add Functionality:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    addTests();
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Testing Remove Functionality:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    removeTests();
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Testing Get Functionality:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    getTests();
}