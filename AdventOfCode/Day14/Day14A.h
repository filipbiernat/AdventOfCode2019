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

class Day14A :
    public AdventDayPart
{
public:
    Day14A();
    virtual ~Day14A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int Produce(std::string what, int quantity = 1);
    int CeilDiv(int x, int y);

    std::map<std::string, std::pair<int, std::map<std::string, int> > > input;
    std::map<std::string, int> producedResources;
    int output;
};

