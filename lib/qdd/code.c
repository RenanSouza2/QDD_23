#include <stdlib.h>

#include "debug.h"
#include "../label/struct.h"
#include "../node/struct.h"
#include "../tree/header.h"
#include "../list/head/struct.h"
#include "../macros/assert.h"
#include "../../mods/clu/header.h"



#ifdef DEBUG
#endif



qdd_p qdd_create(node_p node, list_body_p lb, int qbits)
{
    CLU_IS_SAFE(node);
    CLU_IS_SAFE(lb);

    qdd_p q = malloc(sizeof(qdd_t));
    assert(q);

    *q = (qdd_t)
    {
        .node = node, 
        .lb = lb,
        qbits = qbits
    };
    return q;
}

qdd_p qdd_create_vector(int qbits, amp_t amp[])
{
    int Q = 1 << qbits;
    node_p N[Q];
    for(int i=0; i<Q; i++)
        N[i] = node_amp_create(amp[i]);    
    list_body_p lb = list_body_create_vec(Q, N);

    for(int i=1; i<=qbits; i++)
    for(list_body_p lb_aux = lb; lb_aux; lb_aux = lb_aux->next)
    { 
        node_p node_1 = lb_aux->node;

        list_body_p lb_tmp = lb_aux->next;
        assert(lb_tmp);
        node_p node_2 = lb_tmp->node;

        node_p node = node_branch_create((label_t){V, i});
        node_connect_both(node, node_1, node_2);

        *lb_aux = (list_body_t){
            .node = node,
            .next = list_body_pop(lb_aux->next)
        };
    }
    assert(lb->next == NULL);
    node_p node = lb->node;
    free(lb);

    lb = list_body_create_vec(Q, N);
    return qdd_create(node, lb, qbits);
}

void qdd_free(qdd_p q)
{
    CLU_IS_SAFE(q);

    tree_free(q->node);
    list_body_free(q->lb);
    free(q);
}


typedef bool (*node_eq_f)(node_p, node_p);

bool list_body_reduce_node_item(list_body_p lb, node_eq_f fn, node_p node_1, bool remove)
{
    CLU_IS_SAFE(lb);
    CLU_IS_SAFE(node_1);

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
    CLU_IS_SAFE(lb);

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
    CLU_IS_SAFE(lb);

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

    list_body_p lb_aux = list_body_reduce_node(lh->lb[ELSE], node_eq_th,false);
    list_head_p lh_res_el = list_head_create_body(lb_aux, ELSE, NULL);

    lb_aux = list_body_reduce_node(lh->lb[THEN], node_eq_el, false);
    list_head_p lh_res_th = list_head_create_body(lb_aux, ELSE, NULL);
    
    return list_head_merge(lh_res_el, lh_res_th);
}

list_head_p node_reduce(node_p node_0)
{
    CLU_IS_SAFE(node_0);

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



void qdd_reduce(qdd_p q)
{
    CLU_IS_SAFE(q);

    list_body_p lb = list_body_reduce_node(q->lb, node_eq_amp, true);
    if(lb == NULL)
        return;

    for(
        list_head_p lh = list_head_create_body(lb, ELSE, NULL);
        lh;
        lh = list_head_remove(lh, lh->lb[ELSE]->node, ELSE)
    ) {
        node_p node = lh->lb[ELSE]->node;
        list_head_p lh_aux = node_reduce(node);
        if(node->lh == NULL)
            q->node = node;

        lh = list_head_merge(lh,lh_aux);
    }
}
