#pragma once
#include "../AdventDayPart.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Day4A :
    public AdventDayPart
{
public:
    Day4A();
    virtual ~Day4A();

protected:
    virtual void ReadInput();
    virtual void ProcessData();
    virtual void SaveOutput();

private:
    int begin;
    int end;
    int output;
};

