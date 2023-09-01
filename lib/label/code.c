#include "debug.h"

#ifdef DEBUG

#include <stdbool.h>
#include <assert.h>

#include "../utils/header.h"

#define R 2
#define V 1
#define C 0

void label_display(label_c const lab)
{
    if(label_is_amp(lab))
    {
        PRINT("AMPLITUDE");
        return;
    }

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

#define LONG(LABEL) (*((long*)(LABEL)))

int label_compare(label_c const lab_1, label_c const lab_2)
{
    long const l1 = LONG(lab_1);
    long const l2 = LONG(lab_2);
    if(l1 < l2) return -1;
    if(l1 > l2) return  1;
    return 0;
}

int label_is_amp(label_c const lab)
{
    return LONG(lab) == 0;
}
