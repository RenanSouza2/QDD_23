#ifndef __NODE_H__
#define __NODE_H__

#include "../../static_utils/struct.h"

PLACEHOLDER(node);

typedef double number_t;

node_p node_str_create(int cl, int lv);
node_p node_amp_create(number_t re, number_t im);

#endif
