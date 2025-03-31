#ifndef __LIST_HEAD_STRUCT_H__
#define __LIST_HEAD_STRUCT_H__

#include "../../label/struct.h"

PLACEHOLDER(list_body);

STRUCT(list_head)
{
    label_t lab;
    list_body_p lb[2];
    list_head_p next;
};

#endif
