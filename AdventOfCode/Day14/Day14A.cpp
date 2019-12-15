#include "Day14A.h"

Day14A::Day14A()
{
}

Day14A::~Day14A()
{
}

void Day14A::ReadInput()
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
        std::pair<std::vector<int>, std::vector<int> > inputLine;
        std::regex word_regex("(\\d+) ([A-Z]+)");
        std::smatch matches;

        std::map<std::string, int> newSubstances;
        std::pair<std::string, int> newSubstance;
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
    std::map<std::string, int> oreIngredients;
    input["ORE"] = std::make_pair(1, oreIngredients);
    producedResources["ORE"] = 0;

    inputStream.close();
}

void Day14A::ProcessData()
{
    output = Produce("FUEL");
}

void Day14A::SaveOutput()
{
    //What is the minimum amount of ORE required to produce exactly 1 FUEL?
    std::cout << "Result: " << output << std::endl;
}

int Day14A::Produce(std::string what, int quantity)
{
    //You just need to know how much ORE you'll need to collect before you can produce one unit of FUEL.
    int ore = 0;
    for (auto& elem : input[what].second)
    {
        const int howMuchDoWeNeed = quantity * elem.second;
        const int howMuchDoWeHave = producedResources[elem.first];
        const int howMuchDoWeNeedToProduce = howMuchDoWeNeed - howMuchDoWeHave;
        const int howMuchDoWeProduceAtOnce = input[elem.first].first;
        const int howManyReactionsDoWeNeed = CeilDiv(howMuchDoWeNeedToProduce, howMuchDoWeProduceAtOnce);
        const int howMuchWillBeProduced = howMuchDoWeProduceAtOnce * howManyReactionsDoWeNeed;
        const int howMuchWillBeLeft = howMuchWillBeProduced - howMuchDoWeNeedToProduce;
        producedResources[elem.first] = howMuchWillBeLeft;

        ore += elem.first == "ORE" ? howMuchDoWeNeedToProduce : Produce(elem.first, howManyReactionsDoWeNeed);
    }
    return ore;
}

inline int Day14A::CeilDiv(int x, int y)
{
    return (x + y - 1) / y;
}
