#include "Day5B.h"

Day5B::Day5B()
{
}

Day5B::~Day5B()
{
}

void Day5B::ReadInput()
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

    //This time, when the TEST diagnostic program runs its input instruction to get the ID of the system to test, 
    //provide it 5, the ID for the ship's thermal radiator controller.
    input = 5;
}

void Day5B::ProcessData()
{
    RunProgram(programCode);
}

void Day5B::SaveOutput()
{
    //What is the diagnostic code for system ID 5?
    std::cout << "Result: " << output << std::endl;
}

int Day5B::RunProgram(std::vector<int>& programCode)
{
    //It is important to remember that the instruction pointer should increase by the number of values in the 
    //instruction after the instruction finishes. Because of the new instructions, this amount is no longer always 4.
    int instructionDelta = 0;
    for (size_t instructionPointer = 0; instructionPointer < programCode.size(); instructionPointer += instructionDelta)
    {
        //99 means that the program is finished and should immediately halt.
        if (99 == programCode.at(instructionPointer))
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
            int instruction = programCode.at(instructionPointer);
            int splittedInstruction[5] = { 0 };
            for (int digit = 0; digit < 5; ++digit)
            {
                splittedInstruction[digit] = instruction % 10;
                instruction /= 10;
            }
            int opcode = 10 * splittedInstruction[1] + splittedInstruction[0];

            auto AccessData = [&](int i, int pos, int* splittedInstruction) -> unsigned int
            {
                return 0 == splittedInstruction[pos + 1] ? programCode.at(programCode.at(i + pos)) : programCode.at(i + pos);
            };

            if (1 == opcode)
            {
                instructionDelta = 4;
                // Opcode 1 adds together numbers read from two positions and stores the result in a third position. 
                programCode.at(programCode.at(instructionPointer + 3)) =
                    AccessData(instructionPointer, 1, splittedInstruction) + AccessData(instructionPointer, 2, splittedInstruction);
            }
            else if (2 == opcode)
            {
                instructionDelta = 4;
                //Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them.
                programCode.at(programCode.at(instructionPointer + 3)) =
                    AccessData(instructionPointer, 1, splittedInstruction) * AccessData(instructionPointer, 2, splittedInstruction);
            }
            else if (3 == opcode)
            {
                instructionDelta = 2;
                //Opcode 3 takes a single integer as input and saves it to the position given by its only parameter. 
                programCode.at(programCode.at(instructionPointer + 1)) = input;
            }
            else if (4 == opcode)
            {
                instructionDelta = 2;
                //Opcode 4 outputs the value of its only parameter.
                output = AccessData(instructionPointer, 1, splittedInstruction);
            }
            else if (5 == opcode)
            {
                instructionDelta = 3;
                //Opcode 5 is jump-if-true: if the first parameter is non-zero, it sets the instruction pointer 
                //to the value from the second parameter. Otherwise, it does nothing.
                if (0 != AccessData(instructionPointer, 1, splittedInstruction))
                {
                    instructionPointer = AccessData(instructionPointer, 2, splittedInstruction);

                    // However, if the instruction modifies the instruction pointer, that value is used and the 
                    //instruction pointer is not automatically increased.
                    instructionDelta = 0;
                }
            }
            else if (6 == opcode)
            {
                instructionDelta = 3;
                //Opcode 6 is jump-if-false: if the first parameter is zero, it sets the instruction pointer 
                //to the value from the second parameter. Otherwise, it does nothing.
                if (0 == AccessData(instructionPointer, 1, splittedInstruction))
                {
                    instructionPointer = AccessData(instructionPointer, 2, splittedInstruction);

                    // However, if the instruction modifies the instruction pointer, that value is used and the 
                    //instruction pointer is not automatically increased.
                    instructionDelta = 0;
                }
            }
            else if (7 == opcode)
            {
                instructionDelta = 4;
                //Opcode 7 is less than: if the first parameter is less than the second parameter, it stores 1 
                //in the position given by the third parameter. Otherwise, it stores 0
                programCode.at(programCode.at(instructionPointer + 3)) =
                    (AccessData(instructionPointer, 1, splittedInstruction) < AccessData(instructionPointer, 2, splittedInstruction)) ? 1 : 0;
            }
            else if (8 == opcode)
            {
                instructionDelta = 4;
                //Opcode 8 is equals: if the first parameter is equal to the second parameter, it stores 1 
                //in the position given by the third parameter. Otherwise, it stores 0
                programCode.at(programCode.at(instructionPointer + 3)) =
                    (AccessData(instructionPointer, 1, splittedInstruction) == AccessData(instructionPointer, 2, splittedInstruction)) ? 1 : 0;
            }

        }
    }
    return -1;
}