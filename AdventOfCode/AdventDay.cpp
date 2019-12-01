#include "AdventDay.h"

AdventDay::AdventDay(unsigned int day, std::unique_ptr<AdventDayPart> part1, std::unique_ptr<AdventDayPart> part2)
{
    this->day = day;
    this->part1 = std::move(part1);
    this->part2 = std::move(part2);

    Execute();
}

void AdventDay::Execute()
{
    std::cout << "Executing Day " << day << "..." << std::endl;

    this->part1->Execute();
    this->part2->Execute();
}
