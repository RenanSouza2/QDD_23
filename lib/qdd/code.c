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
    CLU_HANDLER_VALIDATE(node);
    CLU_HANDLER_VALIDATE(lb);

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
    CLU_HANDLER_VALIDATE(q);

    tree_free(q->node);
    list_body_free(q->lb);
    free(q);
}



void qdd_reduce(qdd_p q)
{
    CLU_HANDLER_VALIDATE(q);

    node_p node = tree_reduce(q->lb);
    q->node = node ? node : q->node; 
}
