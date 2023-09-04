#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "../debug.h"
#include "../../../node/debug.h"




list_body_p list_body_create_test(int init, int max)
{
    list_body_p lb = NULL;
    for(long i=max; i>=init; i--)
        lb = list_body_create(NODE(i), lb);

    return lb;
}

void assert_body_list(list_body_p lb, int n, ...)
{
    va_list ptr;
    va_start(ptr, n);
 
    for (int i = 0; i < n; i++, lb = lb->lb)
    {
        node_p n = va_arg(ptr, node_p);
        assert(lb->n == n);
    }
}



void test_list_body_create()
{
    printf("\n\ttest list body create\t\t");

    list_body_p lb = list_body_create(NODE(1), LB(2));
    assert(lb->n  == NODE(1));
    assert(lb->lb == LB(2));

    list_body_p lb_1 = list_body_copy(lb);
    assert(lb_1->n  == NODE(1));
    assert(lb_1->lb == LB(2));
}



void test_list_body_insert()
{
    printf("\n\t\ttest list body insert\t\t");

    list_body_p lb = list_body_create(NULL, NULL);
    
    list_body_insert(lb, NODE(1));
    assert(lb->n == NODE(1));

    list_body_insert(lb, NODE(2));
    assert(lb->n == NODE(1));
    assert(lb->lb);
    assert(lb->lb->n == NODE(2));
    
    list_body_insert(lb, NODE(3));
    assert(lb->lb->n == NODE(3));
}

void test_list_body_remove()
{
    printf("\n\t\ttest list body remove\t\t");

    list_body_p lb = list_body_create_test(1, 4);

    assert(list_body_remove(lb, NODE(4)) == true);
    assert(lb->lb->lb->lb == NULL);
    
    assert(list_body_remove(lb, NODE(2)) == true);
    assert(lb->lb->n == NODE(3));
    
    assert(list_body_remove(lb, NODE(1)) == true);
    assert(lb->n  == NODE(3));
    assert(lb->lb == NULL);
    
    assert(list_body_remove(lb, NODE(3)) == false);
    assert(lb->n  == NULL);
}

void test_list_body_merge()
{
    printf("\n\t\ttest list body merge\t\t");

    list_body_p lb_1 = list_body_create_test(1, 2);
    list_body_p lb_2 = list_body_create_test(3, 4);
    list_body_merge(lb_1, lb_2);
    assert_body_list(lb_1, 4, NODE(1), NODE(2), NODE(3), NODE(4));

    lb_1 = list_body_create_test(1, 2);
    lb_2 = list_body_create(NODE(3), NULL);
    list_body_merge(lb_1, lb_2);
    assert_body_list(lb_1, 3, NODE(1), NODE(2), NODE(3));

    lb_1 = list_body_create(NODE(1), NULL);
    lb_2 = list_body_create_test(2, 3);
    list_body_merge(lb_1, lb_2);
    assert_body_list(lb_1, 3, NODE(1), NODE(2), NODE(3));

    lb_1 = list_body_create(NODE(1), NULL);
    lb_2 = list_body_create(NODE(2), NULL);
    list_body_merge(lb_1, lb_2);
    assert_body_list(lb_1, 2, NODE(1), NODE(2));
}

void test_list_body_operations()
{
    printf("\n\ttest list body operations\t\t");

    test_list_body_insert();
    test_list_body_remove();
    test_list_body_merge();
}



void test_list_body()
{
    printf("\ntest list body library\t\t");

    test_list_body_create();
    test_list_body_operations();
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_body();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
