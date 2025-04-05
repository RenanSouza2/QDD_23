#ifndef __TREE_H__
#define __TREE_H__

#include "../list/head/header.h"

typedef amp_t (*amp_index_f)(int index);

node_p tree_create_vector(int qbits, amp_p amp);
node_p tree_create_fn(int qbits, int index, amp_index_f fn);
void tree_free(node_p n);

void tree_display(node_p n);

list_head_p tree_enlist(node_p n);
list_body_p tree_enlist_amplitude(node_p n);
node_p tree_copy(node_p n);
list_body_p tree_enlist_amplitude(node_p n);

node_p tree_reduce(list_body_p lb);

#endif
