#ifndef __QDD_DEBUG_H__
#define __QDD_DEBUG_H__

#include "struct.h"
#include "../amp/struct.h"

#ifdef DEBUG

#include <stdbool.h>

qdd_p qdd_create_immed(int qbits, ...);

bool qdd(qdd_p q_1, qdd_p q_2);

#endif

qdd_p qdd_create(node_p n, list_body_p lb, int qbits);
qdd_p qdd_create_vector(int qbits, amp_t amps[]);
void qdd_free(qdd_p q);
void qdd_reduce(qdd_p q);

#endif
