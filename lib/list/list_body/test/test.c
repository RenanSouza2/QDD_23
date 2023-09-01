#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "../debug.h"
#include "../../../node/debug.h"



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

    list_body_p lb = NULL;
    for(long i=4; i>=1; i--)
        lb = list_body_create(NODE(i), lb);

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

void test_list_body_operations()
{
    printf("\n\ttest list body operations\t\t");

    test_list_body_insert();
    test_list_body_remove();
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
