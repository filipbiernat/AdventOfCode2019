#pragma once
#include <memory>
#include <iostream>
#include "AdventDayPart.h"

class AdventDay
{
public:
    AdventDay(unsigned int day, std::unique_ptr<AdventDayPart> part1, std::unique_ptr<AdventDayPart> part2);
    virtual ~AdventDay() {}

private:
    void Execute();

    unsigned int day;
    std::unique_ptr<AdventDayPart> partA;
    std::unique_ptr<AdventDayPart> partB;
};

