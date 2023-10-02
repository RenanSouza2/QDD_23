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

        node_p n = node_str_create(&(label_t){V, i});
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





#include "../list/list_body/debug.h"
#include "../list/list_head/debug.h"
#include "../node/debug.h"

void qdd_reduce(qdd_p q)
{
    list_body_p lb_aux = list_body_reduce_equivalence(q->lb, node_amp_eq, true);
    if(lb_aux == NULL) return;

    for(
        list_head_p lh_0 = list_head_create_body(lb_aux, NULL, ELSE);
        lh_0;
        lh_0 = list_head_remove(lh_0, lh_0->lb[ELSE]->n, ELSE)
    ) {
        node_p n0 = lh_0->lb[ELSE]->n;
        list_head_reduce_redundance(&n0->lh, n0);

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
        {
            list_body_p lb_aux = list_body_reduce_equivalence(lh->lb[side], fn[side], false);
            if(lb_aux == NULL) continue;

            list_head_p lh_aux = list_head_create_body(lb_aux, NULL, ELSE); 
            lh_0 = list_head_merge(lh_0, lh_aux);
        }
    }
}
