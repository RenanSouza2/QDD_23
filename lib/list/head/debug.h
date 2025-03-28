#ifndef __LIST_HEAD_DEBUG_H__
#define __LIST_HEAD_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

#define LH(HANDLER) ((list_head_p)(HANDLER))

list_head_p list_head_create_immed(int n, ...);
void list_head_create_vec_immed(list_head_p lh[], int n, ...);

void list_head_display(list_head_p lh);
void list_head_display_full(list_head_p lh);

list_head_p list_head_invert(list_head_p lh);

bool list_head(list_head_p lh_1, list_head_p lh_2);
bool list_head_immed(list_head_p lh, int n, ...);

#endif

list_head_p list_head_create(node_p node, int side, list_head_p next);

bool list_head_occupied(list_head_p lh);

#endif
