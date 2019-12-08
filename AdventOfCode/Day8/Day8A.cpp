#include "Day8A.h"

Day8A::Day8A()
{
}

Day8A::~Day8A()
{
}

void Day8A::ReadInput()
{
    const std::string fileName = "Day8/Day8A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString((std::istreambuf_iterator<char>(inputStream)),
        std::istreambuf_iterator<char>());

    //The image you received is 25 pixels wide and 6 pixels tall.
    for (unsigned i = 0; i < inputString.length(); i += 25 * 6)
    {
        std::string singleString = inputString.substr(i, 25 * 6);
        if (singleString.length() == 25 * 6)
        {
            input.push_back(singleString);
        }
    }
    inputStream.close();
}

void Day8A::ProcessData()
{
    std::vector<std::pair<int, int> > digitsCnt;

    //the Elves would like you to find the layer that contains the fewest 0 digits. 
    //On that layer, what is the number of 1 digits multiplied by the number of 2 digits?
    std::transform(input.begin(), 
        input.end(), 
        back_inserter(digitsCnt), 
        [](std::string str) -> std::pair<int, int>
    {
        return std::make_pair(
            std::count(str.begin(), str.end(), '0'),
            std::count(str.begin(), str.end(), '1') * std::count(str.begin(), str.end(), '2'));
    });

    output = std::get<1>(*std::min_element(digitsCnt.begin(), 
        digitsCnt.end(), 
        [](const auto& lhs, const auto& rhs)
    { 
        return std::get<0>(lhs) < std::get<0>(rhs); 
    }));
}

void Day8A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

