#ifndef __LIST_HEAD_H__
#define __LIST_HEAD_H__

#include "../../../static_utils/struct.h"
#include "../../node/header.h"

PLACEHOLDER(list_head);

#define LH(POINTER)    ((list_head_p)(POINTER))

void list_head_insert(list_head_p lh, node_p const n);
void list_head_remove(list_head_p lh, node_p const n);

#endif
