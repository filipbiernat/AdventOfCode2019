#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>

class Day8B :
    public AdventDayPart
{
public:
    Day8B();
    virtual ~Day8B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<std::string > input;
    std::string resultString;
};

