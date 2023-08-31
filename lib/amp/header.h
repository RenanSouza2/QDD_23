#ifndef __AMP_H__
#define __AMP_H__

#include "../../static_utils/struct.h"

typedef double number_t;

STRUCT(amp)
{
    number_t re, im;
};

typedef double number_t;

int amp_compare(amp_p amp_1, amp_p amp_2);

#endif
