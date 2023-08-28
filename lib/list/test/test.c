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
        node_str_create(V, 1), // 1
        node_str_create(V, 1), // 2
        
        node_str_create(V, 2), // 3
        node_str_create(V, 2), // 4
        
        node_str_create(V, 3), // 5
        node_str_create(V, 3), // 6
        node_str_create(V, 3), // 7
        
        node_str_create(V, 4), // 8
        node_str_create(V, 4), // 9
        node_str_create(V, 4), // 10
    };

    list_head_p lh = list_head_create(NULL, NULL);
    for(int i=0; i<11; i++)
        list_head_insert(lh, n[i]);

    printf("\n\t\t\t\ttest list head remove  1\t\t");
    list_head_remove(lh, n[2]);
    assert(LB(lh)->lb->n == n[1]);
    
    printf("\n\t\t\t\ttest list head remove  2\t\t");
    list_head_remove(lh, n[0]);
    assert(LB(lh)->n  == n[1]);
    assert(LB(lh)->lb == NULL);
    
    printf("\n\t\t\t\ttest list head remove  3\t\t");
    list_head_remove(lh, n[1]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh)->lb);
    assert(LB(lh)->lb->n == n[4]);
    list_head_remove(lh, n[4]);
    
    printf("\n\t\t\t\ttest list head remove  4\t\t");
    list_head_remove(lh, n[7]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->lb->n == n[6]);
    
    printf("\n\t\t\t\ttest list head remove  5\t\t");
    list_head_remove(lh, n[5]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n  == n[6]);
    assert(LB(lh->lh)->lb == NULL);

    printf("\n\t\t\t\ttest list head remove  6\t\t");
    list_head_remove(lh, n[6]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n == n[8]);
    assert(LB(lh->lh)->lb);
    assert(LB(lh->lh)->lb->n == n[10]);

    printf("\n\t\t\t\ttest list head remove  7\t\t");
    list_head_remove(lh, n[10]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->lb->n == n[9]);
    
    printf("\n\t\t\t\ttest list head remove  8\t\t");
    list_head_remove(lh, n[8]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n  == n[9]);
    assert(LB(lh->lh)->lb == NULL);
    assert(LB(lh)->n == n[3]);

    printf("\n\t\t\t\ttest list head remove  9\t\t");
    list_head_remove(lh, n[9]);
    assert(LB(lh)->n == n[3]);
    assert(lh->lh == NULL);

    printf("\n\t\t\t\ttest list head remove 10\t\t");
    list_head_remove(lh, n[3]);
    assert(LB(lh)->n == NULL);
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
