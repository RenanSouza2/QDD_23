#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG
#endif

node_p node_str_create(int cl, int lv)
{
    node_str_p ns;
    ns = malloc(sizeof(node_str_t));
    assert(ns);


    *ns = (node_str_t){{{{NULL, NULL}, NULL}, {lv, cl}}, {NULL, NULL}};
    return NODE(ns);
}
