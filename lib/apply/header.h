#ifndef __APPLY_H__
#define __APPLY_H__

#include "../macros/struct.h"

PLACEHOLDER(apply);
PLACEHOLDER(node);

apply_p apply_tree_fit(node_p n);
void apply_copy(apply_p a);
node_p apply_tree_build(apply_p a);
void apply_free(apply_p a);

#endif
