#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#ifdef DEBUG

bool int_str(int a, int b)
{
    if(a != b)
    {
        printf("\n\n\tINT ASSERTION ERROR\t| VALUE MISMATH\t| %d %d", a, b);
        return false;
    }

    return true;
}

#endif



bool handler_display(char tag[], handler_p h)
{
    PRINT("\nAddress (%s): %p", tag, h);
    return h == NULL;
}
