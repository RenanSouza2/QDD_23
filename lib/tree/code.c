#include <stdlib.h>

#include "debug.h"
#include "../../mods/clu/header.h"

#include "../label/header.h"
#include "../node/struct.h"
#include "../macros/assert.h"
#include "../list/body/struct.h"
#include "../list/head/struct.h"



#ifdef DEBUG

#include "../amp/debug.h"
#include "../label/debug.h"
#include "../list/head/debug.h"
#include "../utils/debug.h"



void tree_display(node_p node)
{
    CLU_HANDLER_VALIDATE(node);

    list_head_p lh = tree_enlist(node);
    list_head_display_full(lh);
}



bool tree_rec(node_p node, node_p node_1, node_p node_2)
{
    CLU_HANDLER_VALIDATE(node);
    CLU_HANDLER_VALIDATE(node_1);
    CLU_HANDLER_VALIDATE(node_2);

    if(node_1 == NULL)
    {
        printf("\n\n\tTREE ASSERT ERRO\t| NODE 1 IS NULL");
        return false;
    }

    assert(node_2);

    if(list_head_first(node_1->lh) != node)
    {
        if(!label(node_1->lab, node_2->lab))
        {
            PRINT("\n\tTREE ASSERT ERROR\t| LABEL MISMATCH ");
            return false;
        }

        if(label_is_amp(&node_1->lab))
        {
            if(!amplitude(AMP(node_1), AMP(node_2)))
            {
                PRINT("\n\tTREE ASSERT ERROR\t| AMP MISMATCH");
                return false;
            }

            return true;
        }

        for(int side=0; side<2; side++)
        {
            if(!tree_rec(node_1, BRANCH(node_1)[side], BRANCH(node_2)[side]))
            {
                PRINT("\n\tTREE ASSERT ERROR\t| %s MISMATCH", side ? "THEN" : "ELSE");
                return false;
            }
        }
    }

    return true;
}

bool tree(node_p n1, node_p n2)
{
    return tree_rec(NULL, n1, n2);
}

#endif



void tree_free(node_p node)
{
    CLU_HANDLER_VALIDATE(node);
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
    if(list_head_first(node->lh) != node_0)
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



bool list_body_reduce_repeated_item(list_body_p lb, node_eq_f fn, node_p node_1, bool remove)
{
    CLU_HANDLER_VALIDATE(lb);
    CLU_HANDLER_VALIDATE(node_1);

    bool insert = false;
    while(lb->next)
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
list_body_p list_body_reduce_repeated(list_body_p lb, node_eq_f fn, bool remove)
{
    CLU_HANDLER_VALIDATE(lb);

    if(lb == NULL)
        return NULL;

    list_body_p lb_res = NULL;
    for(; lb; lb = lb->next)
    {
        node_p node_1 = lb->node;
        if(list_body_reduce_repeated_item(lb, fn, node_1, remove))
            lb_res = list_body_create(node_1, lb_res);
    }

    return lb_res;
}

list_head_p list_head_reduce_repeated(list_head_p lh)
{
    CLU_HANDLER_VALIDATE(lh);

    list_body_p lb;
    lb = list_body_reduce_repeated(lh->lb[ELSE], node_eq_th, false);
    list_head_p lh_res_el = list_head_create_body(lb, ELSE, NULL);

    lb = list_body_reduce_repeated(lh->lb[THEN], node_eq_el, false);
    list_head_p lh_res_th = list_head_create_body(lb, ELSE, NULL);

    return list_head_merge(lh_res_el, lh_res_th);
}



void list_body_reduce_useless(node_p node_0, list_body_p lb)
{
    CLU_HANDLER_VALIDATE(node_0);
    CLU_HANDLER_VALIDATE(lb);

    if(lb == NULL)
        return;

    for(; lb->next; )
    {
        node_p node = lb->next->node;
        if(BRANCH(node)[ELSE] == BRANCH(node)[THEN])
            node_merge(node_0, node);
        else
            lb = lb->next;
    }
}

bool list_head_reduce_useless(node_p node_0, list_head_p *lh_root)
{
    CLU_HANDLER_VALIDATE(node_0);
    CLU_HANDLER_VALIDATE(*lh_root);

    if(*lh_root == NULL)
        return NULL;

    list_head_p lh;
    list_body_p lb;
    while(
        (lh = *lh_root) &&
        (lb = lh->lb[ELSE])
    )
    {
        node_p node = lb->node;
        if(BRANCH(node)[ELSE] != BRANCH(node)[THEN])
            break;

        node_merge(node_0, node);
    }

    if(lh == NULL)
        return false;

    list_body_reduce_useless(node_0, lb);
    return true;
}



list_head_p list_head_reduce(node_p node_0, list_head_p *lh_root)
{
    CLU_HANDLER_VALIDATE(node_0);
    CLU_HANDLER_VALIDATE(*lh_root);

    if(list_head_reduce_useless(node_0, lh_root))
        return NULL;

    return list_head_reduce_repeated(*lh_root);
}

list_head_p node_reduce(node_p node_0)
{
    CLU_HANDLER_VALIDATE(node_0);

    list_head_p lh_res = NULL;
    for(list_head_p *lh_root = &node_0->lh; *lh_root; lh_root = &(*lh_root)->next)
    {
        list_head_p lh = list_head_reduce(node_0, lh_root);
        lh_res = list_head_merge(lh_res, lh);
    }
    return lh_res;
}

node_p list_head_pop_node(list_head_p *lh_root)
{
    CLU_HANDLER_VALIDATE(*lh_root);

    list_head_p lh = *lh_root;
    if(lh_root == NULL)
        return NULL;

    list_body_p lb = lh->lb[ELSE];
    node_p node = lb->node;

    lh->lb[ELSE] = lb = list_body_pop(lb);
    if(lb == NULL)
        *lh_root = list_head_pop(lh);

    return node;
}

node_p tree_reduce(list_body_p lb)
{
    lb = list_body_reduce_repeated(lb, node_eq_amp, true);
    list_head_p lh = list_head_create_body(lb, ELSE, NULL);
    for(
        node_p node = list_head_pop_node(&lh);
        node;
        list_head_pop_node(&lh)
    ) {
        list_head_p lh_aux = node_reduce(node);
        if(node->lh == NULL)
            return node;

        lh = list_head_merge(lh, lh_aux);
    }

    return NULL;
}
