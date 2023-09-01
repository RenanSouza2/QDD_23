#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#ifdef DEBUG

int display_header(char s[], handler_c const p)
{
    PRINT("\nAddress (%s): %p", s, p);
    return p == NULL;
}

#endif
