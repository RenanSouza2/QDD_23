#ifndef __LABEL_H__
#define __LABEL_H__

#include "../../static_utils/struct.h"

#define R 2
#define V 1
#define C 0

PLACEHOLDER(label);

int label_compare(label_c const lab_1, label_c const lab_2);
int label_is_amp(label_c const lab);

#endif
