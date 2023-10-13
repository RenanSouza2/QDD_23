#include <assert.h>

#include "debug.h"
#include "../utils/header.h"

#ifdef DEBUG

#define R 2
#define V 1
#define C 0

#endif

#define LONG(LABEL) (*((long*)(LABEL)))

int label_compare(label_p lab_1, label_p lab_2)
{
    assert(lab_1);
    assert(lab_2);

    long l1 = LONG(lab_1);
    long l2 = LONG(lab_2);
    if(l1 < l2) return -1;
    if(l1 > l2) return  1;
    return 0;
}

int label_is_amp(label_p lab)
{
    assert(lab);
    return LONG(lab) == 0;
}

void label_display(label_p lab)
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
