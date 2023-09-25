#ifndef __ND_DEBUG_H__
#define __ND_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void node_str_display(node_p ns);
void node_amp_display(node_p na);

#endif

#define ND(POINTER)       ((node_p)(POINTER))
#define ND_STR(POINTER)   ((str_p)(ND(POINTER)+1))
#define ND_AMP(POINTER)   ((amp_p)(ND(POINTER)+1))
#define V_STR(POINTER)      ((node_p*)ND_STR(POINTER))
#define SIDE(ND,ND1)    (ND_STR(ND)->el != ND1)

#endif
