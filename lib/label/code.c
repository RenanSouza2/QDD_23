#include "debug.h"

#ifdef DEBUG

#include "../utils/header.h"
#include "../macros/assert.h"



void label_display(label_t lab)
{
    if(label_is_amp(&lab))
    {
        PRINT("AMPLITUDE");
        return;
    }

    switch (lab.cl)
    {
        case C: PRINT("C"); break;
        case V: PRINT("V"); break;
        case R: PRINT("R"); break;

        default: assert(false);
    }
    PRINT("%d", lab.lv);
}



bool label(label_t lab_1, label_t lab_2)
{
    if(label_compare(&lab_1, &lab_2) != 0)
    {
        printf("\n\n\tLABEL ASSERTION ERROR\t| LABEL MISMATCH | ");
        label_display(lab_1);
        PRINT(" ");
        label_display(lab_2);
        return false;
    }

    return true;
}

#endif



#define LONG(LABEL) (*((long*)(LABEL)))

int label_compare(label_p lab_1, label_p lab_2)
{
    long l1 = LONG(lab_1);
    long l2 = LONG(lab_2);
    if(l1 < l2) return -1;
    if(l1 > l2) return  1;
    return 0;
}

bool label_is_amp(label_p lab)
{
    return LONG(lab) == 0;
}
