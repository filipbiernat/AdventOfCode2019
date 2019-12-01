#include <iostream>
#include <memory>
#include "AdventDay.h"
#include "Day0\Day0.h"
#include "Day1\Day1A.h"
#include "Day1\Day1B.h"

int main()
{
    AdventDay(1, std::make_unique<Day1A>(), std::make_unique<Day1B>());

    std::cout << "Execution completed." << std::endl;
    return 0;
}