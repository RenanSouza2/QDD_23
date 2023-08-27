#ifndef __NODE_DEBUG_H__
#define __NODE_DEBUG_H__

#include "header.h"
#include "../list/debug.h"
#include "../label/debug.h"

STRUCT(node)
{
    list_head_t lh;
    label_t lab;
};

STRUCT(str)
{
    node_p el, th;
};

STRUCT(amp)
{
    number_t re, im;
};

STRUCT(node_str)
{
    node_t n;
    str_t s;
};

STRUCT(node_amp)
{
    node_t n;
    amp_t a;
};

#define NODE(POINTER)       ((node_p)(POINTER))
#define NODE_STR(POINTER)   ((str_p)(NODE(POINTER)+1))
#define NODE_AMP(POINTER)   ((amp_p)(NODE(POINTER)+1))
#define V_NODE(POINTER)     ((node_p*)NODE_STR(POINTER))

void node_str_display(node_p ns);
void node_amp_display(node_p na);

#endif
