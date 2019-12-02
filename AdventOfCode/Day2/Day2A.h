#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>

class Day2A :
    public AdventDayPart
{
public:
    Day2A();
    virtual ~Day2A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    void PrintVector();

    std::vector<int> input;
};

