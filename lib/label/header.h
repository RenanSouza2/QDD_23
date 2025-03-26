#ifndef __LABEL_H__
#define __LABEL_H__

#include <stdbool.h>

#include "../macros/struct.h"

#define R 2
#define V 1
#define C 0

PLACEHOLDER(label);

int label_compare(label_p lab_1, label_p lab_2);
bool label_is_amp(label_p lab);

#endif
