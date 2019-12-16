#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

class Day15A :
    public AdventDayPart
{
public:
    Day15A();
    virtual ~Day15A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);
    int DiscoverNeighbourhood(std::vector<long long>& programCode, int x = 0, int y = 0, int distance = 1);

    std::vector<long long> programCode;
    std::set<std::pair<int, int>> visitedPoints;
    int input;
    int output;
};

