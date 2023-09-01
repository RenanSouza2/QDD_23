#ifndef __LIST_BODY_DEBUG_H__
#define __LIST_BODY_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

void list_body_display(list_body_c const lb);

#endif

#define LB(POINTER)    ((list_body_p)(POINTER))

#endif
