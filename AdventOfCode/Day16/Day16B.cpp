#include "Day16B.h"

Day16B::Day16B()
    : output(0)
{
}

Day16B::~Day16B()
{
}

void Day16B::ReadInput()
{
    const std::string fileName = "Day16/Day16A.txt";

    std::ifstream inputStream(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return;
    }

    std::string inputString((std::istreambuf_iterator<char>(inputStream)),
        std::istreambuf_iterator<char>());

    //As input, FFT takes a list of numbers. In the signal you received (your puzzle input), each number is a single digit.
    std::for_each(
        inputString.begin(),
        inputString.end(),
        [this](const auto &elem)
    {
        input.push_back(elem - '0');
    });
    inputStream.close();
}

void Day16B::ProcessData()
{
    //The first seven digits of your initial input signal also represent the message offset. 
    //The message offset is the location of the eight-digit message in the final output list. 
    //Specifically, the message offset indicates the number of digits to skip before reading 
    //the eight-digit message. 
    int offset = 0;
    for (size_t offsetDigit = 0; offsetDigit < 7; ++offsetDigit)
    {
        offset += input[offsetDigit] * static_cast<int>(pow(10, 6 - offsetDigit));
    }

    //The real signal is your puzzle input repeated 10000 times. Treat this new signal as a single input list. 
    std::vector<int> signal;
    for (size_t i = offset; i < 10000 * input.size(); ++i)
    {
        signal.push_back(input[i % input.size()]);
    }

    //Patterns are still calculated as before, and 100 phases of FFT are still applied.
    for (size_t phase = 0; phase < 100; ++phase)
    {
        for (int signalDigit = signal.size() - 2; signalDigit >= 0; --signalDigit)
        {
            //Let's make it easier. Thanks to the offset, we are in the second part of the signal,
            //so the vector of multipliers consists of zeros and ones. E.g.: 
            //
            //1*0  + 2*0  + 3*0  + 4*0  + 5*1  + 6*1  + 7*1  + 8*1  = 6
            //1*0  + 2*0  + 3*0  + 4*0  + 5*0  + 6*1  + 7*1  + 8*1  = 1
            //1*0  + 2*0  + 3*0  + 4*0  + 5*0  + 6*0  + 7*1  + 8*1  = 5
            //1*0  + 2*0  + 3*0  + 4*0  + 5*0  + 6*0  + 7*0  + 8*1  = 8
            //
            //So... the current signal digit may be calculated as a sum of the input signal digit
            //and the next digit. All we need to do it to iterate backwards. Hooray!
            auto scalarProduct = signal[signalDigit] + signal[signalDigit + 1];
            //Then, only the ones digit is kept.
            signal[signalDigit] = abs(scalarProduct % 10);
        }
    }

    //After repeating your input signal 10000 times and running 100 phases of FFT,
    //what is the eight-digit message embedded in the final output list?
    for (size_t signalDigit = 0; signalDigit < 8; ++signalDigit)
    {
        output += signal[signalDigit] * static_cast<int>(pow(10, 7 - signalDigit));
    }
}

void Day16B::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

