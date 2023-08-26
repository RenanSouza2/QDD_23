#include "debug.h"

#ifdef DEBUG

#include <stdbool.h>
#include <assert.h>

#include "../utils/header.h"

#define R 2
#define V 1
#define C 0

void label_display(label_p lab)
{
    switch (lab->cl)
    {
        case C: PRINT("C"); break;
        case V: PRINT("V"); break;
        case R: PRINT("R"); break;
    
        default: assert(false);
    }
    PRINT("%d", lab->lv);
}

#endif

int label_compare(label_p lab_1, label_p lab_2)
{
    long l1 = *((long*)lab_1);
    long l2 = *((long*)lab_2);
    if(l1 < l2) return -1;
    if(l1 > l2) return  1;
    return 0;
}
