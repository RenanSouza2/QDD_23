#include <stdio.h>

#include "debug.h"
#include "../node/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

#endif

void tree_free(node_p n)
{
    if(LB(n)->n) return;

    if(node_is_amp(n))
    {
        free(n);
        return;
    }

    str_p str = node_str(n);
    node_p n1 = str->el;
    node_p n2 = str->th;
    node_disconnect_both(n);
    free(n);

    tree_free(n1);
    tree_free(n2);
}

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
    list_head_p lh = list_head_create(NULL, NULL);
    return tree_enlist_rec(lh, n);
}
