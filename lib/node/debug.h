#ifndef __ND_DEBUG_H__
#define __ND_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void node_branch_display(node_p ns);
void node_amp_display(node_p na);
void node_display(node_p n);

#endif

#define NODE(POINTER) ((node_p)(POINTER))
#define NODE_AMP(POINTER) ((amp_p)(ND(POINTER)+1))
#define NODE_BRANCH(POINTER) ((branch_p)(ND(POINTER)+1))
#define SIDE(NODE, NODE_1) (NODE_BRANCH(ND)->el != ND1)

#endif
