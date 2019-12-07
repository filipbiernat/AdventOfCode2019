#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day5A :
    public AdventDayPart
{
public:
    Day5A();
    virtual ~Day5A();

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

