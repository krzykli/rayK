// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <random>

// TODO: reference additional headers your program requires here
#define randf static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
