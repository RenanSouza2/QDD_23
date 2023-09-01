#ifndef __LIST_BODY_DEBUG_H__
#define __LIST_BODY_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void list_body_display(list_body_p lb);

#endif

#define LB(POINTER)    ((list_body_p)(POINTER))

list_body_p list_body_create(node_p n, list_body_p lb_next);

#endif
