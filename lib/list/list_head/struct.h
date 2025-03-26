#ifndef __LIST_HEAD_STRUCT_H__
#define __LIST_HEAD_STRUCT_H__

#include "header.h"

#include "../list_body/header.h"
#include "../../label/struct.h"

STRUCT(list_head)
{
    label_t lab;
    list_body_p lb[2];
    list_head_p lh;
};

#endif