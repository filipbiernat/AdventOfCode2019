#include "Day12B.h"

Day12B::Day12B()
{
}

Day12B::~Day12B()
{
}

void Day12B::ReadInput()
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

void Day12B::ProcessData()
{
    //Of course, the universe might last for a very long time before repeating.
    //Clearly, you might need to find a more efficient way to simulate the universe.
    long long x = SimulateOneDirection(0);
    long long y = SimulateOneDirection(1);
    long long z = SimulateOneDirection(2);
    output = std::lcm(std::lcm(x, y), z);
}

void Day12B::SaveOutput()
{
    //How many steps does it take to reach the first state that exactly matches a previous state?
    std::cout << "Result: " << output << std::endl;
}

int Day12B::SimulateOneDirection(int dir)
{
    std::vector<std::pair<std::vector<int>, std::vector<int> > > originalInput = input;

    //Determine the number of steps that must occur before all of the moons' positions and velocities 
    //exactly match a previous point in time.
    int step = 1;
    for (;; ++step)
    {
        //Within each time step, first update the velocity of every moon by applying gravity. 
        for (auto& moon1 : input)
        {
            for (auto& moon2 : input)
            {
                if (moon1 != moon2)
                {
                    //To apply gravity, consider every pair of moons. On each axis (x, y, and z), 
                    //the velocity of each moon changes by exactly +1 or -1 to pull the moons together. 
                    moon1.second[dir] += (moon1.first[dir] < moon2.first[dir]) - (moon1.first[dir] > moon2.first[dir]);
                }
            }
        }

        //Once all gravity has been applied, apply velocity: simply add the velocity of each moon to its own position.
        for (auto& moon : input)
        {
            moon.first[dir] += moon.second[dir];
        }

        int matches = 0;
        for (auto originalMoon = originalInput.begin(), moon = input.begin();
            originalMoon != originalInput.end() && moon != input.end();
            ++originalMoon, ++moon
            )
        {
            if (originalMoon->first[dir] == moon->first[dir] && originalMoon->second[dir] == moon->second[dir])
            {
                ++matches;
            }
        }
        if (matches == input.size())
        {
            return step;
        }
    }
    return -1;
}
