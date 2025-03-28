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
    CLU_HANDLER_IS_SAFE(node);

    list_head_p lh = tree_enlist(node);
    lh = list_head_invert(lh);
    list_head_display_full(lh);
}

bool tree_str_rec(node_p node, node_p node_1, node_p node_2)
{
    CLU_HANDLER_IS_SAFE(node);
    CLU_HANDLER_IS_SAFE(node_1);
    CLU_HANDLER_IS_SAFE(node_2);

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
    CLU_HANDLER_IS_SAFE(node);
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




typedef bool (*node_eq_f)(node_p, node_p);

bool list_body_reduce_node_item(list_body_p lb, node_eq_f fn, node_p node_1, bool remove)
{
    CLU_HANDLER_IS_SAFE(lb);
    CLU_HANDLER_IS_SAFE(node_1);

    bool insert = false;
    for(; lb->next; )
    {
        node_p node_2 = lb->next->node;
        if(!fn(node_1, node_2))
        {
            lb = lb->next;
            continue;
        }

        insert = true;
        node_merge(node_1, node_2);

        if(remove)
            lb->next = list_body_pop(lb->next);
    }

    return insert;
}

// returns the list of the nodes reduced
list_body_p list_body_reduce_node(list_body_p lb, node_eq_f fn, bool remove)
{
    CLU_HANDLER_IS_SAFE(lb);

    if(lb == NULL)
        return NULL;

    list_body_p lb_res = NULL;
    for(; lb && lb->next; lb = lb->next)
    {
        node_p node_1 = lb->node;
        if(list_body_reduce_node_item(lb, fn, node_1, remove))
            lb_res = list_body_create(node_1, lb_res);
    }

    return lb_res;
}

void list_body_reduce_path(node_p node_0, list_body_p lb)
{
    CLU_HANDLER_IS_SAFE(lb);

    if(lb == NULL)
        return;

    for(; lb->next; lb = list_body_pop(lb))
    {
        node_p node = lb->next->node;
        if(BRANCH(node)[ELSE] == BRANCH(node)[THEN])
            node_merge(node_0, node);
    }
}

list_head_p list_head_reduce(node_p node_0, list_head_p *lh_root)
{
    if(*lh_root == NULL)
        return NULL;

    list_head_p lh;
    list_body_p lb;
    while(
        (lh = *lh_root) &&
        (lb = lh->lb[ELSE]) &&
        (
            BRANCH(lb->node)[ELSE] ==
            BRANCH(lb->node)[THEN]
        )
    )
        node_merge(node_0, lb->node);

    lh = *lh_root;
    if(lh == NULL)
        return NULL;

    list_body_reduce_path(node_0, lh->lb[ELSE]);

    list_body_p lb_aux = list_body_reduce_node(lh->lb[ELSE], node_eq_th,false);
    list_head_p lh_res_el = list_head_create_body(lb_aux, ELSE, NULL);

    lb_aux = list_body_reduce_node(lh->lb[THEN], node_eq_el, false);
    list_head_p lh_res_th = list_head_create_body(lb_aux, ELSE, NULL);

    return list_head_merge(lh_res_el, lh_res_th);
}

list_head_p node_reduce(node_p node_0)
{
    CLU_HANDLER_IS_SAFE(node_0);

    list_head_p lh_res = list_head_reduce(node_0, &node_0->lh);
    if(node_0->lh == NULL)
        return lh_res;

    for(list_head_p lh = node_0->lh; lh->next; lh = lh->next)
    {
        list_head_p lh_aux = list_head_reduce(node_0, &lh->next);
        lh_res = list_head_merge(lh_res, lh_aux);
    }
    return lh_res;
}

node_p tree_reduce(list_body_p lb)
{
    lb = list_body_reduce_node(lb, node_eq_amp, true);
    for(
        list_head_p lh = list_head_create_body(lb, ELSE, NULL);
        lh;
        lh = list_head_remove(lh, lh->lb[ELSE]->node, ELSE)
    ) {
        node_p node = lh->lb[ELSE]->node;
        list_head_p lh_aux = node_reduce(node);
        if(node->lh == NULL)
            return node;

        lh = list_head_merge(lh,lh_aux);
    }

    return NULL;
}