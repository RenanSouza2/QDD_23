#ifndef __UTILS_DEBUG_H__
#define __UTILS_DEBUG_H__

#include "header.h"

#ifdef DEBUG

#include <stdbool.h>

#include "../macros/struct.h"

bool handler_display(char tag[], handler_p h);

bool int_str(int a, int b);

#endif

#endif
