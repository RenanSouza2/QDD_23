#ifndef __LABEL_STRUCT_H__
#define __LABEL_STRUCT_H__

#include "header.h"

STRUCT(label)
{
    int cl, lv;
};

#define LAB(CL, LV) (label_t){CL, LV}

#endif