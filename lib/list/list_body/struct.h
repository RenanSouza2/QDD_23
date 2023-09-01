#ifndef __LIST_BODY_STRUCT_H__
#define __LIST_BODY_STRUCT_H__

#include "header.h"

#include "../../node/header.h"

STRUCT(list_body)
{
    node_p n;
    list_body_p lb;
};

#endif