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
#include <map>
#include <iterator>
#include "Day10A.h"

class Day10B :
    public AdventDayPart
{
public:
    Day10B();
    virtual ~Day10B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<std::pair<int, int> > input;
    int output;
};
