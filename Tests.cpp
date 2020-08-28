#include "Tests.h"
#include "Range.h"
#include <assert.h>
#include <iostream>

// macro used to declutter output with success messages
// only prints out failed testcases if enabled
#define ONLY_PRINT_FAILURES 1

inline bool verifyAnswer(const Range& range, const std::vector<int>& ans, const char* funcname){
    bool success = (range.toVec() == ans);
#if ONLY_PRINT_FAILURES 
    if (success){
        return true;
    }
#endif
    std::cout << "Test for #" << funcname << " : ";
    if (success){
        std::cout << "SUCCESS" << std::endl;
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
    return success;
}

inline bool verifyAnswer(const std::vector<std::pair<int, int>>& actual, 
    const std::vector<std::pair<int, int>>& expected, const char* funcname){
    bool success = (actual == expected);
#if ONLY_PRINT_FAILURES 
    if (success){
        return true;
    }
#endif
    std::cout << "Test for #" << funcname << " : ";
    if (success){
        std::cout << "SUCCESS" << std::endl;
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
    return success;
}

void addIntoExistingRegion()
{
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(2, 8);
    std::vector<int> ans = {10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addIntoEmptyRegion()
{
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(11, 20);
    std::vector<int> ans = {20, 11, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

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

void addOverExistingRegionLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(20, 35);
    std::vector<int> ans = {50, 40, 35, 20, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addOverExistingRegionRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.addRange(15, 30);
    std::vector<int> ans = {50, 40, 30, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

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

void addPartialOverlapLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(5, 35);
    std::vector<int> ans = {35, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addPartialOverlapRight(){
    Range range = Range();
    range.addRange(30, 40);
    range.addRange(5, 35);
    std::vector<int> ans = {40, 5};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addPartialOverlapBoth(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(5, 35);
    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addOverLeftMostRegion(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(-5, 15);
    std::vector<int> ans = {15, -5};
    verifyAnswer(range, ans, __FUNCTION__);
}

void addPartialOverlapBoundaryLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(0, 35);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

void addPartialOverlapBoundaryRight(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(5, 40);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

void addFullOverlapBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(30, 40);
    range.addRange(0, 40);

    std::vector<int> ans = {40, 0};
    verifyAnswer(range, ans, __FUNCTION__);    
}

void addConnectTwoRegions(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);

    range.addRange(15, 20);

    std::vector<int> ans = {30, 15, 10, 0};
    verifyAnswer(range, ans, __FUNCTION__);  
}

void addConnectThreeRegions(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(10, 20);

    std::vector<int> ans = {30, 0};
    verifyAnswer(range, ans, __FUNCTION__);  
}

void addDuplicateRanges(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(0, 10);

    std::vector<int> ans = {10, 0};
    verifyAnswer(range, ans, __FUNCTION__);      
}

void addExtendLeft(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(-10, 5);
    
    std::vector<int> ans = {10, -10};
    verifyAnswer(range, ans, __FUNCTION__);  
}


void addExtendRight(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(5, 20);
    
    std::vector<int> ans = {20, 0};
    verifyAnswer(range, ans, __FUNCTION__);  
}

void addTests()
{
    // easier tests
    addIntoExistingRegion();
    addIntoEmptyRegion();
    addOverExistingRegion();
    addOverExistingRegionLeftBoundary();
    addOverExistingRegionRightBoundary();
    addOverMultipleRegions();
    addDuplicateRanges();
    addExtendLeft();
    addExtendRight();

    // harder tests
    addOverLeftMostRegion();
    addPartialOverlapLeft();
    addPartialOverlapRight();
    addPartialOverlapBoth();
    addPartialOverlapBoundaryLeft();
    addPartialOverlapBoundaryRight();
    addFullOverlapBoundary();
    addConnectTwoRegions();
    addConnectThreeRegions();
}

void removeNothing(){
    Range range = Range();
    range.deleteRange(-5, 15);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeNormal(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(5, 15);
    std::vector<int> ans = {20, 15, 5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeLeftBoundary(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(0, 15);
    std::vector<int> ans = {20, 15}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeRightBoundary(){
    Range range = Range();
    range.addRange(0, 20);
    range.deleteRange(5, 20);
    std::vector<int> ans = {5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeMultipleIntervals(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(-5, 55);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeMultipleIntervalsLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(0, 55);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeMultipleIntervalsRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(-5, 50);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeMultipleIntervalsBothBoundaries(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    range.deleteRange(0, 50);
    std::vector<int> ans = {}; 
    verifyAnswer(range, ans, __FUNCTION__);
}

void removeMultipleFromInterval(){
    Range range = Range();
    range.addRange(0, 40);
    range.deleteRange(5, 15);
    range.deleteRange(25, 35);
    std::vector<int> ans = {40, 35, 25, 15, 5, 0}; 
    verifyAnswer(range, ans, __FUNCTION__);    
}

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
}

void getEmptyInterval(){
    Range range = Range();
    auto res = range.getRange(-10, 10);
    std::vector<std::pair<int, int>> ans = {}; 
    verifyAnswer(res, ans, __FUNCTION__);    
}

void getIntervalOvelappingBothSides(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(-5, 15);
    std::vector<std::pair<int, int>> ans = {{0, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getPartialInterval(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(2, 8);
    std::vector<std::pair<int, int>> ans = {{2, 8}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getPartialIntervalLeftBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(0, 8);
    std::vector<std::pair<int, int>> ans = {{0, 8}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getPartialIntervalRightBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    auto res = range.getRange(2, 10);
    std::vector<std::pair<int, int>> ans = {{2, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervals(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(0, 30);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervalsOver(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(-10, 40);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervalsBoundary(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(0, 30);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervalsLeftPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(5, 30);
    std::vector<std::pair<int, int>> ans = {{5, 10}, {20, 30}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervalsRightPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    auto res = range.getRange(0, 25);
    std::vector<std::pair<int, int>> ans = {{0, 10}, {20, 25}}; 
    verifyAnswer(res, ans, __FUNCTION__);
}

void getMultipleIntervalsBothPartial(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(5, 45);
    std::vector<std::pair<int, int>> ans = {{5, 10}, {20, 30}, {40, 45}}; 
    verifyAnswer(res, ans, __FUNCTION__);    
}

void getLeftMostInterval(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(-5, 15);
    std::vector<std::pair<int, int>> ans = {{0, 10}}; 
    verifyAnswer(res, ans, __FUNCTION__);        
}

void getRightMostInterval(){
    Range range = Range();
    range.addRange(0, 10);
    range.addRange(20, 30);
    range.addRange(40, 50);
    auto res = range.getRange(35, 55);
    std::vector<std::pair<int, int>> ans = {{40, 50}}; 
    verifyAnswer(res, ans, __FUNCTION__);        
}

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

    getMultipleIntervals();
    getMultipleIntervalsLeftPartial();
    getMultipleIntervalsRightPartial();
    getMultipleIntervalsOver();
    getMultipleIntervalsBoundary();
    getMultipleIntervalsBothPartial();
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