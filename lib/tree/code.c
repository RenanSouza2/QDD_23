#include <stdio.h>

#include "debug.h"
#include "../node/struct.h"

#ifdef DEBUG
#endif

list_head_p tree_enlist_rec(list_head_p lh, node_p n)
{
    list_head_insert(lh, n);
    if(node_is_amp(n)) return lh;

    str_p str = node_str(n);
    node_p n1 = str->el;
    if(LB(n1)->n == n) lh = tree_enlist_rec(lh, n1);

    n1 = str->th;
    return (LB(n1)->n == n) ? tree_enlist_rec(lh, n1) : lh;
}

list_head_p tree_enlist(node_p n)
{
    list_head_p lh = list_head_crate(NULL, NULL);
    return tree_enlist_rec(lh, n);
}
