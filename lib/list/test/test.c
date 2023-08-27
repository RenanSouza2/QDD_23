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



void test_list_head_insert()
{
    printf("\n\t\ttest list head insert\t\t");

    list_head_p lh = list_head_create(NULL, NULL);
    node_p n = node_str_create(V, 2);
    list_head_insert(lh, n);
    assert(LB(lh)->n == n);
    assert(lh->lh == NULL);

    n = node_str_create(V, 2);
    list_head_insert(lh, n);
    assert(LB(lh)->lb);
    assert(LB(lh)->lb->n == n);

    n = node_str_create(V, 1);
    list_head_insert(lh, n);
    assert(LB(lh)->n == n);
    assert(lh->lh);
    
    n = node_str_create(V, 4);
    list_head_insert(lh, n);
    assert(lh->lh->lh);
    assert(LB(lh->lh->lh)->n == n);

    n = node_str_create(V, 4);
    list_head_insert(lh, n);
    assert(LB(lh->lh->lh)->lb);
    assert(LB(lh->lh->lh)->lb->n == n);

    n = node_str_create(V, 3);
    list_head_insert(lh, n);
    assert(LB(lh->lh->lh)->n == n);
}



void test_list_body_remove()
{
    printf("\n\t\t\ttest list body remove\t\t");

    list_body_p lb = NULL;
    for(long i=3; i>=0; i--)
        lb = list_body_create(NODE(i), lb);

    list_body_remove(lb, NODE(3));
    assert(lb->lb->lb->lb == NULL);
    
    list_body_remove(lb, NODE(1));
    assert(lb->lb->n == NODE(2));
    
    list_body_remove(lb, NODE(2));
    assert(lb->lb == NULL);
}

void test_list_head_remove()
{
    printf("\n\t\t\ttest list head remove\t\t");

    node_p n[] = {
        node_str_create(V, 1), // 0
        node_str_create(V, 1), // 2
        node_str_create(V, 1), // 1

        node_str_create(V, 2),
        node_str_create(V, 2),

        node_str_create(V, 3),
        node_str_create(V, 3),

        node_str_create(V, 4),
        node_str_create(V, 4),
    };

    list_head_p lh = list_head_create(NULL, NULL);
    for(int i=0; i<6; i++)
        list_head_insert(lh, n[i]);

    list_head_remove(lh, n[1], LB(lh));
}

void test_list_remove()
{
    printf("\n\t\ttest list remove\t\t");

    test_list_body_remove();
    test_list_head_remove();
}

void test_list_operations()
{
    printf("\n\ttest list operations\t\t");

    test_list_head_insert();
    test_list_remove();
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
