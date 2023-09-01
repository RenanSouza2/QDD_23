#ifndef __NODE_H__
#define __NODE_H__

#include "../../static_utils/struct.h"
#include "../label/header.h"
#include "../amp/header.h"

PLACEHOLDER(node);

#define ELSE 0
#define THEN 1

label_c node_label(node_c const n);

node_p node_str_create(int const cl, int const lv);
node_p node_amp_create(amp_c const amp);

void node_connect(node_p const n1, node_p const n2, int const side);
void node_connect_both(node_p const n, node_p const n_el, node_p const n_th);

void node_disconnect(node_p const n1, node_p const n2);
void node_disconnect_both(node_p const n);

#endif
