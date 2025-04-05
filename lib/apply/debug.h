#ifndef __APPLY_DEBUG_H__
#define __APPLY_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG

#include <stdbool.h>

#define AP(HANDLER) ((apply_p)(HANDLER))

apply_p apply_create_immed(int N, ...);

void apply_display(apply_p a);

bool apply(apply_p a_1, apply_p a_2);

#endif

apply_p apply_create(node_p n1, node_p n2);

apply_p apply_insert(apply_p *a_root, node_p n1, node_p n2);

#endif
