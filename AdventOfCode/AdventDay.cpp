#include "AdventDay.h"

AdventDay::AdventDay(unsigned int day, std::unique_ptr<AdventDayPart> part1, std::unique_ptr<AdventDayPart> part2)
{
    this->day = day;
    this->partA = std::move(part1);
    this->partB = std::move(part2);

    Execute();
}

void AdventDay::Execute()
{
    std::cout << "Executing Day " << day << ", Part A..." << std::endl;
    this->partA->Execute();
    std::cout << "Executing Day " << day << ", Part B..." << std::endl;
    this->partB->Execute();
}
