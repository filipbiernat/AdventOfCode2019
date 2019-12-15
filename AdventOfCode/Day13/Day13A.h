#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day13A :
    public AdventDayPart
{
public:
    Day13A();
    virtual ~Day13A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);

    std::vector<long long> programCode;
    int input;
    int output;
    std::vector<long long> programOutput;
};

