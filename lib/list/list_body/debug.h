#ifndef __LIST_BODY_DEBUG_H__
#define __LIST_BODY_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

#include <stdarg.h>

void list_body_display(list_body_p lb);
bool list_body_vector_vargs(list_body_p lb, int tot_b, va_list args);
bool list_body_vector(list_body_p lb, int tot_b, ...);

#endif

#define LB(POINTER)    ((list_body_p)(POINTER))

#endif
