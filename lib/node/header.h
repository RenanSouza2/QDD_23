#ifndef __ND_H__
#define __ND_H__

#include <stdbool.h>

#include "../../static_utils/struct.h"
#include "../label/header.h"
#include "../amp/header.h"

PLACEHOLDER(node);
PLACEHOLDER(str);

#define ELSE 0
#define THEN 1

label_p node_label(node_p n);

node_p node_str_create(label_p lab);
node_p node_amp_create(amp_p amp);
node_p node_copy(node_p n);
void node_free(node_p n);

bool node_is_amp(node_p n);
str_p node_str(node_p n);
amp_p node_amp(node_p n);
bool node_amp_eq(node_p n1, node_p n2);
bool node_el_eq(node_p n1, node_p n2);
bool node_th_eq(node_p n1, node_p n2);
node_p node_first(node_p n);

void node_connect(node_p n1, node_p n0, int side);
void node_connect_both(node_p n, node_p n_el, node_p n_th);

void node_disconnect(node_p n, int side);
void node_disconnect_both(node_p n);

bool node_merge(node_p n1, node_p n2);

#endif
