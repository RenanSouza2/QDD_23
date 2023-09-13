#ifndef __QDD_DEBUG_H__
#define __QDD_DEBUG_H__

#include "struct.h"
#include "../amp/struct.h"

#ifdef DEBUG
#endif

qdd_p qdd_create(node_p n, list_body_p lb, int max);
qdd_p qdd_create_vector(int qbits, amp_t amps[]);

#endif
