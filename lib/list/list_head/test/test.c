#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>
 
#include "../debug.h"
#include "../../list_body/debug.h"
#include "../../../utils/debug.h"
#include "../../../node/debug.h"



list_head_p list_head_create_vector(int tot, node_p N[])
{
    list_head_p lh = list_head_create(NULL, NULL);
    for(int i=0; i<tot; i++)
        list_head_insert(lh, N[i]);

    return lh;
}

bool list_head_vector(list_head_p lh, int tot_h, ...)
{
    va_list args;
    va_start(args, tot_h);

    int i=0;
    for(; lh && (i<tot_h); i++, lh = lh->lh)
    {
        int tot_b = va_arg(args, int);
        node_p N[tot_b];
        for(int j=0; j<tot_b; j++)
            N[j] = va_arg(args, node_p);

        if(list_body_vector(LB(lh), tot_b, N)) continue;
        PRINT("\nERROR LIST HEAD VECTOR 1 | LIST BODY MISMATCH | %d %d\t\t", i, tot_h);
        return false;
    }

    if(lh)
    {
        PRINT("\nERROR LIST HEAD VECTOR 2 | LIST LONGER | %d\t\t", tot_h);
        return false;
    }

    if(i < tot_h)
    {
        PRINT("\nERROR LIST HEAD VECTOR | LIST SHORTER | %d %d\t\t", i, tot_h);
        return false;
    }

    return true;
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
    assert(list_head_vector(lh, 1, 1, n1));

    node_p n2 = node_str_create_test(V, 2);
    list_head_insert(lh, n2);
    assert(list_head_vector(lh, 1, 2, n1, n2));

    node_p n3 = node_str_create_test(V, 1);
    list_head_insert(lh, n3);
    assert(list_head_vector(lh, 2, 1, n3, 2, n1, n2));
    
    node_p n4 = node_str_create_test(V, 4);
    list_head_insert(lh, n4);
    assert(list_head_vector(lh, 3, 1, n3, 2, n1, n2, 1, n4));

    node_p n5 = node_str_create_test(V, 4);
    list_head_insert(lh, n5);
    assert(list_head_vector(lh, 3, 1, n3, 2, n1, n2, 2, n4, n5));

    node_p n6 = node_str_create_test(V, 3);
    list_head_insert(lh, n6);
    assert(list_head_vector(lh, 4, 1, n3, 2, n1, n2, 1, n6, 2, n4, n5));
}

void test_list_head_remove()
{
    printf("\n\t\ttest list head remove\t\t");

    node_p N[] = {
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

    list_head_p lh = list_head_create_vector(11, N);
    assert(list_head_vector(lh, 4, 
        3, N[0], N[2], N[1], 
        2, N[3], N[4], 
        3, N[5], N[7], N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  1\t\t");
    list_head_remove(lh, N[2]);
    assert(list_head_vector(lh, 4, 
        2, N[0], N[1], 
        2, N[3], N[4], 
        3, N[5], N[7], N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  2\t\t");
    list_head_remove(lh, N[0]);
    assert(list_head_vector(lh, 4, 
        1, N[1], 
        2, N[3], N[4], 
        3, N[5], N[7], N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  3\t\t");
    list_head_remove(lh, N[1]);
    assert(list_head_vector(lh, 3, 
        2, N[3], N[4], 
        3, N[5], N[7], N[6], 
        3, N[8], N[10], N[9])
    );

    list_head_remove(lh, N[4]);
    assert(list_head_vector(lh, 3, 
        1, N[3],
        3, N[5], N[7], N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  4\t\t");
    list_head_remove(lh, N[7]);
    assert(list_head_vector(lh, 3, 
        1, N[3],
        2, N[5], N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  5\t\t");
    list_head_remove(lh, N[5]);
    assert(list_head_vector(lh, 3, 
        1, N[3],
        1, N[6], 
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  6\t\t");
    list_head_remove(lh, N[6]);
    assert(list_head_vector(lh, 2, 
        1, N[3],
        3, N[8], N[10], N[9])
    );

    printf("\n\t\t\ttest list head remove  7\t\t");
    list_head_remove(lh, N[10]);
    assert(list_head_vector(lh, 2, 
        1, N[3],
        2, N[8], N[9])
    );

    printf("\n\t\t\ttest list head remove  8\t\t");
    list_head_remove(lh, N[8]);
    assert(list_head_vector(lh, 2, 
        1, N[3],
        1, N[9])
    );

    printf("\n\t\t\ttest list head remove  9\t\t");
    list_head_remove(lh, N[9]);
    assert(list_head_vector(lh, 1,  1, N[3]));

    printf("\n\t\t\ttest list head remove 10\t\t");
    list_head_remove(lh, N[3]);
    assert(list_head_vector(lh, 1, 1, NULL));
}

void test_list_head_merge()
{
    printf("\n\t\ttest list head merge\t\t");

    node_p n1 = node_str_create_test(V, 1);
    list_head_p lh_1 = list_head_create(n1, NULL);

    node_p n2 = node_str_create_test(V, 1);
    list_head_p lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(list_head_vector(lh_1, 1, 2, n1, n2));



    n1 = node_str_create_test(V, 1);
    lh_1 = list_head_create(n1, NULL);

    n2 = node_str_create_test(V, 2);
    lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(list_head_vector(lh_1, 2, 1, n1, 1, n2));



    n1 = node_str_create_test(V, 2);
    lh_1 = list_head_create(n1, NULL);

    n2 = node_str_create_test(V, 1);
    lh_2 = list_head_create(n2, NULL);

    list_head_merge(lh_1, lh_2);
    assert(list_head_vector(lh_1, 2, 1, n2, 1, n1));


    node_p N1[] = {
        node_str_create_test(V, 1),
        node_str_create_test(V, 3),
        node_str_create_test(V, 5),
    };
    lh_1 = list_head_create_vector(3, N1);

    node_p N2[] = {
        node_str_create_test(V, 1),
        node_str_create_test(V, 2),
        node_str_create_test(V, 3),
        node_str_create_test(V, 4),
    };
    lh_2 = list_head_create_vector(4, N2);

    list_head_merge(lh_1, lh_2);
    assert(list_head_vector(lh_1, 5,
        2, N1[0], N2[0],
        1, N2[1],
        2, N1[1], N2[2],
        1, N2[3],
        1, N1[2]
    ));
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
