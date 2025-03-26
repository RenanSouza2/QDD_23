#ifndef __LIST_HEAD_DEBUG_H__
#define __LIST_HEAD_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void list_head_display_item(list_head_p lh);
void list_head_display(list_head_p lh);

bool list_head(list_head_p lh, int tot_h, ...);

list_head_p list_head_invert(list_head_p lh);

#endif

#define LH(POINTER) ((list_head_p)(POINTER))

list_head_p list_head_create_cold();

#endif
