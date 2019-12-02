#include "Day2B.h"

Day2B::Day2B()
{
}

Day2B::~Day2B()
{
}

void Day2B::ReadInput()
{
    const std::string fileName = "Day2/Day2A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString;
    while (std::getline(inputStream, inputString, ','))
    {
        if (inputString.size() > 0)
        {
            const int inputInt = static_cast<int>(std::stoi(inputString, nullptr, 0));
            input.push_back(inputInt);
        }
    }
    inputStream.close();
}

void Day2B::ProcessData()
{
    for (int noun = 0; noun <= 99; ++noun)
    {
        for (int verb = 0; verb <= 99; ++verb)
        {
            //make sure you first reset the computer's memory to the values in the program
            std::vector<int> programCode = input;

            // In this program, the value placed in address 1 is called the noun
            // and the value placed in address 2 is called the verb.
            // Each of the two input values will be between 0 and 99, inclusive.
            programCode.at(1) = noun;
            programCode.at(2) = verb;

            //Find the input noun and verb that cause the program to produce the output 19690720
            if (19690720 == RunProgram(programCode))
            {
                //What is 100 * noun + verb? 
                output = 100 * noun + verb;
            }
        }
    }
}

void Day2B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

int Day2B::RunProgram(std::vector<int>& programCode)
{
    for (size_t i = 0; i < programCode.size(); i += 4)
    {
        //99 means that the program is finished and should immediately halt.
        if (99 == programCode.at(i))
        {
            return programCode.at(0);
        }
        else
        {
            int left = programCode.at(i + 1);
            int right = programCode.at(i + 2);
            int dest = programCode.at(i + 3);

            if (left < programCode.size() && right < programCode.size() && dest < programCode.size())
            {
                if (1 == programCode.at(i))
                {
                    // Opcode 1 adds together numbers read from two positions and stores the result in a third position. 
                    programCode.at(dest) = programCode.at(left) + programCode.at(right);
                }
                else if (2 == input.at(i))
                {
                    //Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them.
                    programCode.at(dest) = programCode.at(left) * programCode.at(right);
                }
            }
            else
            {
                break;
            }
        }
    }
    return -1;
}