#include <stdio.h>

#include "debug.h"

#ifdef DEBUG
#endif

bool str_eq(str_p str_1, str_p str_2)
{
    return (str_1->el == str_2->el) && (str_1->th == str_2->th);
}
