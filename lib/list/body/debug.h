#ifndef __LIST_BODY_DEBUG_H__
#define __LIST_BODY_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG

#include <stdarg.h>

list_body_p list_body_create_variadic(va_list *args);
list_body_p list_body_create_immed(int n, ...);
void list_body_create_vec_immed(list_body_p lb[], int n, ...);

bool list_body_inner(list_body_p lb_1, list_body_p lb_2);
bool list_body(list_body_p lb_1, list_body_p lb_2);
bool list_body_variadic(list_body_p lb, int n, va_list *args);
bool list_body_immed(list_body_p lb, int n, ...);

#endif

#define LB(HANDLER)    ((list_body_p)(HANDLER))

#endif
