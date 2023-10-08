#ifndef __TREE_H__
#define __TREE_H__

#include "../../static_utils/struct.h"
#include "../list/list_head/header.h"
#include "../node/header.h"

void tree_free(node_p n);
list_head_p tree_enlist(node_p n);
node_p tree_copy(node_p n);
list_body_p tree_enlist_amplitude(node_p n);

#endif
