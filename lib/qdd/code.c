#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "debug.h"
#include "../label/struct.h"
#include "../node/struct.h"
#include "../tree/header.h"
#include "../apply/struct.h"
#include "../list/list_head/struct.h"

#ifdef DEBUG

#include <stdarg.h>

#include "../../static_utils/mem_report/bin/header.h"
#include "../tree/debug.h"

qdd_p qdd_create_variadic(int qbits, ...)
{
    va_list args;
    va_start(args, qbits);
    node_p n = tree_create_variadic(qbits, args);
    return qdd_encapsulate_tree(qbits, n);
}

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
    tree_free(q->n);
    list_body_free(q->lb);
    free(q);
}


qdd_p qdd_encapsulate_tree(int qbits, node_p n)
{
    list_body_p lb = tree_enlist_amplitude(n);
    return qdd_create(n, lb, qbits);
}


void qdd_reduce(qdd_p q)
{
    list_body_p lb_aux = list_body_reduce_2(q->lb, node_amp_eq);
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
            continue;
        }

        list_head_p lh_aux = list_head_reduce_equivalence(n0->lh);
        list_head_merge(lh_0, lh_aux);
    }
}

void qdd_copy(qdd_p q)
{
}
