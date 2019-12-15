#include "Day12A.h"

Day12A::Day12A()
{
}

Day12A::~Day12A()
{
}

void Day12A::ReadInput()
{
    const std::string fileName = "Day12/Day12A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        std::pair<std::vector<int>, std::vector<int> > inputLine;
        std::regex word_regex("<x=(.*), y=(.*), z=(.*)>");
        std::smatch matches;
        if (std::regex_search(inputString, matches, word_regex))
        {
            for (size_t i = 1; i < matches.size(); ++i) 
            {
                //Each moon has a 3-dimensional position (x, y, and z) and a 3-dimensional velocity. 
                //The position of each moon is given in your scan; the x, y, and z velocity of each 
                //moon starts at 0.
                inputLine.first.push_back(std::stoi(matches[i].str()));
                inputLine.second.push_back(0);
            }
        }
        input.push_back(inputLine);
    }
    inputStream.close();
}

void Day12A::ProcessData()
{
    //Simulate the motion of the moons in time steps. 
    const int steps = 1000;
    for (int step = 0; step < steps; ++step)
    {
        //Within each time step, first update the velocity of every moon by applying gravity. 
        for (auto& moon1 : input)
        {
            for (auto& moon2 : input)
            {
                if (moon1 != moon2)
                {
                    for (int dir = 0; dir < 3; ++dir)
                    {
                        //To apply gravity, consider every pair of moons. On each axis (x, y, and z), 
                        //the velocity of each moon changes by exactly +1 or -1 to pull the moons together. 
                        moon1.second[dir] += (moon1.first[dir] < moon2.first[dir]) - (moon1.first[dir] > moon2.first[dir]);
                    }
                }
            }
        }

        //Once all gravity has been applied, apply velocity: simply add the velocity of each moon to its own position.
        for (auto& moon : input)
        {
            for (int dir = 0; dir < 3; ++dir)
            {
                moon.first[dir] += moon.second[dir];
            }
        }
    }

    //Then, it might help to calculate the total energy in the system.
    output = 0;
    for (auto& moon : input)
    {
        int potentialEnergy = 0;
        int kineticEnergy = 0;
        for (int dir = 0; dir < 3; ++dir)
        {
            //A moon's potential energy is the sum of the absolute values of its x, y, and z position 
            //coordinates. A moon's kinetic energy is the sum of the absolute values of its velocity coordinates.
            potentialEnergy += abs(moon.first[dir]);
            kineticEnergy   += abs(moon.second[dir]);
        }
        //The total energy for a single moon is its potential energy multiplied by its kinetic energy.
        output += potentialEnergy * kineticEnergy;
    }
}

void Day12A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}
