#include <stdlib.h>

#include "debug.h"
#include "../str/struct.h"
#include "../node/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"
#include "../list/list_head/debug.h"

void tree_display(node_p n)
{
    list_head_p lh = tree_enlist(n);
    lh = list_head_invert(lh);
    list_head_display(lh);
}

#endif

void tree_free(node_p n)
{
    if(n->lh[ELSE] || n->lh[THEN]) return;

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

list_head_p tree_enlist_rec(list_head_p lh, node_p n0, node_p n)
{
    if(n0 && (node_first(n) != n0)) return lh;

    lh = list_head_insert(lh, n);
    if(node_is_amp(n)) return lh;

    str_p str = node_str(n);
    lh = tree_enlist_rec(lh, n, str->el);
    return tree_enlist_rec(lh, n, str->th);
}

list_head_p tree_enlist(node_p n)
{
    return tree_enlist_rec(NULL, NULL, n);
}
