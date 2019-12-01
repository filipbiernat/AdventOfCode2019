#pragma once
#include "../AdventDayPart.h"
class Day0 :
    public AdventDayPart
{
public:
    Day0();
    virtual ~Day0();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();
};

