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

class Day6A :
    public AdventDayPart
{
public:
    Day6A();
    virtual ~Day6A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int CountOrbits(std::string node, int level);
    std::map<std::string, std::set<std::string>> input;
    int output;
};

