#ifndef __LIST_BODY_H__
#define __LIST_BODY_H__

#include "../../../static_utils/struct.h"
#include "../../node/header.h"

PLACEHOLDER(list_body);
PLACEHOLDER(list_head);

#define LB(POINTER)    ((list_body_p)(POINTER))

void list_body_free(list_body_p lb);

void list_body_insert(list_body_p lb, node_p n);
int  list_body_remove(list_body_p lb, node_p n);

#endif
