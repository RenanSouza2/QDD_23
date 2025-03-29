#ifndef __ND_STRUCT_H__
#define __ND_STRUCT_H__

#include "../list/head/header.h"

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

#define ND(NODE) ((node_p)(NODE))
#define AMP(NODE) (*(amp_p)(ND(NODE)+1))
#define BRANCH(NODE) ((node_p*)(ND(NODE)+1))
#define SIDE(NODE_TOP, NODE_BOT) (BRANCH(NODE_TOP)[0] != NODE_BOT)

#endif