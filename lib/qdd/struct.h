#ifndef __QDD_STRUCT_H__
#define __QDD_STRUCT_H__

#include "header.h"

#include "../list/list_body/struct.h"

STRUCT(qdd)
{
    list_body_t lb;
    int qbits;
};

#endif
