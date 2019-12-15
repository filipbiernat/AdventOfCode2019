#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day13B :
    public AdventDayPart
{
public:
    Day13B();
    virtual ~Day13B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);
    void ProcessOutput();

    std::vector<long long> programCode;
    int input;
    int output;
    std::vector<long long> programOutput;
    long long ballX;
    long long paddleX;
};

