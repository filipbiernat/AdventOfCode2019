﻿#include <iostream>
#include <memory>
#include "AdventDay.h"
#include "Day0\Day0.h"
#include "Day1\Day1A.h"
#include "Day1\Day1B.h"
#include "Day2\Day2A.h"
#include "Day2\Day2B.h"
#include "Day3\Day3A.h"
#include "Day3\Day3B.h"
#include "Day4\Day4A.h"
#include "Day4\Day4B.h"
#include "Day5\Day5A.h"
#include "Day5\Day5B.h"
#include "Day6\Day6A.h"
#include "Day6\Day6B.h"
#include "Day7\Day7A.h"
#include "Day7\Day7B.h"
#include "Day8\Day8A.h"
#include "Day8\Day8B.h"
#include "Day9\Day9A.h"
#include "Day9\Day9B.h"
#include "Day10\Day10A.h"
#include "Day10\Day10B.h"
#include "Day11\Day11A.h"
//#include "Day11\Day11B.h"

int main()
{
    //AdventDay( 1, std::make_unique<Day1A>(), std::make_unique<Day1B>());
    //AdventDay( 2, std::make_unique<Day2A>(), std::make_unique<Day2B>());
    //AdventDay( 3, std::make_unique<Day3A>(), std::make_unique<Day3B>());
    //AdventDay( 4, std::make_unique<Day4A>(), std::make_unique<Day4B>());
    //AdventDay( 5, std::make_unique<Day5A>(), std::make_unique<Day5B>());
    //AdventDay( 6, std::make_unique<Day6A>(), std::make_unique<Day6B>());
    //AdventDay( 7, std::make_unique<Day7A>(), std::make_unique<Day7B>());
    //AdventDay( 8, std::make_unique<Day8A>(), std::make_unique<Day8B>());
    //AdventDay( 9, std::make_unique<Day9A>(), std::make_unique<Day9B>());
    //AdventDay(10, std::make_unique<Day10A>(), std::make_unique<Day10B>());
    AdventDay(11, std::make_unique<Day11A>(), std::make_unique<Day0>());

    std::cout << "Execution completed." << std::endl;
    return 0;
}