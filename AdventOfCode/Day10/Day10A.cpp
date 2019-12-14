#include "Day10A.h"

Day10A::Day10A()
{
}

Day10A::~Day10A()
{
}

void Day10A::ReadInput()
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

void Day10A::ProcessData()
{
    std::vector<int> detectedAsteroids;
    std::transform(
        input.begin(),
        input.end(),
        std::back_inserter(detectedAsteroids),
        [&](std::pair<int, int> currentAsteroidCoords) -> int
    {
        //How many other asteroids can be detected from that location?
        std::vector<std::pair<int, int> > otherAsteroids;
        std::copy_if(
            input.begin(), 
            input.end(), 
            std::back_inserter(otherAsteroids),
            [currentAsteroidCoords](std::pair<int, int> coords) -> bool
        {
            return !(std::get<0>(currentAsteroidCoords) == std::get<0>(coords) && std::get<1>(currentAsteroidCoords) == std::get<1>(coords));
        });

        //A monitoring station can detect any asteroid to which it has direct line of sight - that is,
        //there cannot be another asteroid exactly between them. This line of sight can be at any 
        //angle, not just lines aligned to the grid or diagonally.
        std::vector<double> angle;
        std::transform(
            otherAsteroids.begin(),
            otherAsteroids.end(),
            std::back_inserter(angle),
            [currentAsteroidCoords](std::pair<int, int> coords) -> double
        {
            return atan2(
                std::get<0>(currentAsteroidCoords) - std::get<0>(coords),
                std::get<1>(currentAsteroidCoords) - std::get<1>(coords));
        });

        std::sort(angle.begin(), angle.end());
        return std::unique(angle.begin(), angle.end()) - angle.begin();
    });

    //The best location is the asteroid that can detect the largest number of other asteroids.
    output = *max_element(detectedAsteroids.begin(), detectedAsteroids.end());
}

void Day10A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}
