#include <stdlib.h>

#include "debug.h"
#include "../node/struct.h"
#include "../list/body/struct.h"
#include "../list/head/struct.h"

#include "../../mods/clu/header.h"
#include "../macros/assert.h"



#ifdef DEBUG

#include "../utils/header.h"
#include "../node/debug.h"
#include "../label/debug.h"
#include "../list/head/debug.h"



void tree_display(node_p node)
{
    CLU_IS_SAFE(node);

    list_head_p lh = tree_enlist(node);
    lh = list_head_invert(lh);
    list_head_display(lh);
}

bool tree_str_rec(node_p node, node_p node_1, node_p node_2)
{
    CLU_IS_SAFE(node);
    CLU_IS_SAFE(node_1);
    CLU_IS_SAFE(node_2);

    if(node_1 == NULL)
    {
        printf("\n\n\tTREE ASSERTION ERRO\t| NODE 1 IS NULL");
        return false;
    }

    assert(node_2);

    if(node && (list_head_first(node_1->lh) != node))
        return true;

    if(!label(node_1->lab, node_2->lab))
    {
        PRINT("\n\tTREE ASSERTION ERROR\t| LABEL MISMATCH ");
        return false;
    }

    if(label_is_amp(&node_2->lab))
    {
        if(!amp_eq(AMP(node_1), AMP(node_2)))
        {
            PRINT("\n\tERROR TREE ASSSERT 2 | AMP MISMATCH");
            return false;
        }
        return true;
    }

    for(int side=0; side<2; side++)
    {
        if(!tree_str_rec(node_1, BRANCH(node_1)[side], BRANCH(node_2)[side]))
        {
            PRINT("\n\tERROR TREE ASSSERT 3 | %s MISMATCH", side ? "THEN" : "ELSE");
            return false;
        }
    }

    return true;
}

bool tree(node_p n1, node_p n2)
{
    return tree_str_rec(NULL, n1, n2);
}

#endif



void tree_free(node_p node)
{
    CLU_IS_SAFE(node);
    assert(node);

    if(node->lh)
        return;

    if(label_is_amp(&node->lab))
    {
        free(node);
        return;
    }

    node_p node_1 = BRANCH(node)[ELSE];
    node_p node_2 = BRANCH(node)[THEN];
    node_disconnect_both(node);
    free(node);

    tree_free(node_1);
    tree_free(node_2);
}

list_head_p tree_enlist_rec(list_head_p lh, node_p node_0, node_p node)
{
    if(node_0 && (list_head_first(node->lh) != node_0))
        return lh;

    lh = list_head_insert(lh, node, ELSE);
    if(label_is_amp(&node->lab))
        return lh;

    lh = tree_enlist_rec(lh, node, BRANCH(node)[ELSE]);
    return tree_enlist_rec(lh, node, BRANCH(node)[THEN]);
}

list_head_p tree_enlist(node_p n)
{
    return tree_enlist_rec(NULL, NULL, n);
}
