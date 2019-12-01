#include <iostream>
#include <memory>
#include "AdventDay.h"

int main()
{
    AdventDay(0, std::make_unique<AdventDayPart>(), std::make_unique<AdventDayPart>());

    std::cout << "Execution completed." << std::endl;
}