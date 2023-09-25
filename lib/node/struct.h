#ifndef __NODE_STRUCT_H__
#define __NODE_STRUCT_H__

#include "header.h"
#include "../list/list_head/struct.h"
#include "../label/struct.h"
#include "../amp/struct.h"

STRUCT(node)
{
    list_head_t lh;
    label_t lab;
};

STRUCT(str)
{
    node_p el, th;
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

#endif