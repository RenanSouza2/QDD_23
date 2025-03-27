#ifndef __AMP_STRUCT_H__
#define __AMP_STRUCT_H__

#include "header.h"

typedef double number_t;

STRUCT(amp)
{
    number_t re, im;
};

bool amp_eq(amp_t amp_1, amp_t amp_2);

#endif