#ifndef __LIST_HEAD_STRUCT_H__
#define __LIST_HEAD_STRUCT_H__

#include "header.h"

#include "../list_body/header.h"

STRUCT(list_head)
{
    list_body_p lb;
    list_head_p lh;
};

#endif