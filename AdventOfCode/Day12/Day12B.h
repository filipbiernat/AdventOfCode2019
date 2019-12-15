#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <regex>

class Day12B :
    public AdventDayPart
{
public:
    Day12B();
    virtual ~Day12B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int SimulateOneDirection(int dir);
    std::vector<std::pair<std::vector<int>, std::vector<int> > > input;
    unsigned long long output;
};

