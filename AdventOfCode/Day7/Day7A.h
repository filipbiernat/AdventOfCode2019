#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>

class Day7A :
    public AdventDayPart
{
public:
    Day7A();
    virtual ~Day7A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int RunProgram(std::vector<int>& programCode);
    void clearQueue(std::queue<std::reference_wrapper<int> > &q);
    int AccessInput();

    std::vector<int> programCode;
    std::queue<std::reference_wrapper<int> > programInput;
    int output;
};

