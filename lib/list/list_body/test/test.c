#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "../debug.h"
#include "../../list_head/debug.h"
#include "../../../node/debug.h"
#include "../../../../static_utils/mem_report/bin/header.h"


list_body_p list_body_create_test(int init, int max)
{
    list_body_p lb = NULL;
    for(long i=max; i>=init; i--)
        lb = list_body_create(ND(i), lb);

    return lb;
}



void test_list_body_create()
{
    printf("\n\t%s\t\t", __func__);

    list_body_p lb = list_body_create(ND(1), LB(2));
    assert(lb->n  == ND(1));
    assert(lb->lb == LB(2));
    free(lb);

    lb = list_body_create_vector(1, (node_p[]){ND(1)});
    assert(list_body(lb, 1, ND(1)));
    free(lb);

    lb = list_body_create_vector(1, (node_p[]){ND(1), ND(2)});
    assert(list_body(lb, 1, ND(1), ND(2)));
    free(lb);

    assert(mem_empty());
}



void test_list_body_remove()
{
    printf("\n\t\t%s\t\t", __func__);

    list_body_p lb = list_body_create_test(1, 4);
    assert(list_body(lb, 4, ND(1), ND(2), ND(3), ND(4)));

    lb = list_body_remove(lb, ND(4));
    assert(list_body(lb, 3, ND(1), ND(2), ND(3)));
    
    lb = list_body_remove(lb, ND(2));
    assert(list_body(lb, 2, ND(1), ND(3)));
    
    lb = list_body_remove(lb, ND(1));
    assert(list_body(lb, 1, ND(3)));
    
    lb = list_body_remove(lb, ND(3));
    assert(lb == NULL);

    free(lb);
    assert(mem_empty());
}

void test_list_body_merge()
{
    printf("\n\t\t%s\t\t", __func__);

    printf("\n\t\t\t%s 1\t\t", __func__);
    list_body_p lb_1 = list_body_create_test(1, 2);
    list_body_p lb_2 = list_body_create_test(3, 4);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body(lb_1, 4, ND(3), ND(4), ND(1), ND(2)));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 2\t\t", __func__);
    lb_1 = list_body_create_test(1, 2);
    lb_2 = list_body_create(ND(3), NULL);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body(lb_1, 3, ND(3), ND(1), ND(2)));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 3\t\t", __func__);
    lb_1 = list_body_create(ND(1), NULL);
    lb_2 = list_body_create_test(2, 3);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body(lb_1, 3, ND(2), ND(3), ND(1)));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 4\t\t", __func__);
    lb_1 = list_body_create(ND(1), NULL);
    lb_2 = list_body_create(ND(2), NULL);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body(lb_1, 2, ND(2), ND(1)));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 5\t\t", __func__);
    lb_2 = list_body_create(ND(2), NULL);
    lb_1 = list_body_merge(NULL, lb_2);
    assert(list_body(lb_1, 1, ND(2)));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 6\t\t", __func__);
    lb_1 = list_body_create(ND(2), NULL);
    lb_1 = list_body_merge(lb_1, NULL);
    assert(list_body(lb_1, 1, ND(2)));
    list_body_free(lb_1);

    assert(mem_empty());
}

void test_list_body_operations()
{
    printf("\n\t%s\t\t", __func__);

    test_list_body_remove();
    test_list_body_merge();

    assert(mem_empty());
}



void test_list_body_reduce_equivalence()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p n0_0, n0_1, n1, n2;
    n0_0 = node_amp_create(&AMP(0, 0));
    n0_1 = node_amp_create(&AMP(0, 1));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 1));
    node_connect_both(n1, n0_0, n0_1);
    node_connect_both(n2, n0_0, n0_1);
    
    list_body_p lb = list_body_reduce_equivalence(n0_0->lh->lb[ELSE], node_th_eq);
    assert(list_head(n0_0->lh, 1,
        LAB(V, 1), 1, n2, 0
    ));
    assert(list_head(n0_1->lh, 1,
        LAB(V, 1), 0, 1, n2
    ));
    assert(list_body(lb, 1, n2));
    node_free(n0_0);
    node_free(n0_1);
    node_free(n2);
    list_body_free(lb);

    assert(mem_empty());
}

void test_list_body_reduce_redundance()
{
    printf("\n\t\t%s\t\t", __func__);

    printf("\n\t\t\t%s 1\t\t", __func__);
    node_p n0, n1;
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    node_connect(n1, n0, ELSE);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == false);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 1, n1, 0
    ));
    node_free(n0);
    node_free(n1);
    
    printf("\n\t\t\t%s 2\t\t", __func__);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    node_connect(n1, n0, THEN);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == false);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 0, 1, n1
    ));
    node_free(n0);
    node_free(n1);

    printf("\n\t\t\t%s 3\t\t", __func__);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    node_connect_both(n1, n0, n0);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == true);
    assert(n0->lh == NULL);
    node_free(n0);

    printf("\n\t\t\t%s 4\t\t", __func__);
    node_p n2;
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 1));
    node_connect(n2, n0, ELSE);
    node_connect_both(n1, n0, n0);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == true);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 1, n2, 0
    ));
    node_free(n0);
    node_free(n2);

    printf("\n\t\t\t%s 5\t\t", __func__);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 1));
    node_connect(n2, n0, THEN);
    node_connect_both(n1, n0, n0);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == true);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 0, 1, n2
    ));
    node_free(n0);
    node_free(n2);

    printf("\n\t\t\t%s 6\t\t", __func__);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 2));
    node_connect(n2, n1, ELSE);
    node_connect_both(n1, n0, n0);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == true);
    assert(list_head(n0->lh, 1,
        LAB(V, 2), 1, n2, 0
    ));
    node_free(n0);
    node_free(n2);

    printf("\n\t\t\t%s 7\t\t", __func__);
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 2));
    node_connect(n2, n1, THEN);
    node_connect_both(n1, n0, n0);
    assert(list_body_reduce_redundance(&n0->lh->lb[ELSE], n0) == true);
    assert(list_head(n0->lh, 1,
        LAB(V, 2), 0, 1, n2
    ));
    node_free(n0);
    node_free(n2);

    assert(mem_empty());
}

void test_list_body_reduce_redundance_rec()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p n0, n1;
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));

    node_p n2;
    n2 = node_str_create(&LAB(V, 1));
    node_connect_both(n2, n0, n0);
    node_connect(n1, n0, ELSE);
    list_body_reduce_redundance_rec(&n0->lh->lb[ELSE], n0);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 1, n1, 0
    ));
    node_free(n0);
    node_free(n1);

    node_p n3;
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_str_create(&LAB(V, 1));
    n2 = node_str_create(&LAB(V, 1));
    n3 = node_str_create(&LAB(V, 1));
    node_connect(n3, n0, ELSE);
    node_connect_both(n2, n0, n0);
    node_connect(n1, n0, ELSE);
    list_body_reduce_redundance_rec(&n0->lh->lb[ELSE], n0);
    assert(list_head(n0->lh, 1,
        LAB(V, 1), 2, n1, n3, 0
    ));
    node_free(n0);
    node_free(n1);
    node_free(n3);

    assert(mem_empty());
}

void test_list_body_reduce()
{
    printf("\n\t%s\t\t", __func__);

    test_list_body_reduce_equivalence();
    test_list_body_reduce_redundance();
    test_list_body_reduce_redundance_rec();

    assert(mem_empty());
}



void test_list_body()
{
    printf("\n%s\t\t", __func__);

    test_list_body_create();
    test_list_body_operations();
    test_list_body_reduce();

    assert(mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_body();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
