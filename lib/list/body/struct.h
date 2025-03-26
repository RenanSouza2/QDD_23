#ifndef __LIST_BODY_STRUCT_H__
#define __LIST_BODY_STRUCT_H__

#include "header.h"

#define LB(POINTER)    ((list_body_p)(POINTER))

STRUCT(list_body)
{
    node_p node;
    list_body_p lb;
};

#endif