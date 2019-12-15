#include "Day14B.h"

Day14B::Day14B()
{
}

Day14B::~Day14B()
{
}

void Day14B::ReadInput()
{
    const std::string fileName = "Day14/Day14A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    //You ask the nanofactory to produce a list of the reactions it can perform that are 
    //relevant to this process (your puzzle input). Every reaction turns some quantities 
    //of specific input chemicals into some quantity of an output chemical.
    std::string inputString;
    while (std::getline(inputStream, inputString))
    {
        std::pair<std::vector<long long>, std::vector<long long> > inputLine;
        std::regex word_regex("(\\d+) ([A-Z]+)");
        std::smatch matches;

        std::map<std::string, long long> newSubstances;
        std::pair<std::string, long long> newSubstance;
        for (
            auto it = inputString.cbegin();
            std::regex_search(it, inputString.cend(), matches, word_regex);
            it = matches[0].second
            )
        {
            if (it != inputString.cbegin())
            {
                newSubstances.insert(newSubstance);
            }
            newSubstance = std::make_pair(matches[2].str(), std::stoi(matches[1].str()));

            producedResources[newSubstance.first] = 0;
        }
        input[newSubstance.first] = std::make_pair(newSubstance.second, newSubstances);
    }

    //Almost every chemical is produced by exactly one reaction; the only exception, ORE, 
    //is the raw material input to the entire process and is not produced by a reaction.
    std::map<std::string, long long> oreIngredients;
    input["ORE"] = std::make_pair(1, oreIngredients);
    producedResources["ORE"] = 0;

    inputStream.close();
}

void Day14B::ProcessData()
{
    //After collecting ORE for a while, you check your cargo hold: 1 trillion (1000000000000) units of ORE.
    //Given 1 trillion ORE, what is the maximum amount of FUEL you can produce?
    long long lowerVal = 0;
    long long higherVal = 1000000000000ll;
    long long middleVal;

    do
    {
        middleVal = lowerVal + (higherVal - lowerVal) / 2;
        if (Produce("FUEL", middleVal) < 1000000000000ll)
        {
            lowerVal = middleVal;
        }
        else
        {
            higherVal = middleVal;
        }
    } while (lowerVal < higherVal);

    output = middleVal - 1;
}

void Day14B::SaveOutput()
{
    //What is the minimum amount of ORE required to produce exactly 1 FUEL?
    std::cout << "Result: " << output << std::endl;
}

long long Day14B::Produce(std::string what, long long quantity)
{
    //You just need to know how much ORE you'll need to collect before you can produce one unit of FUEL.
    long long ore = 0;
    for (auto& elem : input[what].second)
    {
        const long long howMuchDoWeNeed = quantity * elem.second;
        const long long howMuchDoWeHave = producedResources[elem.first];
        const long long howMuchDoWeNeedToProduce = howMuchDoWeNeed - howMuchDoWeHave;
        const long long howMuchDoWeProduceAtOnce = input[elem.first].first;
        const long long howManyReactionsDoWeNeed = CeilDiv(howMuchDoWeNeedToProduce, howMuchDoWeProduceAtOnce);
        const long long howMuchWillBeProduced = howMuchDoWeProduceAtOnce * howManyReactionsDoWeNeed;
        const long long howMuchWillBeLeft = howMuchWillBeProduced - howMuchDoWeNeedToProduce;
        producedResources[elem.first] = howMuchWillBeLeft;

        ore += elem.first == "ORE" ? howMuchDoWeNeedToProduce : Produce(elem.first, howManyReactionsDoWeNeed);
    }
    return ore;
}

inline long long Day14B::CeilDiv(long long x, long long y)
{
    return (x + y - 1) / y;
}
