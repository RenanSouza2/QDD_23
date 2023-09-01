#ifndef __LIST_BODY_H__
#define __LIST_BODY_H__

#include <stdbool.h>

#include "../../../static_utils/struct.h"
#include "../../node/header.h"

PLACEHOLDER(list_body);
PLACEHOLDER(list_head);

#define LB(POINTER)    ((list_body_p)(POINTER))

list_body_p list_body_create(node_p const n, list_body_p const lb_next);
void list_body_free(list_body_p lb);

void list_body_insert(list_body_p const lb, node_p const n);
bool list_body_remove(list_body_p lb, node_c const n);

#endif
