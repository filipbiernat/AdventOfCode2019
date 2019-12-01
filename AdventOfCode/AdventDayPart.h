#pragma once
#include <iostream>

class AdventDayPart
{
public:
    AdventDayPart();
    virtual ~AdventDayPart();

    void Execute();

protected:
    virtual void ReadInput() = 0;
    virtual void ProcessData() = 0;
    virtual void SaveOutput() = 0;
};

