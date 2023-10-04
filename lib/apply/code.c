#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../qdd/struct.h"

#ifdef DEBUG
#endif

apply_p apply_create(node_p n1, node_p n2)
{
    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t){NULL, n1, n2, NULL, NULL, NULL};
    return a;
}
