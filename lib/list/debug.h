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

list_body_p list_body_create(node_p n, list_body_p lb_next);
list_head_p list_head_create(node_p n, list_head_p lh_next);

#endif
