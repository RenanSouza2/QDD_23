#ifndef __LIST_BODY_H__
#define __LIST_BODY_H__

#include <stdbool.h>

#include "../../../static_utils/struct.h"
#include "../../node/header.h"

PLACEHOLDER(list_body);

list_body_p list_body_create(node_p n, list_body_p lb_next);
list_body_p list_body_copy(list_body_p lb);
list_body_p list_body_create_vector(int max, node_p N[]);
list_body_p list_body_pop(list_body_p lb);
void list_body_free(list_body_p lb);

list_body_p list_body_remove(list_body_p lb, node_p n);
list_body_p list_body_merge(list_body_p lb_1, list_body_p lb_2);


typedef bool (*node_eq_f)(node_p, node_p);
list_body_p list_body_reduce_equivalence(list_body_p lb, node_eq_f fn);
bool list_body_reduce_redundance(list_body_p *lb_p);
void list_body_reduce_redundance_rec(list_body_p *lb_p);

#endif
