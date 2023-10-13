#ifndef __QDD_DEBUG_H__
#define __QDD_DEBUG_H__

#include "struct.h"
#include "../amp/struct.h"

#ifdef DEBUG

qdd_p qdd_create_variadic(int qbits, ...);

#endif

qdd_p qdd_create(node_p n, list_body_p lb, int qbits);
qdd_p qdd_encapsulate_tree(int qbits, node_p n);

#endif
