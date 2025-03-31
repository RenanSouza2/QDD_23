#ifndef __TREE_H__
#define __TREE_H__

#include "../list/head/header.h"

void tree_free(node_p n);
list_head_p tree_enlist(node_p n);

node_p tree_reduce(list_body_p lb);

#endif
