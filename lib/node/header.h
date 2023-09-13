#ifndef __NODE_H__
#define __NODE_H__

#include "../../static_utils/struct.h"
#include "../label/header.h"
#include "../amp/header.h"

PLACEHOLDER(node);

#define ELSE 0
#define THEN 1

label_p node_label(node_p n);

node_p node_str_create(label_p lab);
node_p node_amp_create(amp_p amp);
void node_free(node_p n);

void node_connect(node_p n1, node_p n2, int side);
void node_connect_both(node_p n, node_p n_el, node_p n_th);

void node_disconnect(node_p n1, node_p n2);
void node_disconnect_both(node_p n);

#endif
