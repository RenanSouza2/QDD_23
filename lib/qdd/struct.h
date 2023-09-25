#ifndef __QDD_STRUCT_H__
#define __QDD_STRUCT_H__

#include "header.h"

#include "../list/list_body/struct.h"

STRUCT(qdd)
{
    node_p n;
    list_body_p lb;
    int qbits;
};

#endif
