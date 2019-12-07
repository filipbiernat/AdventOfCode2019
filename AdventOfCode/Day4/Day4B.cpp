#include "Day4B.h"

Day4B::Day4B()
    : output(0)
{
}

Day4B::~Day4B()
{
}

void Day4B::ReadInput()
{
    begin = 206938;
    end = 679128;
}

void Day4B::ProcessData()
{
    //It is a six-digit number.
    const int size = 6;
    int number[size] = { 0 };

    //Going from left to right, the digits never decrease; they only ever increase or stay the same 
    for (; number[0] < 10; ++number[0])
    {
        for (number[1] = number[0]; number[1] < 10; ++number[1])
        {
            for (number[2] = number[1]; number[2] < 10; ++number[2])
            {
                for (number[3] = number[2]; number[3] < 10; ++number[3])
                {
                    for (number[4] = number[3]; number[4] < 10; ++number[4])
                    {
                        for (number[5] = number[4]; number[5] < 10; ++number[5])
                        {
                            int fullNumber = 100000 * number[0] + 10000 * number[1] + 1000 * number[2] +
                                100 * number[3] + 10 * number[4] + number[5];

                            //The value is within the range given in your puzzle input.
                            if (fullNumber > begin)
                            {
                                if (fullNumber > end)
                                {
                                    return;
                                }

                                //Two adjacent digits are the same
                                for (int k = 0; k < size - 1; ++k)
                                {
                                    if (number[k] == number[k + 1])
                                    {
                                        //the two adjacent matching digits are not part of a larger group of matching digit
                                        if ((k == 0 || number[k - 1] != number[k]) &&
                                            (k == size - 2 || number[k + 1] != number[k + 2]))
                                        {
                                            ++output;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Day4B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}
