#include "Day7A.h"

Day7A::Day7A()
{
}

Day7A::~Day7A()
{
}

void Day7A::ReadInput()
{
    const std::string fileName = "Day7/Day7a.txt";

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
}

void Day7A::ProcessData()
{
    int phaseSettings[5] = { 0, 1, 2, 3, 4 };
    int highestSignal = 0;

    //trying every possible combination of phase settings on the amplifiers.
    do 
    {
        output = 0;
        for (int i = 0; i < 5; ++i)
        {
            //Make sure that memory is not shared or reused between copies of the program.
            std::vector<int> currentProgramCode = programCode;
            clearQueue(programInput);

            //When a copy of the program starts running on an amplifier, it will first use an input instruction to 
            //ask the amplifier for its current phase setting (an integer from 0 to 4).
            programInput.push(phaseSettings[i]);
            //The program will then call another input instruction to get the amplifier's input signal, compute the 
            //correct output signal, and supply it back to the amplifier with an output instruction. 
            programInput.push(output);
            RunProgram(currentProgramCode);
            //Your job is to find the largest output signal that can be sent to the thrusters
            highestSignal = std::max(highestSignal, output);
        }
    } 
    while (std::next_permutation(phaseSettings, phaseSettings + 5));
    output = highestSignal;
}

void Day7A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

int Day7A::RunProgram(std::vector<int>& programCode)
{
    //It is important to remember that the instruction pointer should increase by the number of values in the 
    //instruction after the instruction finishes. Because of the new instructions, this amount is no longer always 4.
    int instructionDelta = 0;
    for (size_t instructionPointer = 0; instructionPointer < programCode.size(); instructionPointer += instructionDelta)
    {

        //std::cout << "               " << instructionPointer << " " << programCode.at(instructionPointer) << std::endl;
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
                programCode.at(programCode.at(instructionPointer + 1)) = AccessInput();
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

void Day7A::clearQueue(std::queue<std::reference_wrapper<int> > &q)
{
    std::queue<std::reference_wrapper<int> > empty;
    std::swap(q, empty);
}

int Day7A::AccessInput()
{
     int input = programInput.front();
     programInput.pop();
     return input;
}
