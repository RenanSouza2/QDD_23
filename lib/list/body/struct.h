#ifndef __LIST_BODY_STRUCT_H__
#define __LIST_BODY_STRUCT_H__

#include "header.h"

STRUCT(list_body)
{
    node_p node;
    list_body_p next;
};

#endif