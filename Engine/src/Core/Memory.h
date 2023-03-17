#pragma once

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define EMBER_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define EMBER_DELETE delete
#else
#define EMBER_NEW new
#define EMBER_DELETE delete
#endif
