#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <tuple>

class Day6B :
    public AdventDayPart
{
public:
    Day6B();
    virtual ~Day6B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::tuple<int, bool, bool> CountOrbits(std::string node, int level);
    std::map<std::string, std::set<std::string>> input;
    int output;
};

