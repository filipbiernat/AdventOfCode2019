#include "Day7B.h"

Day7B::Day7B()
{
}

Day7B::~Day7B()
{
}

void Day7B::ReadInput()
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

void Day7B::ProcessData()
{
    //In feedback loop mode, the amplifiers need totally different phase settings: 
    //integers from 5 to 9, again each used exactly once.
    int phaseSettings[5] = { 5, 6, 7, 8, 9 };
    int highestSignal = 0;

    //trying every possible combination of phase settings on the amplifiers.
    do
    {
        //Don't restart the Amplifier Controller Software on any amplifier during this process. 
        //Each one should continue receiving and sending signals until it halts.
        std::vector<std::vector<int> > programCodes(5, programCode);
        std::vector<int> instructionPointers(5, 0);

        // Provide each amplifier its phase setting at its first input instruction; 
        //all further input/output instructions are for signals.
        std::vector<std::queue<int>> programInput(5);
        for (int i = 0; i < 5; ++i)
        {
            programInput.at(i).push(phaseSettings[i]);
        }
        //To start the process, a 0 signal is sent to amplifier A's input exactly once.
        programInput.at(0).push(0);

        for (int i = 0; i < 5; i = (i + 1) % 5)
        {
            auto retVal = RunProgram(programCodes.at(i), static_cast<size_t>(instructionPointers.at(i)), programInput.at(i));
            if (std::get<0>(retVal) != output)
            {
                //Eventually, the software on the amplifiers will halt after they have processed the final loop. 
                //When this happens, the last output signal from amplifier E is sent to the thrusters.
                highestSignal = std::max(highestSignal, output);
                break;
            }
            else
            {
                //Most of the amplifiers are connected as they were before; amplifier A's output is connected to amplifier B's input, and so on. 
                //However, the output from amplifier E is now connected into amplifier A's input. 
                programInput.at((i + 1) % 5).push(std::get<0>(retVal));
                instructionPointers.at(i) = std::get<1>(retVal);
            }
        }
    } while (std::next_permutation(phaseSettings, phaseSettings + 5));
    output = highestSignal;
}

void Day7B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

std::pair<int, int> Day7B::RunProgram(std::vector<int>& programCode, size_t instructionPointer, std::queue<int>& programInput)
{
    //It is important to remember that the instruction pointer should increase by the number of values in the 
    //instruction after the instruction finishes. Because of the new instructions, this amount is no longer always 4.
    int instructionDelta = 0;
    for (; instructionPointer < programCode.size(); instructionPointer += instructionDelta)
    {
        //99 means that the program is finished and should immediately halt.
        if (99 == programCode.at(instructionPointer))
        {
            return std::make_pair(programCode.at(0), instructionPointer);
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
                programCode.at(programCode.at(instructionPointer + 1)) = programInput.front();
                programInput.pop();
            }
            else if (4 == opcode)
            {
                instructionDelta = 2;
                //Opcode 4 outputs the value of its only parameter.
                output = AccessData(instructionPointer, 1, splittedInstruction);
                return std::make_pair(output, instructionPointer + instructionDelta);
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
    return std::make_pair(-1, instructionPointer);
}
