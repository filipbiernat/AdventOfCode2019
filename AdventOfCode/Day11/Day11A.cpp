#include "Day11A.h"

Day11A::Day11A() :
    output(0),
    map(400, std::vector<int>(400, 0)),
    paintingCnt(400, std::vector<int>(400, 0)),
    x(200),
    y(200),
    direction('U')
{
}

Day11A::~Day11A()
{
}

void Day11A::ReadInput()
{
    const std::string fileName = "Day11/Day11A.txt";

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
            //The computer should have support for large numbers. Some instructions near the beginning of the 
            //BOOST program will verify this capability.
            programCode.push_back(std::stoll(inputString, nullptr, 0));
        }
    }
    inputStream.close();

    //The BOOST program will ask for a single input; run it in test mode by providing it the value 1. 
    input = 0;
}

void Day11A::ProcessData()
{
    //Although it takes almost three hours for their reply signal to reach you, they send instructions for how 
    //to power up the emergency hull painting robot and even provide a small Intcode program (your puzzle input) 
    //that will cause it to paint your ship appropriately.
    RunProgram(programCode);

    //specifically, you need to know the number of panels it paints at least once, regardless of color.
    for (auto& vec : paintingCnt)
    {
        for (auto& elem : vec)
        {
            if (elem)
            {
                ++output;
            }
        }
    }
}

void Day11A::SaveOutput()
{
    std::cout << output << std::endl;
}

long long Day11A::RunProgram(std::vector<long long>& programCode)
{
    //It is important to remember that the instruction pointer should increase by the number of values in the 
    //instruction after the instruction finishes. Because of the new instructions, this amount is no longer always 4.
    long long instructionDelta = 0;

    //The important difference is that relative mode parameters don't count from address 0. Instead, they count from 
    //a value called the relative base. The relative base starts at 0.
    long long relativeBase = 0;

    for (long long instructionPointer = 0; instructionPointer < programCode.size(); instructionPointer += instructionDelta)
    {
        auto AccessCode = [&](long long instructionPointer) -> long long&
        {
            //The computer's available memory should be much larger than the initial program. Memory beyond the initial 
            //program starts with the value 0 and can be read or written like any other memory. (It is invalid to try 
            //to access memory at a negative address, though.)
            if (programCode.size() <= instructionPointer)
            {
                programCode.resize(static_cast<size_t>(instructionPointer + 1), 0);
            }
            return programCode.at(static_cast<const unsigned int>(instructionPointer));
        };

        //99 means that the program is finished and should immediately halt.
        if (99ll == AccessCode(instructionPointer))
        {
            return AccessCode(0);
        }
        else
        {
            //Parameter modes are stored in the same value as the instruction's opcode. The opcode is a two-digit number 
            //based only on the ones and tens digit of the value, that is, the opcode is the rightmost two digits of the 
            //first value in an instruction. Parameter modes are single digits, one per parameter, read right-to-left from 
            //the opcode: the first parameter's mode is in the hundreds digit, the second parameter's mode is in the 
            //thousands digit, the third parameter's mode is in the ten-thousands digit, and so on. Any missing modes are 0.
            long long instruction = AccessCode(instructionPointer);
            long long splittedInstruction[5] = { 0 };
            for (int digit = 0; digit < 5; ++digit)
            {
                splittedInstruction[digit] = instruction % 10;
                instruction /= 10;
            }
            long long opcode = 10 * splittedInstruction[1] + splittedInstruction[0];

            auto AccessData = [&](long long i, long long pos, long long* splittedInstruction) -> long long&
            {
                if (1 == splittedInstruction[pos + 1])
                {
                    return AccessCode(i + pos);
                }
                else if (2 == splittedInstruction[pos + 1])
                {
                    //Parameters in mode 2, relative mode, behave very similarly to parameters in position mode: the 
                    //parameter is interpreted as a position. Like position mode, parameters in relative mode can be 
                    //read from or written to.
                    //The address a relative mode parameter refers to is itself plus the current relative base. When 
                    //the relative base is 0, relative mode parameters and position mode parameters with the same 
                    //value refer to the same address.
                    return AccessCode(AccessCode(i + pos) + relativeBase);
                }
                return AccessCode(AccessCode(i + pos));
            };

            if (1ll == opcode)
            {
                instructionDelta = 4;
                // Opcode 1 adds together numbers read from two positions and stores the result in a third position. 
                AccessData(instructionPointer, 3, splittedInstruction) =
                    AccessData(instructionPointer, 1, splittedInstruction) + AccessData(instructionPointer, 2, splittedInstruction);
            }
            else if (2ll == opcode)
            {
                instructionDelta = 4;
                //Opcode 2 works exactly like opcode 1, except it multiplies the two inputs instead of adding them.
                AccessData(instructionPointer, 3, splittedInstruction) =
                    AccessData(instructionPointer, 1, splittedInstruction) * AccessData(instructionPointer, 2, splittedInstruction);
            }
            else if (3ll == opcode)
            {
                instructionDelta = 2;
                //Opcode 3 takes a single integer as input and saves it to the position given by its only parameter. 
                AccessData(instructionPointer, 1, splittedInstruction) = input;
            }
            else if (4ll == opcode)
            {
                instructionDelta = 2;
                //Opcode 4 outputs the value of its only parameter.
                long long thisOutput = AccessData(instructionPointer, 1, splittedInstruction);
                intcodeOutput.push_back(thisOutput);
                ProcessOutput();
            }
            else if (5ll == opcode)
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
            else if (6ll == opcode)
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
            else if (7ll == opcode)
            {
                instructionDelta = 4;
                //Opcode 7 is less than: if the first parameter is less than the second parameter, it stores 1 
                //in the position given by the third parameter. Otherwise, it stores 0
                AccessData(instructionPointer, 3, splittedInstruction) =
                    (AccessData(instructionPointer, 1, splittedInstruction) < AccessData(instructionPointer, 2, splittedInstruction)) ? 1 : 0;
            }
            else if (8ll == opcode)
            {
                instructionDelta = 4;
                //Opcode 8 is equals: if the first parameter is equal to the second parameter, it stores 1 
                //in the position given by the third parameter. Otherwise, it stores 0
                AccessData(instructionPointer, 3, splittedInstruction) =
                    (AccessData(instructionPointer, 1, splittedInstruction) == AccessData(instructionPointer, 2, splittedInstruction)) ? 1 : 0;
            }
            else if (9ll == opcode)
            {
                instructionDelta = 2;
                //Opcode 9 adjusts the relative base by the value of its only parameter. The relative base
                //increases (or decreases, if the value is negative) by the value of the parameter.
                relativeBase += AccessData(instructionPointer, 1, splittedInstruction);
            }

        }
    }
    return -1;
}

void Day11A::ProcessOutput()
{
    if (intcodeOutput.size() > 1)
    {
        //First, it will output a value indicating the color to paint the panel the robot is over: 0 means 
        //to paint the panel black, and 1 means to paint the panel white.
        if (map[x][y] != intcodeOutput[0])
        {
            map[x][y] = static_cast<int>(intcodeOutput[0]);
            ++paintingCnt[x][y];
        }

        //Second, it will output a value indicating the direction the robot should turn: 0 means it should 
        //turn left 90 degrees, and 1 means it should turn right 90 degrees.
        //After the robot turns, it should always move forward exactly one panel. The robot starts facing up.
        if (intcodeOutput[1] == 0)
        {
            TurnLeft();
        }
        else
        {
            TurnRight();
        }

        intcodeOutput.clear();
        //The program uses input instructions to access the robot's camera: provide 0 if the robot is over 
        //a black panel or 1 if the robot is over a white panel.
        input = map[x][y];
    }
}

void Day11A::TurnLeft()
{
    if (direction == 'U')
    {
        --x;
        direction = 'L';
    }
    else if (direction == 'L')
    {
        ++y;
        direction = 'D';
    }
    else if (direction == 'D')
    {
        ++x;
        direction = 'R';
    }
    else if (direction == 'R')
    {
        --y;
        direction = 'U';
    }
}

void Day11A::TurnRight()
{
    if (direction == 'U')
    {
        ++x;
        direction = 'R';
    }
    else if (direction == 'R')
    {
        ++y;
        direction = 'D';
    }
    else if (direction == 'D')
    {
        --x;
        direction = 'L';
    }
    else if (direction == 'L')
    {
        --y;
        direction = 'U';
    }
}
