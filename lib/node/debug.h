#ifndef __NODE_DEBUG_H__
#define __NODE_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void node_str_display(node_p ns);
void node_amp_display(node_p na);

#endif

#define NODE(POINTER)       ((node_p)(POINTER))
#define NODE_STR(POINTER)   ((str_p)(NODE(POINTER)+1))
#define NODE_AMP(POINTER)   ((amp_p)(NODE(POINTER)+1))
#define V_STR(POINTER)      ((node_p*)NODE_STR(POINTER))
#define SIDE(NODE,NODE1)    (NODE_STR(NODE)->el != NODE1)

#endif
