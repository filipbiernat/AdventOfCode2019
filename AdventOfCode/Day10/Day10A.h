#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstdlib> 
#include <cmath>

class Day10A :
    public AdventDayPart
{
public:
    Day10A();
    virtual ~Day10A();

    std::pair<int, int> GetStationCoords();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<std::pair<int, int> > input;
    int output;
    std::pair<int, int> outputCoords;
};

