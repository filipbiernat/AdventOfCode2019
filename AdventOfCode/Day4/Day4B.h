#pragma once
#include "../AdventDayPart.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Day4B :
    public AdventDayPart
{
public:
    Day4B();
    virtual ~Day4B();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int begin;
    int end;
    int output;
};

