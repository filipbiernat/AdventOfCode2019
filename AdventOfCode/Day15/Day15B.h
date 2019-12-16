#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

class Day15B :
    public AdventDayPart
{
public:
    Day15B();
    virtual ~Day15B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    long long RunProgram(std::vector<long long>& programCode);
    int SearchForOxygenSystem(std::vector<long long>& programCode, int x = 0, int y = 0, int distance = 1);
    int FillWithOxygen(std::vector<long long>& programCode, int x, int y, int distance = 0);

    std::vector<long long> programCode;
    std::set<std::pair<int, int>> visitedPoints;
    int input;
    int output;

    int oxygenSystemX;
    int oxygenSystemY;
    std::vector<long long> oxygenSystemProgramCode;
};

