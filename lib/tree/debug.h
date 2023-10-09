#ifndef __TREE_DEBUG_H__
#define __TREE_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

#include <stdarg.h>

void tree_display(node_p n);
bool tree(node_p n1, node_p n2);
node_p tree_create_variadic(int qbits, va_list args);
node_p tree_create(int qbits, ...);

#endif

#endif
