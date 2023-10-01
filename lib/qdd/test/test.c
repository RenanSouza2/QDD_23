#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "../debug.h"
#include "../../amp/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"
#include "../../tree/debug.h"
#include "../../list/list_head/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

#define IDX(L) L.cl][L.lv

qdd_p qdd_create_variadic(int qbits, ...)
{
    node_p *N[3][qbits];
    memset(N, 0, sizeof(N));

    va_list args;
    va_start(args, qbits);

    node_p n;
    int size = va_arg(args, int);

    N[0][0] = malloc(size * sizeof(node_p));
    for(int i=0; i<size; i++)
    {
        amp_t amp = va_arg(args, amp_t);
        N[0][0][i] = n = node_amp_create(&amp);
    }
    list_body_p lb = list_body_create_vector(size, N[0][0]);

    int max = va_arg(args, int);
    for(int i=0; i<max; i++)
    {
        label_t lab = va_arg(args, label_t);
        int size = va_arg(args, int);

        N[IDX(lab)] = malloc(size * sizeof(node_p));
        for(int j=0; j<size; j++)
        {
            N[IDX(lab)][j] = n = node_str_create(&lab);
            
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



void test_create()
{
    printf("\n\t%s\t\t", __func__);
    
    qdd_p q = qdd_create(ND(1), LB(2), 3);
    assert(q->n  == ND(1));
    assert(q->lb == LB(2));
    assert(q->qbits == 3);
    free(q);

    assert(mem_empty());
}

void test_create_variadic()
{
    printf("\n\t%s\t\t", __func__);

    label_t amp, V1, V2;
    amp = LAB(0, 0);
    V1 = LAB(V, 1);
    V2 = LAB(V, 2);

    qdd_p q = qdd_create_variadic(1, 
        2, AMP(0, 0), AMP(0, 1), 
        1,
        V1, 1, amp, 0, amp, 1
    );

    node_p n, n0, n1;
    n  = node_str_create(&V1);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_amp_create(&AMP(0, 1));
    node_connect_both(n, n0, n1);
    
    assert(tree(q->n, n));
    assert(amp_eq(node_amp(q->lb->n), &AMP(0, 0)));
    assert(amp_eq(node_amp(q->lb->lb->n), &AMP(0, 1)));
    qdd_free(q);
    tree_free(n);

    q = qdd_create_variadic(1, 
        1, AMP(0, 0), 
        0
    );
    n = node_amp_create(&AMP(0, 0));
    assert(tree(q->n, n));
    assert(amp_eq(node_amp(q->lb->n), &AMP(0, 0)));
    qdd_free(q);
    tree_free(n);

    q = qdd_create_variadic(2, 
        4, AMP(0, 0), AMP(0, 1), AMP(0, 2), AMP(0, 3),
        2,
        V1, 2, amp, 0, amp, 1, amp, 2, amp, 3,
        V2, 1, V1, 0, V1, 1
    );
    n = node_str_create(&V2);
    for(int i=0; i<2; i++)
    {
        n1 = node_str_create(&V1);
        node_connect(n, n1, i);

        for(int j=0; j<2; j++)
        {
            n0 = node_amp_create(&AMP(0, (i << 1) | j));
            node_connect(n1, n0, j);
        }
    }
    assert(tree(q->n, n));
    qdd_free(q);
    tree_free(n);

    assert(mem_empty());
    
    q = qdd_create_variadic(2, 
        2, AMP(0, 0), AMP(0, 1),
        2,
        V1, 1, amp, 0, amp, 1,
        V2, 1, amp, 0, V1, 0
    );
    
    node_p n2;
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 1));
    n = node_str_create(&V1);
    node_connect_both(n, n1, n2);
    
    n2 = n;
    n = node_str_create(&V2);
    node_connect_both(n, n1, n2);
    
    assert(tree(q->n, n));
    qdd_free(q);
    tree_free(n);

    q = qdd_create_variadic(2,
        3, AMP(0, 0), AMP(0, 1), AMP(0, 2),
        2,
        V1, 2, amp, 0, amp, 1, amp, 0, amp, 2,
        V2, 1, V1, 0, V1, 1
    );

    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_amp_create(&AMP(0, 1));
    n2 = node_str_create(&V1);
    node_connect_both(n2, n0, n1);
    
    node_p n3;
    n1 = node_amp_create(&AMP(0, 2));
    n3 = node_str_create(&V1);
    node_connect_both(n3, n0, n1);

    n = node_str_create(&V2);
    node_connect_both(n, n2, n3);

    assert(tree(q->n, n)); 
    qdd_free(q);
    tree_free(n);

    assert(mem_empty());
}

void test_vector()
{
    printf("\n\t%s\t\t", __func__);

    label_t amp, V1;
    amp = LAB(0, 0);
    V1 = LAB(V, 1);
    
    qdd_p q0 = qdd_create_vector(1, (amp_t[]){{0, 0}, {0, 1}});
    qdd_p q1 = qdd_create_variadic(1,
        2, AMP(0, 0), AMP(0, 1),
        1,
        V1, 1, amp, 0, amp, 1
    );
    assert(tree(q0->n, q1->n));

    qdd_free(q0);
    qdd_free(q1);

    assert(mem_empty());
}



void test_reduce()
{
    printf("\n\t%s\t\t", __func__);

    qdd_p q = qdd_create_vector(2, (amp_t[]){{0, 0}, {0, 1}, {0, 0}, {0, 2}});
    qdd_reduce(q);

    label_t amp, V1, V2;
    amp = LAB(0, 0);
    V1 = LAB(V, 1);
    V2 = LAB(V, 2);

    qdd_p q_exp = qdd_create_variadic(2,
        3, AMP(0, 0), AMP(0, 1), AMP(0, 2),
        2,
        V1, 2, amp, 0, amp, 1, amp, 0, amp, 2,
        V2, 1, V1, 0, V1, 1
    );

    assert(tree(q->n, q_exp->n));
    qdd_free(q);
    qdd_free(q_exp);

    q = qdd_create_vector(1, (amp_t[]){{0, 0}, {0, 0}});
    qdd_reduce(q);
    
    q_exp = qdd_create_variadic(1,
        1, AMP(0, 0),
        0
    );
    assert(tree(q->n, q_exp->n));
    qdd_free(q);
    qdd_free(q_exp);
    
    assert(mem_empty());
}

void test_qdd()
{
    printf("\n%s\t\t", __func__);

    test_create();
    test_create_variadic();
    test_vector();
    test_reduce();

    assert(mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_qdd();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
