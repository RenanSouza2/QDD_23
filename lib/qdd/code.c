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
#include "../label/debug.h"
#include "../list/body/debug.h"
#include "../list/head/debug.h"
#include "../node/debug.h"
#include "../tree/debug.h"
#include "../utils/debug.h"



#define IDX(L) L.lv][L.cl

qdd_p qdd_create_variadic_qbits(int qbits, va_list args)
{
    int max = qbits + 1;
    node_p *N[max][3];
    memset(N, 0, sizeof(N));

    int size_amp = va_arg(args, int);
    assert(size_amp);
    node_p *N_lab = N[0][0] = malloc(size_amp * sizeof(node_p));
    assert(N_lab);

    node_p node = NULL;
    for(int i=0; i<size_amp; i++)
    {
        amp_t amp = va_arg(args, amp_t);
        N_lab[i] = node = node_amp_create(amp);
    }
    list_body_p lb = list_body_create_vec(size_amp, N_lab);

    int n = va_arg(args, int);
    for(int i=0; i<n; i++)
    {
        label_t lab = va_arg(args, label_t);
        int size = va_arg(args, int);
        assert(size);

        N_lab = N[IDX(lab)] = malloc(size * sizeof(node_p));
        assert(N_lab);

        for(int j=0; j<size; j++)
        {
            N_lab[j] = node = node_branch_create(lab);

            for(int side=0; side<2; side++)
            {
                label_t lab_0 = va_arg(args, label_t);
                assert(N[IDX(lab_0)]);

                int index = va_arg(args, int);
                node_connect(node, N[IDX(lab_0)][index], side);
            }
        }
    }

    for(int i=0; i<max; i++)
    for(int j=0; j<3; j++)
    {
        N_lab = N[i][j];
        if(N_lab)
            free(N_lab);
    }

    return qdd_create(node, lb, qbits);
}

qdd_p qdd_create_variadic(va_list args)
{
    int qbits = va_arg(args, int);
    return qdd_create_variadic_qbits(qbits, args);
}

qdd_p qdd_create_immed(int qbits, ...)
{
    va_list args;
    va_start(args, qbits);
    return qdd_create_variadic_qbits(qbits, args);
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

        if(!label_is_amp(&lb_1->node->lab))
        {
            printf("\n\n\tQDD ASSERT ERROR\t| NODE IM AMPLITUDE LIST IS NOT AMP | %d", i);
            return false;
        }

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
        printf("\n\n\tQDD ASSERT ERROR\t| LB AMPLITUDE LONGER");
        return false;
    }

    if(lb_2)
    {
        printf("\n\n\tQDD ASSERT ERROR\t| LB AMPLITUDE SHORTER");
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
        printf("\n");
        printf("\n-----------------------------------------------");
        printf("\nQDD 1");
        qdd_display(q_1);
        printf("\n-----------------------------------------------");
        printf("\n");
        printf("\n-----------------------------------------------");
        printf("\nQDD 2");
        qdd_display(q_2);
        printf("\n-----------------------------------------------");
        return false;
    }

    qdd_free(q_1);
    qdd_free(q_2);
    return true;
}

bool qdd_immed(qdd_p q, ...)
{
    va_list args;
    va_start(args, q);
    qdd_p q2 = qdd_create_variadic(args);
    return qdd(q, q2);
}

#endif


qdd_p qdd_encapsulate_tree(int qbits, node_p n)
{
    list_body_p lb = tree_enlist_amplitude(n);
    return qdd_create(n, lb, qbits);
}

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
        .qbits = qbits
    };
    return q;
}

qdd_p qdd_create_arr(int qbits, amp_t node_amp[])
{
    int Q = 1 << qbits;
    node_p N[Q];
    for(int i=0; i<Q; i++)
        N[i] = node_amp_create(node_amp[i]);
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

qdd_p qdd_create_fn(int qbits, int index, amp_index_f fn) // TODO test
{
    node_p n = tree_create_fn(qbits, index, fn);
    return qdd_encapsulate_tree(qbits, n);
}

void qdd_free(qdd_p q)
{
    CLU_HANDLER_VALIDATE(q);

    tree_free(q->node);
    list_body_free(q->lb);
    free(q);
}



void qdd_display(qdd_p q)
{
    CLU_HANDLER_VALIDATE(q);

    printf("\nQDD: %p", q);
    printf("\nqbits: %d", q->qbits);

    printf("\namplitudes:");
    list_body_display_short(q->lb);

    list_head_p lh = tree_enlist(q->node);
    list_head_display(lh->next);
    list_head_free(lh);
}



void qdd_reduce(qdd_p q)
{
    CLU_HANDLER_VALIDATE(q);

    node_p node = tree_reduce(q->lb);
    q->node = node ? node : q->node;
}

qdd_p qdd_copy(qdd_p q)
{
    node_p n = tree_copy(q->node);
    return qdd_encapsulate_tree(q->qbits, n);
}
