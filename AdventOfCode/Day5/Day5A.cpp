#include "Day5A.h"

Day5A::Day5A()
{
}

Day5A::~Day5A()
{
}

void Day5A::ReadInput()
{
    const std::string fileName = "Day5/Day5a.txt";

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
            programCode.push_back(inputInt);
        }
    }
    inputStream.close();

    input = 1;
}

void Day5A::ProcessData()
{
    RunProgram(programCode);
}

void Day5A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

int Day5A::RunProgram(std::vector<int>& programCode)
{
    //It is important to remember that the instruction pointer should increase by the number of values in the 
    //instruction after the instruction finishes. Because of the new instructions, this amount is no longer always 4.
    int instructionDelta = 0;
    for (size_t i = 0; i < programCode.size(); i += instructionDelta)
    {
        //99 means that the program is finished and should immediately halt.
        if (99 == programCode.at(i))
        {
            return programCode.at(0);
        }
        else
        {
            //Parameter modes are stored in the same value as the instruction's opcode. The opcode is a two-digit number 
            //based only on the ones and tens digit of the value, that is, the opcode is the rightmost two digits of the 
            //first value in an instruction. Parameter modes are single digits, one per parameter, read right-to-left from 
            //the opcode: the first parameter's mode is in the hundreds digit, the second parameter's mode is in the 
            //thousands digit, the third parameter's mode is in the ten-thousands digit, and so on. Any missing modes are 0.
            int instruction = programCode.at(i);
            int splittedInstruction[5] = { 0 };
            for (int digit = 0; digit < 5; ++digit)
            {
                splittedInstruction[digit] = instruction % 10;
                instruction /= 10;
            }
            int opcode = 10 * splittedInstruction[1] + splittedInstruction[0];

            auto AccessData = [&](int i, int pos, int* splittedInstruction) -> unsigned int
            {
                return 0 == splittedInstruction[pos+1] ? programCode.at(programCode.at(i + pos)) : programCode.at(i + pos);
            };

            if (1 == opcode)
            {
                // Opcode 1 adds together numbers read from two positions and stores the result in a third position. 
                programCode.at(programCode.at(i + 3)) = AccessData(i, 1, splittedInstruction) + AccessData(i, 2, splittedInstruction);
                instructionDelta = 4;
            }
            else if (2 == opcode)
            {
                //Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them.
                programCode.at(programCode.at(i + 3)) = AccessData(i, 1, splittedInstruction) * AccessData(i, 2, splittedInstruction);
                instructionDelta = 4;
            }
            else if (3 == opcode)
            {
                //Opcode 3 takes a single integer as input and saves it to the position given by its only parameter. 
                programCode.at(programCode.at(i + 1)) = input;
                instructionDelta = 2;
            }
            else if (4 == opcode)
            {
                //Opcode 4 outputs the value of its only parameter.
                output = AccessData(i, 1, splittedInstruction);
                instructionDelta = 2;
            }
        }
    }
    return -1;
}