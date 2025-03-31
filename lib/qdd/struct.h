#ifndef __QDD_STRUCT_H__
#define __QDD_STRUCT_H__

#include "header.h"

#include "../list/body/struct.h"

STRUCT(qdd)
{
    node_p node;
    list_body_p lb;
    int qbits;
};

#endif
