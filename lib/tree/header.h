#ifndef __TREE_H__
#define __TREE_H__

#include "../macros/struct.h"
#include "../list/head/header.h"
#include "../node/header.h"

void tree_free(node_p n);
list_head_p tree_enlist(node_p n);

#endif
