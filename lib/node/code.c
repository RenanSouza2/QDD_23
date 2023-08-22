#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include <stdio.h>

void node_str_display(node_p ns)
{
    printf("\n");
    printf("\nnode (str) display: %p", ns);
    printf("\nlabel: %d %d", ns->lab.cl, ns->lab.lv);
    printf("\n");
}

#endif

node_p node_str_create(int cl, int lv)
{
    node_str_p ns;
    ns = malloc(sizeof(node_str_t));
    assert(ns);

    *ns = (node_str_t){{{{NULL, NULL}, NULL}, {cl, lv}}, {NULL, NULL}};
    return NODE(ns);
}
