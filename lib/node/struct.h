#ifndef __ND_STRUCT_H__
#define __ND_STRUCT_H__

#include "header.h"
#include "../list/list_head/struct.h"
#include "../str/struct.h"
#include "../label/struct.h"
#include "../amp/struct.h"

STRUCT(node)
{
    list_head_p lh[2];
    label_t lab;
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