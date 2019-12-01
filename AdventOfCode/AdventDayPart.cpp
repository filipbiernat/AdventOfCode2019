#include "AdventDayPart.h"

AdventDayPart::AdventDayPart()
{
}

AdventDayPart::~AdventDayPart()
{
}

void AdventDayPart::Execute()
{
    std::cout << "    Reading input..." << std::endl;
    ReadInput();
    std::cout << "    Processing data..." << std::endl;
    ProcessData();
    std::cout << "    Saving output..." << std::endl;
    SaveOutput();
    std::cout << std::endl;
}
