#ifndef __ND_H__
#define __ND_H__

#include <stdbool.h>

#include "struct.h"

#include "../amp/struct.h"
#include "../label/struct.h"
#include "../macros/struct.h"

PLACEHOLDER(branch);

node_p node_branch_create(label_t lab);
node_p node_amp_create(amp_t amp);
node_p node_copy(node_p n);

bool node_eq_amp(node_p n1, node_p n2);
bool node_eq_el(node_p n1, node_p n2);
bool node_eq_th(node_p n1, node_p n2);

void node_connect(node_p n1, node_p n0, int side);
void node_connect_both(node_p n, node_p n_el, node_p n_th);

void node_disconnect(node_p n, int side);
void node_disconnect_both(node_p n);

void node_merge(node_p node_1, node_p node_2);

#endif
