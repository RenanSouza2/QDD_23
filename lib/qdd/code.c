#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../label/struct.h"
#include "../node/struct.h"
#include "../tree/header.h"
#include "../list/list_head/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

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
    list_body_p lb_res = NULL;
    list_body_p lb = NULL;

    int Q = 1 << qbits;
    for(int i=Q-1; i>=0; i--)
    {
        node_p n = node_amp_create(&amp[i]);
        lb = list_body_create(n, lb);
        lb_res = list_body_create(n, lb_res);
    }

    for(int i=1; i<=qbits; i++)
    for(list_body_p lb_aux = lb; lb_aux; lb_aux = lb_aux->lb)
    {
        node_p n1 = lb_aux->n;

        list_body_p lb_tmp = lb_aux->lb;
        assert(lb_tmp);
        node_p n2 = lb_tmp->n;

        node_p n = node_str_create(&(label_t){V, i});
        node_connect_both(n, n1, n2);
        lb_aux->n = n;
        lb_aux->lb = lb_tmp->lb;
        free(lb_tmp);
    }
    assert(lb->lb == NULL);
    node_p n = lb->n;
    free(lb);

    return qdd_create(n, lb_res, qbits);
}

void qdd_free(qdd_p q)
{
    tree_free(LB(q)->n);
    list_body_free(LB(q)->lb);
    free(q);
}



typedef bool (*node_eq_f)(node_p, node_p);

list_head_p list_body_reduce_equivalence(list_body_p lb, node_eq_f fn)
{
    if(lb == NULL) return NULL;

    list_head_p lh = NULL;
    for(list_body_p lb_1 = lb; lb_1->lb; lb_1 = lb_1->lb)
    {
        bool insert = false;
        node_p n1 = lb_1->n;
        for(list_body_p lb_2 = lb_1; lb_2->lb; )
        {
            list_body_p lb_aux = lb_2->lb;
            node_p n2 = lb_aux->n;
            if(!fn(n1, n2)) 
            {
                lb_2 = lb_aux;
                continue;
            }

            insert = true;
            node_merge(n1, n2);
            lb_2->lb = list_body_pop(lb_2->lb);
        }
        
        if(insert)
            lh = list_head_insert(lh, n1, ELSE);
    }
    return lh;
}

list_head_p list_head_reduce_redundance(list_head_p lh, node_p n0)
{
    while(lh)
    {
        node_p n1 = lh->lb[ELSE]->n;
        str_p str = node_str(n1);
        if(str->el != str->th) break;

        node_disconnect(n1, THEN);
        node_merge(n0, n1);
        lh = list_head_remove(lh, n1, ELSE);
        free(n1);
    }

    if(lh == NULL) return NULL;

    for(list_body_p lb = lh->lb[ELSE]; lb->lb;)
    {
        node_p n1 = lb->lb->n;
        str_p str = node_str(n1);
        if(str->el != str->th)
        {
            lb = lb->lb;
            continue;
        }

        node_disconnect(n1, THEN);
        node_merge(n0, n1);
        lb->lb = list_body_pop(lb->lb);
        free(n1);
    }

    lh->lh = list_head_reduce_redundance(lh->lh, n0);
    return lh;
}

void qdd_reduce(qdd_p q)
{
    list_head_p lh_0 = list_body_reduce_equivalence(q->lb, node_amp_eq);
    while(lh_0)
    {
        node_p n0 = lh_0->lb[ELSE]->n;
        n0->lh = list_head_reduce_redundance(n0->lh, n0);
        if(n0->lh == NULL)
        {
            q->n = n0;
            free(lh_0);
            return;
        }

        node_eq_f fn[] = {node_th_eq, node_el_eq};
        for(list_head_p lh = n0->lh; lh; lh = lh->lh)
        for(int side = 0; side < 2; side ++)
        {
            list_head_p lh_aux = list_body_reduce_equivalence(LB(lh), fn[side]);
            lh_0 = list_head_merge(lh_0, lh_aux);
        }

        lh_0 = list_head_remove(lh_0, n0, ELSE);
    }
}
