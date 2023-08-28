#ifndef __LIST_H__
#define __LIST_H__

#include "../../static_utils/struct.h"
#include "../node/header.h"

PLACEHOLDER(list_body);
PLACEHOLDER(list_head);

void list_body_insert(list_body_p lb, node_p n);
int  list_body_remove(list_body_p lb, node_p n);

void list_head_insert(list_head_p lh, node_p n);
void list_head_remove(list_head_p lh, node_p n);

#endif
