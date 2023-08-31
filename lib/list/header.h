#ifndef __LIST_H__
#define __LIST_H__

#include "../../static_utils/struct.h"
#include "../node/header.h"

STRUCT(list_body)
{
    node_p n;
    list_body_p lb;
};

STRUCT(list_head)
{
    list_body_t lb;
    list_head_p lh;
};

void list_body_insert(list_body_p lb, node_p n);
int  list_body_remove(list_body_p lb, node_p n);

void list_head_insert(list_head_p lh, node_p n);
void list_head_remove(list_head_p lh, node_p n);

#endif
