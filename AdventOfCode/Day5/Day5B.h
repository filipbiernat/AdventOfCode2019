#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day5B :
    public AdventDayPart
{
public:
    Day5B();
    virtual ~Day5B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int RunProgram(std::vector<int>& programCode);

    std::vector<int> programCode;
    int input;
    int output;
};

