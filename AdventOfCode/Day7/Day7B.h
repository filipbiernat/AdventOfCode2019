#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>

class Day7B :
    public AdventDayPart
{
public:
    Day7B();
    virtual ~Day7B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::pair<int, int> RunProgram(std::vector<int>& programCode, size_t instructionPointer, std::queue<int>& programInput);

    std::vector<int> programCode;
    int output;
};

