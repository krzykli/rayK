#ifndef LOGGERH
#define LOHHERH

#include <string>
#include <iostream>
#include <time.h>

#define CLOCK_FACTOR (double(CLOCKS_PER_SEC))

static const void debug_log(const std::string m)
{
    std::cout << "[TIME: " << clock() / CLOCK_FACTOR
              << " s] " << m << std::endl;
}

#endif LOGGERH
