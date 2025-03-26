#include <stdlib.h>

#include "debug.h"
#include "../label/struct.h"
#include "../node/struct.h"
#include "../tree/header.h"
#include "../list/list_head/struct.h"
#include "../macros/assert.h"
#include "../../mods/clu/header.h"



#ifdef DEBUG
#endif



qdd_p qdd_create(node_p n, list_body_p lb, int qbits)
{
    qdd_p q = malloc(sizeof(qdd_t));
    assert(q);

    *q = (qdd_t){n, lb, qbits};
    return q;
}

qdd_p qdd_create_vector(int qbits, amp_t amp[])
{
    int Q = 1 << qbits;
    node_p N[Q];
    for(int i=0; i<Q; i++)
        N[i] = node_amp_create(&amp[i]);    
    list_body_p lb = list_body_create_vector(Q, N);

    for(int i=1; i<=qbits; i++)
    for(list_body_p lb_aux = lb; lb_aux; lb_aux = lb_aux->lb)
    { 
        node_p n1 = lb_aux->n;

        list_body_p lb_tmp = lb_aux->lb;
        assert(lb_tmp);
        node_p n2 = lb_tmp->n;

        node_p n = node_branch_create(&(label_t){V, i});
        node_connect_both(n, n1, n2);

        *lb_aux = (list_body_t){n, list_body_pop(lb_aux->lb)};
    }
    assert(lb->lb == NULL);
    node_p n = lb->n;
    free(lb);

    lb = list_body_create_vector(Q, N);
    return qdd_create(n, lb, qbits);
}

void qdd_free(qdd_p q)
{
    tree_free(LB(q)->n);
    list_body_free(LB(q)->lb);
    free(q);
}



bool list_body_reduce_equivalence_item(list_body_p lb, node_eq_f fn, node_p n1)
{
    bool insert = false;
    for(; lb->lb; )
    {
        node_p n2 = lb->lb->n;
        if(!fn(n1, n2)) 
        {
            lb = lb->lb;
            continue;
        }

        insert = true;
        if(!node_merge(n1, n2))
            lb->lb = list_body_pop(lb->lb);
    }

    return insert;
}

// returns the list of the nodes reduced
list_body_p list_body_reduce_node(list_body_p lb, node_eq_f fn)
{
    if(lb == NULL)
        return NULL;

    list_body_p lb_res = NULL;
    for(; lb && lb->lb; lb = lb->lb)
    {
        node_p n1 = lb->n;
        if(list_body_reduce_equivalence_item(lb, fn, n1))
            lb_res = list_body_create(n1, lb_res);
    }

    return lb_res;
}

bool list_body_reduce_path_item(list_body_p *lb_root)
{
    list_body_p lb = *lb_root;
    if(lb == NULL)
        return false;

    node_p n1 = lb->n;
    branch_p branch = node_branch(n1);
    if(branch->el != branch->th)
        return false;

    node_merge(branch->el, n1);
    return true;
}

list_body_p list_body_reduce_path(list_body_p lb)
{
    list_body_t lb_0;
    lb_0.lb = lb;

    for(lb = &lb_0; lb->lb; )
    {
        node_p node = lb->lb->n;
        branch_p branch = node_branch(node);
        if(branch->el != branch->th)
        {
            lb = lb->lb;
            continue;
        }

        
    }

    while(list_body_reduce_path_item(lb_p));

    if(*lb_p == NULL) return;

    list_body_reduce_path(&(*lb_p)->lb);
}

void list_head_reduce_redundance(list_head_p *lh_p)
{
    if(*lh_p == NULL || (*lh_p)->lb[ELSE] == NULL) return;

    while(*lh_p && list_body_reduce_path(&(*lh_p)->lb[ELSE]));

    if(*lh_p == NULL || (*lh_p)->lb[ELSE] == NULL) return;

    list_body_reduce_path(&(*lh_p)->lb[ELSE]->lb);
    list_head_reduce_redundance(&(*lh_p)->lh);
}



void qdd_reduce(qdd_p q)
{
    list_body_p lb_aux = list_body_reduce_node(q->lb, node_amp_eq);
    if(lb_aux == NULL) return;

    for(
        list_head_p lh_0 = list_head_create_body(lb_aux, NULL, ELSE);
        lh_0;
        lh_0 = list_head_remove(lh_0, lh_0->lb[ELSE]->n, ELSE)
    ) {
        node_p n0 = lh_0->lb[ELSE]->n;
        list_head_reduce_redundance(&n0->lh);

        if(n0->lh == NULL)
        {
            q->n = n0;
            free(lh_0->lb[ELSE]);
            free(lh_0);
            return;
        }

        node_eq_f fn[] = {node_th_eq, node_el_eq};
        for(list_head_p lh = n0->lh; lh; lh = lh->lh)
        for(int side = 0; side < 2; side ++)
        if(lh->lb[side])
        {
            list_body_p lb_aux = list_body_reduce_node(lh->lb[side], fn[side]);
            if(lb_aux == NULL) continue;

            list_head_p lh_aux = list_head_create_body(lb_aux, NULL, ELSE); 
            lh_0 = list_head_merge(lh_0, lh_aux);
        }
    }
}
