#ifndef __LIST_HEAD_H__
#define __LIST_HEAD_H__

#include "../../../static_utils/struct.h"
#include "../../node/header.h"

PLACEHOLDER(list_head);

#define LH(POINTER)    ((list_head_p)(POINTER))

list_head_p list_head_create(node_p n, list_head_p lh_next);
void list_head_free(list_head_p lh);
void list_head_insert(list_head_p lh, node_p n);
void list_head_remove(list_head_p lh, node_p n);
void list_head_merge(list_head_p lh_1, list_head_p lh_2);

#endif
