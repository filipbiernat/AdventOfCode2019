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

class Day3B :
    public AdventDayPart
{
public:
    Day3B();
    virtual ~Day3B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    
    virtual void SaveOutput();

private:
    std::vector<std::pair <int, int> > FillWire(std::vector<std::string> wireInput);
    void FillNextSection(std::vector<std::pair <int, int> >& coordinates, std::string& instruction);
    std::pair <int, int> GetNextStep(std::pair <int, int>& previous, std::string direction);
    std::vector<std::pair<int, int>> GetWireIntersections(std::vector<std::pair<int, int>> wire1, std::vector<std::pair<int, int>> wire2);

    std::vector<std::vector<std::string> > input;
    int output;

    struct compare
    {
        std::pair <int, int> key;
        compare(std::pair <int, int> const &i) : key(i) { }

        bool operator()(std::pair <int, int> const &i)
        {
            return (i == key);
        }
    };
};

