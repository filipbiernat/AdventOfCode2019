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

class Day12A :
    public AdventDayPart
{
public:
    Day12A();
    virtual ~Day12A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<std::pair<std::vector<int>, std::vector<int> > > input;
    unsigned int output;
};

