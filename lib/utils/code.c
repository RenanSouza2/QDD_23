#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#ifdef DEBUG

int display_header(char s[], handler_p p)
{
    PRINT("\nAddress (%s): %p", s, p);
    return p == NULL;
}

#endif
