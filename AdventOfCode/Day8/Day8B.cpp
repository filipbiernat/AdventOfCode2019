#include "Day8B.h"

Day8B::Day8B()
{
}

Day8B::~Day8B()
{
}

void Day8B::ReadInput()
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

void Day8B::ProcessData()
{
    resultString = *input.begin();
    //The image is rendered by stacking the layers and aligning the pixels with the same positions in each layer.
    for (std::string currentString : input)
    {
        std::transform(
            resultString.begin(),
            resultString.end(),
            currentString.begin(),
            resultString.begin(),
            [](char result, char current) -> char
        {
            //Transparent -> get from the next layer.
            return '2' == result ? current : result;
        });
    }

    //The digits indicate the color of the corresponding pixel: 0 is black, 1 is white, and 2 is transparent.
    char r;
    std::map<char, char> encoding = { {'0', ' '}, {'1', '#'} };
    std::replace_if(
        resultString.begin(),
        resultString.end(),
        [&](char ch) { return r = encoding[ch]; }, r);
}

void Day8B::SaveOutput()
{
    //What message is produced after decoding your image?
    for (unsigned i = 0; i < resultString.length(); i += 25)
    {
        std::cout << resultString.substr(i, 25) << std::endl;
    }
}

