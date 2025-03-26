#ifndef __ND_STRUCT_H__
#define __ND_STRUCT_H__

#include "header.h"
#include "../list/list_head/header.h"
#include "../label/struct.h"
#include "../amp/struct.h"

STRUCT(node)
{
    list_head_p lh;
    label_t lab;
};

STRUCT(node_branch)
{
    node_t n;
    node_p node[2];
};

STRUCT(node_amp)
{
    node_t n;
    amp_t amp;
};

#endif