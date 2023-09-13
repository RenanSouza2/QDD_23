#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../label/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

#endif

qdd_p qdd_create(node_p n, list_body_p lb, int max)
{
    qdd_p q = malloc(sizeof(qdd_t));
    assert(q);

    *q = (qdd_t){{n, lb}, max};
    return q;
}

qdd_p qdd_create_vector(int qbits, amp_t amp[])
{
    list_body_p lb_res = NULL;
    list_body_p lb = NULL;

    int Q = 1 << qbits;
    for(int i=0; i<Q; i++)
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