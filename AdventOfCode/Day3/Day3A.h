#pragma once
#include "../AdventDayPart.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstdlib> 

class Day3A :
    public AdventDayPart
{
public:
    Day3A();
    virtual ~Day3A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    std::vector<std::pair <int, int> > FillWire(std::vector<std::string> wireInput);
    void FillNextSection(std::vector<std::pair <int, int> >& coordinates, std::string& instruction);
    std::pair <int, int> GetNextStep(std::pair <int, int>& previous, std::string direction);

    std::vector<std::vector<std::string> > input;
    unsigned int output;
};

