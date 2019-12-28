#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Day17A :
    public AdventDayPart
{
public:
    Day17A();
    virtual ~Day17A();

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
};

