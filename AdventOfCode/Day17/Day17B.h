#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>

class Day17B :
    public AdventDayPart
{
public:
    Day17B();
    virtual ~Day17B();

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
    std::vector<std::vector<char> > viewFromCameras;
    std::queue<long long> programInput;
};

