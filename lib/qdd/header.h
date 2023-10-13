#ifndef __QDD_H__
#define __QDD_H__

#include "../../static_utils/struct.h"
#include "../tree/header.h"

PLACEHOLDER(qdd);

qdd_p qdd_create_vector(int qbits, amp_p amps);
qdd_p qdd_create_fn(int qbits, int index, amp_index_f fn);
void qdd_reduce(qdd_p q);
void qdd_free(qdd_p q);

#endif
