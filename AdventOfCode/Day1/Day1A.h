#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

class Day1A :
    public AdventDayPart
{
public:
    Day1A();
    virtual ~Day1A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<unsigned int> input;
    unsigned int output;
};

