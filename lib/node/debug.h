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

#endif
