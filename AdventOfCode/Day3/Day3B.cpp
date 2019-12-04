#include "Day3B.h"

Day3B::Day3B()
{
}

Day3B::~Day3B()
{
}

void Day3B::ReadInput()
{
    const bool testMode = false;
    const std::string fileName = testMode ? "Day3/Day3a_test.txt" : "Day3/Day3a.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        std::vector<std::string> inputWire;
        std::stringstream ss(inputString);
        while (std::getline(ss, inputString, ','))
        {
            if (inputString.size() > 0)
            {
                inputWire.push_back(inputString);
            }
        }
        input.push_back(inputWire);
    }
    inputStream.close();
}

void Day3B::ProcessData()
{
    auto wire1 = FillWire(input.at(0));
    auto wire2 = FillWire(input.at(1));

    std::vector<std::pair<int, int>> wireIntersections = GetWireIntersections(wire1, wire2);

    std::vector<int> distance;
    for (auto& elem : wireIntersections)
    {
        //The number of steps a wire takes is the total number of grid squares 
        //the wire has entered to get to that location
        auto itr1 = std::find_if(wire1.cbegin(), wire1.cend(), compare(elem));
        auto itr2 = std::find_if(wire2.cbegin(), wire2.cend(), compare(elem));
        distance.push_back(std::distance(wire1.cbegin(), itr1) + std::distance(wire2.cbegin(), itr2));
    }

    //choose the intersection where the sum of both wires' steps is lowest
    std::nth_element(distance.begin(), distance.begin() + 1, distance.end(), std::less<int>());
    output = distance[1];
}

void Day3B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

std::vector<std::pair<int, int>> Day3B::FillWire(std::vector<std::string> wireInput)
{
    std::vector<std::pair<int, int>> wire;
    wire.push_back(std::make_pair(0, 0));

    for (auto& instruction : wireInput)
    {
        FillNextSection(wire, instruction);
    }

    return wire;
}

void Day3B::FillNextSection(std::vector<std::pair <int, int> >& coordinates, std::string& instruction)
{
    auto direction = instruction.substr(0, 1);
    auto distance = stoi(instruction.substr(1));
    for (int i = 0; i < distance; ++i)
    {
        coordinates.push_back(GetNextStep(coordinates.back(), direction));
    }
};

std::pair<int, int> Day3B::GetNextStep(std::pair<int, int>& previousStep, std::string direction)
{
    auto nextStep(previousStep);

    if (direction == "L")
    {
        --std::get<0>(nextStep);
    }
    else if (direction == "R")
    {
        ++std::get<0>(nextStep);
    }
    else if (direction == "U")
    {
        ++std::get<1>(nextStep);
    }
    else if (direction == "D")
    {
        --std::get<1>(nextStep);
    }

    return nextStep;
}

std::vector<std::pair<int, int>> Day3B::GetWireIntersections(std::vector<std::pair<int, int>> wire1, std::vector<std::pair<int, int>> wire2)
{
    std::vector<std::pair<int, int>> wireIntersections;
    std::sort(wire1.begin(), wire1.end());
    std::sort(wire2.begin(), wire2.end());

    std::set_intersection(wire1.begin(),
        wire1.end(),
        wire2.begin(),
        wire2.end(),
        std::back_inserter(wireIntersections));
    return wireIntersections;
}