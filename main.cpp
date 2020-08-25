#include "Range.h"


int main(){
    Range * range = new Range();
    range->addRange(0, 10);
    range->addRange(20, 30);
    range->addRange(40, 50);
    range->addRange(15, 35);
    // range->getUpper(0);
    range->printAll();
}

