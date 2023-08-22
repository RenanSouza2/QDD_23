#ifndef __EXAMPLE_DEBUG_H__
#define __EXAMPLE_DEBUG_H__

#include "header.h"
#include "../node/header.h"

STRUCT(list_body)
{
    node_p n;
    list_body_p lb;
};

STRUCT(list_head)
{
    list_body_t lb;
    list_head_p lh;
};

#define LB(POINTER)    ((list_body_p)(POINTER))
#define LH(POINTER)    ((list_head_p)(POINTER))

#endif
