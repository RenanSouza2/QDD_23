#ifndef __APPLY_DEBUG_H__
#define __APPLY_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG
#endif

#define AP(POINTER) ((apply_p)(POINTER))

apply_p apply_create(node_p n1, node_p n2);

#endif
