#ifndef __LABEL_DEBUG_H__
#define __LABEL_DEBUG_H__

#include "header.h"

STRUCT(label)
{
    int cl, lv;
};

void label_display(label_p lab);

#endif
