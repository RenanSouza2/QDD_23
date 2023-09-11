#ifndef __LIST_HEAD_DEBUG_H__
#define __LIST_HEAD_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void list_head_display(list_head_c const lh);

#endif

#define LH(POINTER) ((list_head_p)(POINTER))

list_head_p list_head_create_cold();
list_head_p list_head_create(node_p const n, list_head_p const lh_next);
void list_head_free(list_head_p lh);

#endif
