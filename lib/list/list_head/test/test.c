#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "../debug.h"
#include "../../../node/debug.h"



node_p* node_create_vector(int tot, ...)
{
    node_p *N = malloc(tot * sizeof(node_p));
    assert(N);
    
    va_list args;
    va_start(args, tot);
    for(int i=0;i<tot; i++)
    {
        label_t lab = va_arg(args, label_t);
        N[i] = node_str_create(&lab);
    }
    return N;
}

bool list_head_vector(list_head_p lh, int tot, ...)
{
    va_list args;
    va_start(args, tot);
    int i = 0;
    for(; lh; lh = lh->lh)
    for(list_body_p lb = LB(lh); lb; lb = lb->lb, i++)
    {
        if(i == tot) return false;

        node_p n = va_arg(args, node_p);
        if(lb->n != n) return false;
    }
    return !lh;
}



void test_list_head_create()
{
    printf("\n\ttest list head create\t\t");

    list_head_p lh = list_head_create(NODE(1), LH(2));
    assert(LB(lh)->n  == NODE(1));
    assert(LB(lh)->lb == NULL);
    assert(lh->lh == LH(2));
}




void test_list_head_insert()
{
    printf("\n\t\ttest list head insert\t\t");

    list_head_p lh = list_head_create(NULL, NULL);
    node_p n1 = node_str_create_test(V, 2);
    list_head_insert(lh, n1);
    assert(list_head_vector(lh, 1, n1));

    node_p n2 = node_str_create_test(V, 2);
    list_head_insert(lh, n2);
    assert(list_head_vector(lh, 2, n1, n2));

    node_p n = node_str_create_test(V, 1);
    list_head_insert(lh, n);
    assert(LB(lh)->n == n);
    assert(lh->lh);
    
    n = node_str_create_test(V, 4);
    list_head_insert(lh, n);
    assert(lh->lh->lh);
    assert(LB(lh->lh->lh)->n == n);

    n = node_str_create_test(V, 4);
    list_head_insert(lh, n);
    assert(LB(lh->lh->lh)->lb);
    assert(LB(lh->lh->lh)->lb->n == n);

    n = node_str_create_test(V, 3);
    list_head_insert(lh, n);
    assert(LB(lh->lh->lh)->n == n);
}

void test_list_head_remove()
{
    printf("\n\t\ttest list head remove\t\t");

    node_p n[] = {
        node_str_create_test(V, 1), // 0
        node_str_create_test(V, 1), // 1
        node_str_create_test(V, 1), // 2
        
        node_str_create_test(V, 2), // 3
        node_str_create_test(V, 2), // 4
        
        node_str_create_test(V, 3), // 5
        node_str_create_test(V, 3), // 6
        node_str_create_test(V, 3), // 7
        
        node_str_create_test(V, 4), // 8
        node_str_create_test(V, 4), // 9
        node_str_create_test(V, 4), // 10
    };

    list_head_p lh = list_head_create(NULL, NULL);
    for(int i=0; i<11; i++)
        list_head_insert(lh, n[i]);

    printf("\n\t\t\ttest list head remove  1\t\t");
    list_head_remove(lh, n[2]);
    assert(LB(lh)->lb->n == n[1]);
    
    printf("\n\t\t\ttest list head remove  2\t\t");
    list_head_remove(lh, n[0]);
    assert(LB(lh)->n  == n[1]);
    assert(LB(lh)->lb == NULL);
    
    printf("\n\t\t\ttest list head remove  3\t\t");
    list_head_remove(lh, n[1]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh)->lb);
    assert(LB(lh)->lb->n == n[4]);
    list_head_remove(lh, n[4]);
    
    printf("\n\t\t\ttest list head remove  4\t\t");
    list_head_remove(lh, n[7]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->lb->n == n[6]);
    
    printf("\n\t\t\ttest list head remove  5\t\t");
    list_head_remove(lh, n[5]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n  == n[6]);
    assert(LB(lh->lh)->lb == NULL);

    printf("\n\t\t\ttest list head remove  6\t\t");
    list_head_remove(lh, n[6]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n == n[8]);
    assert(LB(lh->lh)->lb);
    assert(LB(lh->lh)->lb->n == n[10]);

    printf("\n\t\t\ttest list head remove  7\t\t");
    list_head_remove(lh, n[10]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->lb->n == n[9]);
    
    printf("\n\t\t\ttest list head remove  8\t\t");
    list_head_remove(lh, n[8]);
    assert(LB(lh)->n == n[3]);
    assert(LB(lh->lh)->n  == n[9]);
    assert(LB(lh->lh)->lb == NULL);
    assert(LB(lh)->n == n[3]);

    printf("\n\t\t\ttest list head remove  9\t\t");
    list_head_remove(lh, n[9]);
    assert(LB(lh)->n == n[3]);
    assert(lh->lh == NULL);

    printf("\n\t\t\ttest list head remove 10\t\t");
    list_head_remove(lh, n[3]);
    assert(LB(lh)->n == NULL);
}

#include "../../../node/debug.h"

void test_list_head_merge()
{
    printf("\n\t\ttest list head merge\t\t");

    node_p n1 = node_str_create_test(V, 1);
    list_head_p lh_1 = list_head_create(n1, NULL);

    node_p n2 = node_str_create_test(V, 1);
    list_head_p lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(lh_1->lh == NULL);
    assert(LB(lh_1)->n == n1);
    assert(LB(lh_1)->lb);
    assert(LB(lh_1)->lb->n  == n2);
    assert(LB(lh_1)->lb->lb == NULL);



    n1 = node_str_create_test(V, 1);
    lh_1 = list_head_create(n1, NULL);

    n2 = node_str_create_test(V, 2);
    lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(LB(lh_1)->n  == n1);
    assert(LB(lh_1)->lb == NULL);
    assert(lh_1->lh);
    assert(lh_1->lh->lh == NULL);
    assert(LB(lh_1->lh)->n  == n2);
    assert(LB(lh_1->lh)->lb == NULL);



    n1 = node_str_create_test(V, 2);
    lh_1 = list_head_create(n1, NULL);

    n2 = node_str_create_test(V, 1);
    lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(LB(lh_1)->n  == n2);
    assert(LB(lh_1)->lb == NULL);
    assert(lh_1->lh);
    assert(lh_1->lh->lh == NULL);
    assert(LB(lh_1->lh)->n  == n1);
    assert(LB(lh_1->lh)->lb == NULL);

    int tot = 1;
    node_p const * const N = node_create_vector(tot, 
        (label_t){V, 1}
    );
    for(int i=0; i<tot; i++)
        node_str_display(N[i]);
}

void test_list_head_operations()
{
    printf("\n\ttest list head operations\t\t");

    test_list_head_insert();
    test_list_head_remove();
    test_list_head_merge();
}



void test_list_head()
{
    printf("\ntest list head library\t\t");

    test_list_head_create();
    test_list_head_operations();
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_head();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
