#ifndef __TREE_DEBUG_H__
#define __TREE_DEBUG_H__

#include "header.h"

#ifdef DEBUG

void tree_display(node_p n);
bool tree(node_p n1, node_p n2);

#endif

typedef bool (*node_eq_f)(node_p, node_p);

list_body_p list_body_reduce_repeated(list_body_p lb, node_eq_f fn, bool remove);

bool list_head_reduce_useless(node_p node_0, list_head_p *lh_root);

#endif
