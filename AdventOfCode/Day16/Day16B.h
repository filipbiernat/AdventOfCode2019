#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <sstream>

class Day16B :
    public AdventDayPart
{
public:
    Day16B();
    virtual ~Day16B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<int> input;
    int output;
};

