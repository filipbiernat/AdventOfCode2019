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
#include <regex>

class Day14B :
    public AdventDayPart
{
public:
    Day14B();
    virtual ~Day14B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long Produce(std::string what, long long quantity = 1);
    long long CeilDiv(long long x, long long y);

    std::map<std::string, std::pair<long long, std::map<std::string, long long> > > input;
    std::map<std::string, long long> producedResources;
    long long output;
};

