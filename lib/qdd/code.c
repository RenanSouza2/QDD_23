#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG
#endif

qdd_p qdd_create(node_p n, list_body_p lb, int max)
{
    qdd_p q = malloc(sizeof(qdd_t));
    assert(q);

    *q = (qdd_t){{n, lb}, max};
    return q;
}
