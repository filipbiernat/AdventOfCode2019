#include "Day16A.h"

Day16A::Day16A()
    : output(0)
{
}

Day16A::~Day16A()
{
}

void Day16A::ReadInput()
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

void Day16A::ProcessData()
{
    //The base pattern is 0, 1, 0, -1.
    const std::vector<int> basePattern { 0, 1, 0, -1 };

    std::vector<std::vector<int> > multipliersMatrix;
    for (size_t positionInTheOutput = 0; positionInTheOutput < input.size(); ++positionInTheOutput)
    {
        // Then, repeat each value in the pattern a number of times equal to the position in the output list being considered.
        std::vector<int> baseMultipliers;
        for (int elem : basePattern)
        {
            std::fill_n(std::back_inserter(baseMultipliers), positionInTheOutput + 1, elem);
        }

        //When applying the pattern, skip the very first value exactly once.
        //So, for the second element of the output list, the actual pattern used would be: 
        //0, 1, 1, 0, 0, -1, -1, 0, 0, 1, 1, 0, 0, -1, -1, ....
        std::vector<int> multipliersForThisPosition;
        for (size_t i = 0; i < input.size(); ++i)
        {
            multipliersForThisPosition.push_back(baseMultipliers[(i + 1) % baseMultipliers.size()]);
        }
        multipliersMatrix.push_back(multipliersForThisPosition);
    }

    //FFT operates in repeated phases. In each phase, a new list is constructed with the same length as the input list. 
    //This new list is also used as the input for the next phase.
    std::vector<int> signal = input;
    for (size_t phase = 0; phase < 100; ++phase)
    {
        for (size_t signalDigit = 0; signalDigit < signal.size(); ++signalDigit)
        {
            //Each element in the new list is built by multiplying every value in the input list by a value in a repeating 
            //pattern and then adding up the results. 
            auto scalarProduct = std::inner_product(std::begin(signal), std::end(signal), std::begin(multipliersMatrix[signalDigit]), 0);
            //Then, only the ones digit is kept.
            signal[signalDigit] = abs(scalarProduct % 10);
        }
    }

    //After 100 phases of FFT, what are the first eight digits in the final output list?
    for (size_t signalDigit = 0; signalDigit < 8; ++signalDigit)
    {
        output += signal[signalDigit] * static_cast<int>(pow(10, 7 - signalDigit));
    }
}

void Day16A::SaveOutput()
{
    std::cout << "Result: " << output << std::endl;
}

