#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day2B :
    public AdventDayPart
{
public:
    Day2B();
    virtual ~Day2B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int RunProgram(std::vector<int>& programCode);

    std::vector<int> input;
    int output;
};

