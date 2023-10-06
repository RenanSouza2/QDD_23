#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../qdd/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

#endif

apply_p apply_create(node_p n1, node_p n2, apply_p a_next)
{
    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t){NULL, n1, n2, a, NULL, NULL};
    return a;
}

apply_p apply_find(apply_p a, node_p n1, node_p n2)
{
    for(; a; a = a->a)
        if(a->n1 == n1 && a->n2 == n2)
            break;

    return a;
}

apply_p apply_insert(apply_p a, node_p n1, node_p n2)
{
    apply_p a = apply_find(a, n1, n2);
    if(a) return a;

    return apply_create(n1, n2, a);
}