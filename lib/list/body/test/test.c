#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../debug.h"
#include "../../head/debug.h"
#include "../../../amp/debug.h"
#include "../../../node/debug.h"
#include "../../../macros/test.h"
#include "../../../../mods/clu/header.h"



void test_list_body_create(bool show)
{
    printf("\n\t%s\t\t", __func__);

    CLU_REGISTER(ND(1));

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    list_body_p lb = list_body_create(NULL, NULL);
    assert(lb->node == NULL);
    assert(lb->next == NULL);
    list_body_free(lb);

    if(show) printf("\n\t\t%s 2\t\t", __func__);
    lb = list_body_create(ND(1), NULL);
    assert(lb->node == ND(1));
    assert(lb->next == NULL);
    list_body_free(lb);

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    list_body_p lb_aux = list_body_create(NULL, NULL);
    lb = list_body_create(NULL, lb_aux);
    assert(lb->node == NULL);
    assert(lb->next == lb_aux);
    list_body_free(lb);

    if(show) printf("\n\t\t%s 4\t\t", __func__);
    lb_aux = list_body_create(NULL, NULL);
    lb = list_body_create(ND(1), lb_aux);
    assert(lb->node == ND(1));
    assert(lb->next == lb_aux);
    list_body_free(lb);

    CLU_UNREGISTER(ND(1));

    assert(clu_mem_is_empty());
}

void test_list_body_create_vec(bool show)
{
    printf("\n\t%s\t\t", __func__);
    
    for(long int i=1; i<5; i++)
        CLU_REGISTER(ND(i));

    #define TEST_LIST_BODY_CREATE_VEC(TAG, N, ...)   \
    {   \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        list_body_p lb = list_body_create_vec(N, (node_p[]){__VA_ARGS__});  \
        assert(list_body_immed(lb, N, __VA_ARGS__));    \
    }

    TEST_LIST_BODY_CREATE_VEC(1, 1, ND(1));
    TEST_LIST_BODY_CREATE_VEC(2, 2, ND(1), ND(2));
    TEST_LIST_BODY_CREATE_VEC(3, 3, ND(1), ND(2), ND(3));

    #undef TEST_LIST_BODY_CREATE_VEC

    if(show) printf("\n\t\t%s 4\t\t", __func__);
    TEST_REVERT_OPEN
    list_body_create_vec(0, NULL);
    TEST_REVERT_CLOSE
    
    for(long int i=1; i<5; i++)
        CLU_UNREGISTER(ND(i));

    assert(clu_mem_is_empty());
}



void test_list_body_remove(bool show)
{
    printf("\n\t%s\t\t", __func__);
    
    clu_set_log(true);

    #define TEST_LIST_BODY_REMOVE(TAG, NODE, ...)   \
    {   \
        list_body_p lb[2];  \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        printf("\nb");  \
        list_body_create_vec_immed(lb, 2, __VA_ARGS__); \
        printf("\na");  \
        lb[0] = list_body_remove(lb[0], NODE);  \
        printf("\nb");  \
        assert(list_body_str(lb[0], lb[1]));    \
    }

    TEST_LIST_BODY_REMOVE(1, ND(1),
        1, ND(1),
        0
    );

    assert(clu_mem_is_empty());
}

// void test_list_body_merge(bool show)
// {
//     printf("\n\t%s\t\t", __func__);

//     if(show) printf("\n\t\t%s 1\t\t", __func__);
//     list_body_p lb_1 = list_body_create_test(1, 2);
//     list_body_p lb_2 = list_body_create_test(3, 4);
//     lb_1 = list_body_merge(lb_1, lb_2);
//     assert(list_body_immed(lb_1, 4, ND(3), ND(4), ND(1), ND(2)));
//     list_body_free(lb_1);

//     if(show) printf("\n\t\t%s 2\t\t", __func__);
//     lb_1 = list_body_create_test(1, 2);
//     lb_2 = list_body_create(ND(3), NULL);
//     lb_1 = list_body_merge(lb_1, lb_2);
//     assert(list_body_immed(lb_1, 3, ND(3), ND(1), ND(2)));
//     list_body_free(lb_1);

//     if(show) printf("\n\t\t%s 3\t\t", __func__);
//     lb_1 = list_body_create(ND(1), NULL);
//     lb_2 = list_body_create_test(2, 3);
//     lb_1 = list_body_merge(lb_1, lb_2);
//     assert(list_body_immed(lb_1, 3, ND(2), ND(3), ND(1)));
//     list_body_free(lb_1);

//     if(show) printf("\n\t\t%s 4\t\t", __func__);
//     lb_1 = list_body_create(ND(1), NULL);
//     lb_2 = list_body_create(ND(2), NULL);
//     lb_1 = list_body_merge(lb_1, lb_2);
//     assert(list_body_immed(lb_1, 2, ND(2), ND(1)));
//     list_body_free(lb_1);

//     if(show) printf("\n\t\t%s 5\t\t", __func__);
//     lb_2 = list_body_create(ND(2), NULL);
//     lb_1 = list_body_merge(NULL, lb_2);
//     assert(list_body_immed(lb_1, 1, ND(2)));
//     list_body_free(lb_1);

//     if(show) printf("\n\t\t%s 6\t\t", __func__);
//     lb_1 = list_body_create(ND(2), NULL);
//     lb_1 = list_body_merge(lb_1, NULL);
//     assert(list_body_immed(lb_1, 1, ND(2)));
//     list_body_free(lb_1);

//     assert(clu_mem_is_empty());
// }



void test_list_body()
{
    printf("\n%s\t\t", __func__);

    bool show = true;

    test_list_body_create(show);
    test_list_body_create_vec(show);

    test_list_body_remove(show);
    // test_list_body_merge(show);

    assert(clu_mem_is_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_body();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
