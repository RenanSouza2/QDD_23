#ifndef __EXAMPLE_DEBUG_H__
#define __EXAMPLE_DEBUG_H__

#include "header.h"
#include "../node/header.h"

#ifdef DEBUG

void list_body_display(list_body_p lb);
void list_head_display(list_head_p lh);

#endif

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
#define L_LABEL(POINTER) (&(LB(POINTER)->n->lab))

list_body_p list_body_create(node_p n, list_body_p lb_next);

list_head_p list_head_create_cold();
list_head_p list_head_create(node_p n, list_head_p lh_next);

void list_body_remove(list_body_p lb, node_p n);

#endif
