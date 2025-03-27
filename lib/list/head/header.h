#ifndef __LIST_HEAD_H__
#define __LIST_HEAD_H__

#include "../../macros/struct.h"

#include "../body/header.h"
#include "../../node/header.h"

PLACEHOLDER(list_head);

list_head_p list_head_create_body(list_body_p lb, int side, list_head_p next);
void list_head_free(list_head_p lh);

node_p list_head_first(list_head_p lh);

list_head_p list_head_insert(list_head_p lh, node_p n, int side);
list_head_p list_head_remove(list_head_p lh, node_p n, int side);
list_head_p list_head_merge(list_head_p lh_1, list_head_p lh_2);

#endif
