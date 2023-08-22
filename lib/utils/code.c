#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#ifdef DEBUG
#endif

void exit_program(const char s[])
{
    NL;NL;NL;NL;NL;NL;
    PRINT("\nERRO");
    if(s != NULL)
        PRINT("\t%s",s);
    exit(EXIT_FAILURE);
}
