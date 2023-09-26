#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
 
#include "../debug.h"
#include "../../list_body/debug.h"
#include "../../../utils/debug.h"
#include "../../../node/debug.h"
#include "../../../../static_utils/mem_report/bin/header.h"



list_head_p list_head_create_vector(int tot, node_p N[])
{
    list_head_p lh = NULL;
    for(int i=0; i<tot; i++)
        lh = list_head_insert(lh, N[i], i&1);

    return lh;
}

void node_vector_free(int len, node_p N[])
{
    for(int i=0; i<len; i++)
        free(N[i]);
}



void test_list_head_create()
{
    printf("\n\t%s\t\t", __func__);

    printf("\n\t\t%s 1\t\t", __func__);
    node_p n = node_amp_create(&(amp_t){1, 2});
    list_head_p lh = list_head_create(n, LH(2), ELSE);
    assert(lh->lab.cl == 0);
    assert(lh->lab.lv == 0);
    assert(list_body_vector(lh->lb[ELSE], 1, n));
    assert(list_body_vector(lh->lb[THEN], 0));
    assert(lh->lh == LH(2));
    free(lh->lb[ELSE]);
    free(lh);
    free(n);

    printf("\n\t\t%s 2\t\t", __func__);
    n  = node_str_create(&(label_t){V, 2});
    lh = list_head_create(n, NULL, THEN);
    assert(list_head_vector(lh, 1,
        (label_t){V, 2}, 0, 1, n
    ));
    list_head_free(lh);
    free(n);

    assert(mem_empty());
}



void test_list_head_insert()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p N[] = {
        node_str_create(&(label_t){V, 2}), // 0
        node_str_create(&(label_t){V, 2}), // 1

        node_str_create(&(label_t){V, 1}), // 2

        node_str_create(&(label_t){V, 4}), // 3
        node_str_create(&(label_t){V, 4}), // 4

        node_str_create(&(label_t){V, 3}), // 5
    };

    printf("\n\t\t\t%s 1\t\t", __func__);
    list_head_p lh = NULL;
    lh = list_head_insert(lh, N[0], ELSE);
    assert(list_head_vector(lh, 1, 
        (label_t){V, 2}, 1, N[0], 0
    ));

    printf("\n\t\t\t%s 2\t\t", __func__);
    lh = list_head_insert(lh, N[1], THEN);
    assert(list_head_vector(lh, 1, 
        (label_t){V, 2}, 1, N[0], 1, N[1] 
    ));

    printf("\n\t\t\t%s 3\t\t", __func__);
    lh = list_head_insert(lh, N[2], ELSE);
    assert(list_head_vector(lh, 2,
        (label_t){V, 1}, 1, N[2], 0,
        (label_t){V, 2}, 1, N[0], 1, N[1] 
    ));
    
    printf("\n\t\t\t%s 4\t\t", __func__);
    lh = list_head_insert(lh, N[3], THEN);
    assert(list_head_vector(lh, 3,
        (label_t){V, 1}, 1, N[2], 0,
        (label_t){V, 2}, 1, N[0], 1, N[1],
        (label_t){V, 4}, 0, 1, N[3]
    ));

    printf("\n\t\t\t%s 5\t\t", __func__);
    lh = list_head_insert(lh, N[4], ELSE);
    assert(list_head_vector(lh, 3,
        (label_t){V, 1}, 1, N[2], 0,
        (label_t){V, 2}, 1, N[0], 1, N[1],
        (label_t){V, 4}, 1, N[4], 1, N[3]
    ));

    printf("\n\t\t\t%s 6\t\t", __func__);
    lh = list_head_insert(lh, N[5], THEN);
    assert(list_head_vector(lh, 4,
        (label_t){V, 1}, 1, N[2], 0,
        (label_t){V, 2}, 1, N[0], 1, N[1],
        (label_t){V, 3}, 0,       1, N[5],
        (label_t){V, 4}, 1, N[4], 1, N[3]
    ));

    list_head_free(lh);
    node_vector_free(6, N);
    assert(mem_empty());
}

// void test_list_head_remove()
// {
//     printf("\n\t\t%s\t\t", __func__);

//     node_p N[] = {
//         node_str_create(&(label_t){V, 1}), // 0
//         node_str_create(&(label_t){V, 1}), // 1
//         node_str_create(&(label_t){V, 1}), // 2
        
//         node_str_create(&(label_t){V, 2}), // 3
//         node_str_create(&(label_t){V, 2}), // 4
        
//         node_str_create(&(label_t){V, 3}), // 5
//         node_str_create(&(label_t){V, 3}), // 6
//         node_str_create(&(label_t){V, 3}), // 7
        
//         node_str_create(&(label_t){V, 4}), // 8
//         node_str_create(&(label_t){V, 4}), // 9
//         node_str_create(&(label_t){V, 4}), // 10
//     };

//     list_head_p lh = list_head_create_vector(11, N);
//     assert(list_head_vector(lh, 4, 
//         3, N[ 2], N[1], N[0], 
//         2, N[ 4], N[3], 
//         3, N[ 7], N[6], N[5], 
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  1\t\t", __func__);
//     lh = list_head_remove(lh, N[2]);
//     assert(list_head_vector(lh, 4, 
//         2, N[ 1], N[0], 
//         2, N[ 4], N[3], 
//         3, N[ 7], N[6], N[5], 
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  2\t\t", __func__);
//     lh = list_head_remove(lh, N[0]);
//     assert(list_head_vector(lh, 4, 
//         1, N[ 1], 
//         2, N[ 4], N[3], 
//         3, N[ 7], N[6], N[5], 
//         3, N[10], N[9], N[8]
//     ));


//     printf("\n\t\t\t%s  3\t\t", __func__);
//     lh = list_head_remove(lh, N[1]);
//     assert(list_head_vector(lh, 3,
//         2, N[ 4], N[3], 
//         3, N[ 7], N[6], N[5],
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  4\t\t", __func__);
//     lh = list_head_remove(lh, N[4]);
//     assert(list_head_vector(lh, 3,
//         1, N[ 3], 
//         3, N[ 7], N[6], N[5],
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  5\t\t", __func__);
//     lh = list_head_remove(lh, N[7]);
//     assert(list_head_vector(lh, 3,
//         1, N[ 3], 
//         2, N[ 6], N[5],
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  6\t\t", __func__);
//     lh = list_head_remove(lh, N[5]);
//     assert(list_head_vector(lh, 3,
//         1, N[ 3], 
//         1, N[ 6],
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  7\t\t", __func__);
//     lh = list_head_remove(lh, N[6]);
//     assert(list_head_vector(lh, 2,
//         1, N[ 3], 
//         3, N[10], N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  8\t\t", __func__);
//     lh = list_head_remove(lh, N[10]);
//     assert(list_head_vector(lh, 2,
//         1, N[3], 
//         2, N[9], N[8]
//     ));

//     printf("\n\t\t\t%s  9\t\t", __func__);
//     lh = list_head_remove(lh, N[8]);
//     assert(list_head_vector(lh, 2,
//         1, N[3], 
//         1, N[9]
//     ));

//     printf("\n\t\t\t%s 10\t\t", __func__);
//     lh = list_head_remove(lh, N[9]);
//     assert(list_head_vector(lh, 1,
//         1, N[3]
//     ));

//     printf("\n\t\t\t%s 11\t\t", __func__);
//     lh = list_head_remove(lh, N[3]);
//     assert(lh == NULL);

//     free(lh);
//     node_vector_free(11, N);
//     assert(mem_empty());
// }

// void test_list_head_merge()
// {
//     printf("\n\t\t%s\t\t", __func__);

//     printf("\n\t\t\t%s 1\t\t", __func__);
//     node_p n1 = node_str_create(&(label_t){V, 1});
//     list_head_p lh_1 = list_head_create(n1, NULL);

//     node_p n2 = node_str_create(&(label_t){V, 1});
//     list_head_p lh_2 = list_head_create(n2, NULL);

//     lh_1 = list_head_merge(lh_1, lh_2);
//     assert(list_head_vector(lh_1, 1, 2, n2, n1));

//     list_head_free(lh_1);
//     free(n1);
//     free(n2);
//     assert(mem_empty());



//     printf("\n\t\t\t%s 2\t\t", __func__);
//     n1 = node_str_create(&(label_t){V, 1});
//     lh_1 = list_head_create(n1, NULL);

//     n2 = node_str_create(&(label_t){V, 2});
//     lh_2 = list_head_create(n2, NULL);

//     lh_1 = list_head_merge(lh_1, lh_2);
//     assert(list_head_vector(lh_1, 2, 
//         1, n1, 
//         1, n2
//     ));

//     list_head_free(lh_1);
//     free(n1);
//     free(n2);
//     assert(mem_empty());



//     printf("\n\t\t\t%s 3\t\t", __func__);
//     n1 = node_str_create(&(label_t){V, 2});
//     lh_1 = list_head_create(n1, NULL);

//     n2 = node_str_create(&(label_t){V, 1});
//     lh_2 = list_head_create(n2, NULL);

//     lh_1 = list_head_merge(lh_1, lh_2);
//     assert(list_head_vector(lh_1, 2, 
//         1, n2, 
//         1, n1
//     ));

//     list_head_free(lh_1);
//     free(n1);
//     free(n2);
//     assert(mem_empty());



//     printf("\n\t\t\t%s 4\t\t", __func__);
//     node_p N1[] = {
//         node_str_create(&(label_t){V, 1}),
//         node_str_create(&(label_t){V, 3}),
//         node_str_create(&(label_t){V, 5}),
//     };
//     lh_1 = list_head_create_vector(3, N1);

//     node_p N2[] = {
//         node_str_create(&(label_t){V, 1}),
//         node_str_create(&(label_t){V, 2}),
//         node_str_create(&(label_t){V, 3}),
//         node_str_create(&(label_t){V, 4}),
//     };
//     lh_2 = list_head_create_vector(4, N2);

//     lh_1 = list_head_merge(lh_1, lh_2);
//     assert(list_head_vector(lh_1, 5,
//         2, N2[0], N1[0],
//         1, N2[1],
//         2, N2[2], N1[1],
//         1, N2[3],
//         1, N1[2]
//     ));

//     list_head_free(lh_1);
//     node_vector_free(3, N1);
//     node_vector_free(4, N2);
//     assert(mem_empty());
// }

// void test_list_head_invert()
// {
//     printf("\n\t\t%s\t\t", __func__);

//     list_head_p lh = list_head_create(ND(1), NULL);
//     lh = list_head_invert(lh);
//     assert(list_head_vector(lh, 1, 1, ND(1)));

//     lh = list_head_create(ND(2), lh);
//     lh = list_head_invert(lh);
//     assert(list_head_vector(lh, 2, 1, ND(1), 1, ND(2)));
//     list_head_free(lh);

//     assert(mem_empty());
// }

void test_list_head_operations()
{
    printf("\n\t%s\t\t", __func__);

    test_list_head_insert();
    // test_list_head_remove();
    // test_list_head_merge();
    // test_list_head_invert();

    assert(mem_empty());
}



void test_list_head()
{
    printf("\n%s\t\t", __func__);

    test_list_head_create();
    test_list_head_operations();

    assert(mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_head();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
