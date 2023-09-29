#include <stdlib.h>

#include "debug.h"
#include "../str/struct.h"
#include "../node/struct.h"
#include "../list/list_body/struct.h"
#include "../list/list_head/struct.h"

#ifdef DEBUG

#include "../utils/header.h"
#include "../node/debug.h"
#include "../list/list_head/debug.h"
#include "../../static_utils/mem_report/bin/header.h"

void tree_display(node_p n)
{
    list_head_p lh = tree_enlist(n);
    lh = list_head_invert(lh);
    list_head_display(lh);
}

bool tree_assert_rec(node_p n, node_p n1, node_p n2)
{
    if(n == NULL || list_head_first(n1->lh) != n) return true;

    if(n1 == NULL)
    {
        if(n2)
        {
            PRINT("ERROR TREE ASSSERT 1 | N1 IS NULL N2 IS NOT");
            return false;
        }

        return true;
    }

    if(n2 == NULL)
    {
        PRINT("ERROR TREE ASSSERT 2 | N1 IS NOT NULL N2 IS");
        return false;
    }

    if(label_compare(node_label(n1), node_label(n2)) != 0)
    {
        PRINT("ERROR TREE ASSSERT 2 | LABEL MISMATCH");
        return false;
    }

    if(node_is_amp(n2))
    {
        if(!amp_eq(node_amp(n1), node_amp(n2)))
        {
            PRINT("ERROR TREE ASSSERT 3 | AMP MISMATCH");
            return false;
        }
        return true;
    }

    for(int side=0; side<2; side++)
    {
        if(!tree_assert_rec(n1, V_STR(n1)[side], V_STR(n2)[side]))
        {
            PRINT("ERROR TREE ASSSERT 4 | %s MISMATCH", side ? "THEN" : "ELSE");
            return false;
        }
    }

    return true;
}

bool tree_assert(node_p n1, node_p n2)
{
    return tree_assert_rec(NULL, n1, n2);
}

#endif

void tree_free(node_p n)
{
    if(n->lh) return;

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

    lh = list_head_insert(lh, n, ELSE);
    if(node_is_amp(n)) return lh;

    str_p str = node_str(n);
    lh = tree_enlist_rec(lh, n, str->el);
    return tree_enlist_rec(lh, n, str->th);
}

list_head_p tree_enlist(node_p n)
{
    return tree_enlist_rec(NULL, NULL, n);
}
