#include <stdlib.h>

#include "debug.h"
#include "../list/body/header.h"
#include "../macros/assert.h"
#include "../node/header.h"
#include "../tree/header.h"
#include "../../mods/clu/header.h"



#ifdef DEBUG

#include <stdarg.h>
#include <memory.h>

#include "../amp/debug.h"
#include "../node/debug.h"
#include "../tree/debug.h"
#include "../utils/debug.h"



#define IDX(L) L.cl][L.lv

qdd_p qdd_create_immed(int qbits, ...)
{
    node_p *N[3][qbits];
    memset(N, 0, sizeof(N));

    va_list args;
    va_start(args, qbits);

    node_p n = NULL;
    int size = va_arg(args, int);

    N[0][0] = malloc(size * sizeof(node_p));
    for(int i=0; i<size; i++)
    {
        amp_t amp = va_arg(args, amp_t);
        N[0][0][i] = n = node_amp_create(amp);
    }
    list_body_p lb = list_body_create_vec(size, N[0][0]);

    int max = va_arg(args, int);
    for(int i=0; i<max; i++)
    {
        label_t lab = va_arg(args, label_t);
        int size = va_arg(args, int);

        N[IDX(lab)] = malloc(size * sizeof(node_p));
        for(int j=0; j<size; j++)
        {
            N[IDX(lab)][j] = n = node_branch_create(lab);

            for(int side=0; side<2; side++)
            {
                label_t lab_0 = va_arg(args, label_t);
                assert(N[IDX(lab_0)]);

                int index = va_arg(args, int);
                node_connect(n, N[IDX(lab_0)][index], side);
            }
        }
    }

    for(int i=0; i<qbits; i++)
    for(int j=0; j<3; j++)
    if(N[j][i]) free(N[j][i]);

    return qdd_create(n, lb, qbits);
}
    


bool qdd_inner(qdd_p q_1, qdd_p q_2)
{
    CLU_HANDLER_VALIDATE(q_1);

    if(!int_str(q_1->qbits, q_2->qbits))
    {
        printf("\n\tQDD ASSERT ERROR\t| MISMATCH QBITS");
        return false;
    }

    list_body_p lb_1 = q_1->lb;
    list_body_p lb_2 = q_2->lb;
    for(int i=0; lb_1 && lb_2; i++)
    {
        CLU_HANDLER_VALIDATE(lb_1);

        if(!amplitude(AMP(lb_1->node), AMP(lb_2->node)))
        {
            printf("\n\tQDD ASSERT ERROR\t| AMPLITUDE MISMATCH | %d", i);
            return false;
        }

        lb_1 = lb_1->next;
        lb_2 = lb_2->next;
    }

    if(lb_1)
    {
        printf("\n\tQDD ASSERT ERROR\t| LB AMPLITUDE LONGER");
        return false;
    }

    if(lb_2)
    {
        printf("\n\tQDD ASSERT ERROR\t| LB AMPLITUDE SHORTER");
        return false;
    }

    if(!tree(q_1->node, q_2->node))
    {
        printf("\n\tQDD ASSERT ERROR\t| LB AMPLITUDE SHORTER");
        return false;
    }

    return true;
}

bool qdd(qdd_p q_1, qdd_p q_2)
{
    if(!qdd_inner(q_1, q_2))
    {
        // qdd_display(q_1);
        // qdd_display(q_2);
        return false;
    }

    qdd_free(q_1);
    qdd_free(q_2);
    return true;
}

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
