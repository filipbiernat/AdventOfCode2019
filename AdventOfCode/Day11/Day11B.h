#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day11B :
    public AdventDayPart
{
public:
    Day11B();
    virtual ~Day11B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);
    void ProcessOutput();
    void TurnLeft();
    void TurnRight();

    std::vector<long long> programCode;
    int input;
    int output;
    std::vector<long long> intcodeOutput;

    std::vector<std::vector<int> > map;
    std::vector<std::vector<int> > paintingCnt;
    int x;
    int y;
    char direction;
};

