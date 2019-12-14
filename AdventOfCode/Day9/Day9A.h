#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day9A :
    public AdventDayPart
{
public:
    Day9A();
    virtual ~Day9A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);

    std::vector<long long> programCode;
    int input;
    std::vector<long long> output;
};

