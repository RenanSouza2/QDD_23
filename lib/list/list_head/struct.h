#ifndef __LIST_HEAD_STRUCT_H__
#define __LIST_HEAD_STRUCT_H__

#include "header.h"

#include "../list_body/struct.h"

STRUCT(list_head)
{
    list_body_t lb;
    list_head_p lh;
};

#endif