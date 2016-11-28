#pragma once
#include <string>
#include <iostream>
#include <time.h>

#define CLOCK_FACTOR (double(CLOCKS_PER_SEC)*1000)

static const void debug_log(const std::string m)
{
	std::cout << "[TIME: " << clock() / CLOCK_FACTOR
		      << " ms] " << m << std::endl;
}
