#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

class Day1B :
    public AdventDayPart
{
public:
    Day1B();
    virtual ~Day1B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    void PrintVector();

    std::vector<int> input;
    unsigned int output;
};

