#ifndef __ND_STRUCT_H__
#define __ND_STRUCT_H__

#include "header.h"
#include "../list/head/header.h"
#include "../label/struct.h"
#include "../amp/struct.h"

STRUCT(node)
{
    list_head_p lh;
    label_t lab;
};

STRUCT(node_branch)
{
    node_t s;
    node_p branch[2];
};

STRUCT(node_amp)
{
    node_t s;
    amp_t amp;
};

#define NODE(PTR) ((node_p)(PTR))
#define AMP(PTR) ((amp_p)(NODE(PTR)+1))
#define BRANCH(PTR) ((node_p*)(NODE(PTR)+1))
#define SIDE(PTR, PTR_1) (BRANCH(ND)[0] != ND1)

#endif