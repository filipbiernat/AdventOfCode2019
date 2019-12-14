#include "Day10B.h"

Day10B::Day10B()
{
}

Day10B::~Day10B()
{
}

void Day10B::ReadInput()
{
    const std::string fileName = "Day10/Day10A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    for (int y = 0; std::getline(inputStream, inputString); ++y)
    {
        for (int x = 0; x < static_cast<int>(inputString.size()); ++x)
        {
            //The map indicates whether each position is empty (.) or contains an asteroid (#). 
            if ('#' == inputString[x])
            {
                //The asteroids can be described with X,Y coordinates where X is the distance from the
                //left edge and Y is the distance from the top edge (so the top-left corner is 0,0 and 
                //the position immediately to its right is 1,0).
                input.push_back(std::make_pair(x, y));
            }
        }
    }
    inputStream.close();
}

void Day10B::ProcessData()
{
    auto partA = std::make_unique<Day10A>();
    std::pair<int, int> currentAsteroidCoords = partA->GetStationCoords();

    //How many other asteroids can be detected from that location?
    std::vector<std::pair<int, int> > otherAsteroids;
    std::copy_if(
        input.begin(),
        input.end(),
        std::back_inserter(otherAsteroids),
        [currentAsteroidCoords](std::pair<int, int> coords) -> bool
    {
        return !(currentAsteroidCoords.first == coords.first && currentAsteroidCoords.second == coords.second);
    });

    std::multimap<double, std::pair<int, int> > otherAsteroidsMap;
    std::transform(
        otherAsteroids.begin(),
        otherAsteroids.end(), 
        std::inserter(otherAsteroidsMap, otherAsteroidsMap.end()),
        [currentAsteroidCoords](std::pair<int, int> coords) -> std::pair<double, std::pair<int, int> >
    {
        //The laser starts by pointing up and always rotates clockwise, vaporizing any asteroid it hits.
        double angle = -atan2(currentAsteroidCoords.first - coords.first, currentAsteroidCoords.second - coords.second);
        return std::make_pair(angle >= 0 ? angle : angle + 2 * 3.14159265359, coords);
    });

    //If multiple asteroids are exactly in line with the station, the laser only has enough power to 
    //vaporize one of them before continuing its rotation. In other words, the same asteroids that can 
    //be detected can be vaporized, but if vaporizing one asteroid makes another one detectable, the 
    //newly-detected asteroid won't be vaporized until the laser has returned to the same position by 
    //rotating a full 360 degrees.
    auto it = otherAsteroidsMap.begin();
    //The Elves are placing bets on which will be the 200th asteroid to be vaporized.
    for (int i = 1; i < 200; it = otherAsteroidsMap.upper_bound(it->first), ++i)
    {
        otherAsteroidsMap.erase(it);
    }
    //What do you get if you multiply its X coordinate by 100 and then add its Y coordinate?
    output = 100 * it->second.first + it->second.second;
}

void Day10B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}
