#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"



void test_list_body_create()
{
    printf("\n\t\ttest list body create\t\t");

    list_body_p lb = list_body_create(NODE(1), LB(2));
    assert(lb->n  == NODE(1));
    assert(lb->lb == LB(2));
}

void test_list_head_create()
{
    printf("\n\t\ttest list head create\t\t");

    list_head_p lh = list_head_create(NODE(1), LH(2));
    assert(LB(lh)->n  == NODE(1));
    assert(LB(lh)->lb == NULL);
    assert(lh->lh == LH(2));
}

void test_list_create()
{
    printf("\n\ttest list create\t\t");

    test_list_body_create();
    test_list_head_create();
}



void test_list_include()
{
    printf("\n\t\ttest list include\t\t");

    list_head_p lh = list_head_create_empty();
    node_p n = node_str_create(V, 2);
    list_include(lh, n);
    assert(LB(lh)->n == n);
    assert(lh->lh == NULL);

    n = node_str_create(V, 2);
    list_include(lh, n);
    assert(LB(lh)->lb);
    assert(LB(lh)->lb->n == n);

    n = node_str_create(V, 1);
    list_include(lh, n);
    assert(LB(lh)->n == n);
    assert(lh->lh);
    
    n = node_str_create(V, 4);
    list_include(lh, n);
    assert(lh->lh->lh);
    assert(LB(lh->lh->lh)->n == n);

    n = node_str_create(V, 4);
    list_include(lh, n);
    assert(LB(lh->lh->lh)->lb);
    assert(LB(lh->lh->lh)->lb->n == n);

    n = node_str_create(V, 3);
    list_include(lh, n);
    assert(LB(lh->lh->lh)->n == n);
}

void test_list_operations()
{
    printf("\n\ttest list operations\t\t");

    test_list_include();
}



void test_list()
{
    printf("\ntest list library\t\t");

    test_list_create();
    test_list_operations();
}

int main() 
{
    setbuf(stdout, NULL);
    test_list();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
