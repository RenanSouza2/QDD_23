#include <stdio.h>
#include <stdbool.h>
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

void test_list_body_create()
{
    printf("\n\ttest list body create\t\t");

    list_body_p lb = list_body_create(NODE(1), LB(2));
    assert(lb->n  == NODE(1));
    assert(lb->lb == LB(2));
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
