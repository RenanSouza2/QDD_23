#ifndef __AMP_STRUCT_H__
#define __AMP_STRUCT_H__

#include "header.h"

#define AMP(RE, IM) (amp_t){RE, IM}

typedef double number_t;

STRUCT(amp)
{
    number_t re, im;
};

#endif