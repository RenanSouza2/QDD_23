#ifndef __LABEL_DEBUG_H__
#define __LABEL_DEBUG_H__

#include "header.h"
#include "struct.h"

#include <stdbool.h>

#ifdef DEBUG

#define LAB(CL, LV) (label_t){CL, LV}

void label_display(label_t lab);

bool label(label_t lab_1, label_t lab_2);

#endif

#endif
