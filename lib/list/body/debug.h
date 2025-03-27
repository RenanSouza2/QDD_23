#ifndef __LIST_BODY_DEBUG_H__
#define __LIST_BODY_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

#include <stdarg.h>

list_body_p list_body_create_immed(int n, ...);

void list_body_display(list_body_p lb);
void list_body_display_full(list_body_p lb);
void list_body_create_vec_immed(list_body_p lb[], int n, ...);

bool list_body_str(list_body_p lb_1, list_body_p lb_2);
bool list_body_variadic(list_body_p lb, int n, va_list *args);
bool list_body_immed(list_body_p lb, int n, ...);

#endif

#define LB(POINTER)    ((list_body_p)(POINTER))

#endif
