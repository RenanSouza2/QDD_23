#ifndef __LABEL_DEBUG_H__
#define __LABEL_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG

#define LAB(CL, LV) (label_t){CL, LV}

bool label(label_t lab_1, label_t lab_2);

#endif

#endif
