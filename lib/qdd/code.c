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


typedef bool (*node_eq_f)(node_p, node_p);

list_head_p list_body_amp_reduce(list_body_p lb, node_eq_f fn)
{
    list_head_p lh = list_head_create(NULL, NULL);
    for(; lb->lb; lb = lb->lb)
    {
        node_p n1 = lb->n;
        bool insert = false;
        for(list_body_p lb_c = lb; lb_c->lb; )
        {
            list_body_p lb_aux = lb_c->lb;
            node_p n2 = lb_aux->n;
            if(!fn(n1, n2)) 
            {
                lb_c = lb_aux;
                continue;
            }

            insert = true;
            node_merge(n1, n2);
            free(lb_aux);
        }
        
        if(insert)
            list_head_insert(lh, n1);
    }
    return lh;
}

void list_body_str_reduce(list_body_p lb, node_p n)
{
    while(lb->lb)
    {
        node_p n1 = lb->lb->n;
        str_p str = node_str(n1);
        if(str->el != str->th)
        {
            lb = lb->lb;
            break;
        }

        node_disconnect_both(n1);
        node_merge(n, n1);
    }
}

void qdd_reduce(qdd_p q)
{
    list_head_p lh = list_body_amp_reduce(LB(q)->lb);

    for(node_p n = LB(lh)->n; n; n = LB(lh)->n)
    {
        // first position
        for(node_p n1 = LB(n)->n; n1; n1 = LB(n)->n)
        {
            str_p str = node_str(n1);
            if(str->el != str->th)
                break;

            node_disconnect_both(n1);
            node_merge(n, n1);
        }

        // early scape
        if(LB(n)->n == NULL)
        {
            LB(q)->n = n;
            free(lh);
            return;
        }

        // first row
        list_body_str_reduce(LB(n), n);

        // other rows
        for(list_head_p lh = LH(n); lh->lh; )
        {
            //first
            for(node_p n1 = LB(lh->lh)->n; n1; n1 = LB(lh->lh)->n)
            {
                str_p str = node_str(n1);
                if(str->el != str->th)
                    break;

                node_disconnect_both(n1);
                node_merge(n, n1);
            }

            lh = lh->lh;
            list_body_str_reduce(LB(lh), n);
        }

        // rule 2
        for(list_head_p lh_1 = LH(n); lh_1->lh; )
        for(list_head_p lh_1)

        list_head_remove(lh, n);
    }
}
