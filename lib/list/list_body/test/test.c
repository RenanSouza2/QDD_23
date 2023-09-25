#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "../debug.h"
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

    list_body_p lb_1 = list_body_copy(lb);
    assert(lb_1->n  == ND(1));
    assert(lb_1->lb == LB(2));

    free(lb);
    free(lb_1);

    assert(mem_empty());
}



void test_list_body_insert()
{
    printf("\n\t\t%s\t\t", __func__);

    list_body_p lb = list_body_create(NULL, NULL);
    
    list_body_insert(lb, ND(1));
    assert(list_body_vector(lb, 1, (node_p[]){ND(1)}));

    list_body_insert(lb, ND(2));
    assert(list_body_vector(lb, 2, (node_p[]){ND(1), ND(2)}));
    
    list_body_insert(lb, ND(3));
    assert(list_body_vector(lb, 3, (node_p[]){ND(1), ND(3), ND(2)}));

    list_body_free(lb);
    assert(mem_empty());
}

void test_list_body_remove()
{
    printf("\n\t\t%s\t\t", __func__);

    list_body_p lb = list_body_create_test(1, 4);
    assert(list_body_vector(lb, 4, (node_p[]){ND(1), ND(2), ND(3), ND(4)}));

    assert(list_body_remove(lb, ND(4)) == true);
    assert(list_body_vector(lb, 3, (node_p[]){ND(1), ND(2), ND(3)}));
    
    assert(list_body_remove(lb, ND(2)) == true);
    assert(list_body_vector(lb, 2, (node_p[]){ND(1), ND(3)}));
    
    assert(list_body_remove(lb, ND(1)) == true);
    assert(list_body_vector(lb, 1, (node_p[]){ND(3)}));
    
    assert(list_body_remove(lb, ND(3)) == false);
    assert(list_body_vector(lb, 1, (node_p[]){NULL}));

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
    assert(list_body_vector(lb_1, 4, (node_p[]){ND(3), ND(4), ND(1), ND(2)}));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 2\t\t", __func__);
    lb_1 = list_body_create_test(1, 2);
    lb_2 = list_body_create(ND(3), NULL);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body_vector(lb_1, 3, (node_p[]){ND(3), ND(1), ND(2)}));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 3\t\t", __func__);
    lb_1 = list_body_create(ND(1), NULL);
    lb_2 = list_body_create_test(2, 3);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body_vector(lb_1, 3, (node_p[]){ND(2), ND(3), ND(1)}));
    list_body_free(lb_1);

    printf("\n\t\t\t%s 4\t\t", __func__);
    lb_1 = list_body_create(ND(1), NULL);
    lb_2 = list_body_create(ND(2), NULL);
    lb_1 = list_body_merge(lb_1, lb_2);
    assert(list_body_vector(lb_1, 2, (node_p[]){ND(2), ND(1)}));
    list_body_free(lb_1);

    assert(mem_empty());
}

void test_list_body_operations()
{
    printf("\n\t%s\t\t", __func__);

    test_list_body_insert();
    test_list_body_remove();
    test_list_body_merge();

    assert(mem_empty());
}



void test_list_body()
{
    printf("\n%s\t\t", __func__);

    test_list_body_create();
    test_list_body_operations();

    assert(mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_body();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
