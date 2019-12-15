#include "Day13B.h"

Day13B::Day13B()
{
}

Day13B::~Day13B()
{
}

void Day13B::ReadInput()
{
    const std::string fileName = "Day13/Day13A.txt";

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

    input = 0;
    
    //Unfortunately, you did not bring any quarters.Memory address 0 represents the number of quarters that 
    //have been inserted; set it to 2 to play for free.
    programCode[0] = 2;
}

void Day13B::ProcessData()
{
    //The arcade cabinet runs Intcode software like the game the Elves sent (your puzzle input). 
    RunProgram(programCode);
}

void Day13B::SaveOutput()
{
    //How many block tiles are on the screen when the game exits?
    std::cout << "Result: " << output << std::endl;
}

long long Day13B::RunProgram(std::vector<long long>& programCode)
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
                programOutput.push_back(thisOutput);
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

void Day13B::ProcessOutput()
{
    //The software draws tiles to the screen with output instructions: every three output instructions 
    //specify the x position (distance from the left), y position (distance from the top), and tile id. 
    if (programOutput.size() > 2)
    {
        if (-1 == programOutput[0] && 0 == programOutput[1])
        {
            //When three output instructions specify X=-1, Y=0, the third output instruction is not 
            //a tile; the value instead specifies the new score to show in the segment display. 
            output = static_cast<int>(programOutput[2]);
        }
        else if (3 == programOutput[2])
        {
            //3 is a horizontal paddle tile. The paddle is indestructible.
            paddleX = programOutput[0];
        }
        else if (4 == programOutput[2])
        {
            //4 is a ball tile. The ball moves diagonally and bounces off objects.
            ballX = programOutput[0];
        }

        programOutput.clear();

        //The arcade cabinet has a joystick that can move left and right. The software reads the position of
        //the joystick with input instructions:
        // - If the joystick is in the neutral position, provide 0.
        // - If the joystick is tilted to the left, provide - 1.
        // - If the joystick is tilted to the right, provide 1.
        input = (ballX > paddleX) - (ballX < paddleX);
    }
}