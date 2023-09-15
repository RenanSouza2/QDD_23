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

    *q = (qdd_t){{n, lb}, qbits};
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

void qdd_free(qdd_p q)
{
    tree_free(LB(q)->n);
    list_body_free(LB(q)->lb);
    free(q);
}



void list_body_reduce(list_body_p lb)
{
    for(; lb->lb; lb = lb->lb)
    {
        string_ass
    }
}

void qdd_reduce(qdd_p q)
{
    list_head_p lh = list_head_create(NULL, NULL);

    for(list_body_p lb_1 = LB(q)->lb; lb_1->lb; lb_1 = lb_1->lb)
    {
        node_p n1 = lb_1->n;
        bool insert = false;
        for(list_body_p lb_2 = lb_1     ; lb_2->lb; lb_2 = lb_2->lb)
        {
            list_body_p lb_aux = lb_2->lb;
            node_p n2 = lb_aux->n;
            if(!amp_compare(node_amp(n1), node_amp(n2))) 
                continue;

            insert = true;
            node_merge(n1, n2);
        }
        if(!insert) continue;

        list_head_insert(lh, n1);
    }

    if(LB(lh)->n == NULL)
    {
        free(lh);
        return;
    }

    for(; lh; lh = lh->lh)
    for(list_body_p lb = LB(lh); lb; lb = lb->lb)
    {
        node_p n = lb->n;
        node_p n1;
        while((n1 = LB(n)->n))
        {
            str_p str = node_str(n1);
            if(str->el != str->th) continue;

            node_disconnect_both(n1);
            node_merge(n, n1);
        }

        if(LB(n)->n == NULL) 
        {
            // TODO
        }


    }
}
