#ifndef __LIST_BODY_H__
#define __LIST_BODY_H__

#include "../../node/header.h"

PLACEHOLDER(list_body);

list_body_p list_body_create(node_p n, list_body_p lb_next);
<<<<<<< HEAD:lib/list/list_body/header.h
list_body_p list_body_create_vector(int n, node_p N[]);
=======
list_body_p list_body_copy(list_body_p lb);
list_body_p list_body_create_vec(int max, node_p N[]);
>>>>>>> main:lib/list/body/header.h
list_body_p list_body_pop(list_body_p lb);
void list_body_free(list_body_p lb);

void list_body_display_full(list_body_p lb);

list_body_p list_body_remove(list_body_p lb, node_p n);
list_body_p list_body_merge(list_body_p lb_1, list_body_p lb_2);

<<<<<<< HEAD:lib/list/list_body/header.h

typedef bool (*node_eq_f)(node_p, node_p);
list_body_p list_body_reduce_2(list_body_p lb, node_eq_f fn);
bool list_body_reduce_1(list_body_p *lb_p);
void list_body_reduce_1_list(list_body_p *lb_p);

=======
>>>>>>> main:lib/list/body/header.h
#endif
