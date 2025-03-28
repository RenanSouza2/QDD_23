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

    CLU_HANDLER_REGISTER(ND(1));

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

    CLU_HANDLER_UNREGISTER(ND(1));

    assert(clu_mem_is_empty());
}

void test_list_body_create_vec(bool show)
{
    printf("\n\t%s\t\t", __func__);

    for(long int i=1; i<5; i++)
        CLU_HANDLER_REGISTER(ND(i));

    #define TEST_LIST_BODY_CREATE_VEC(TAG, N, ...)                          \
    {                                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);                  \
        list_body_p lb = list_body_create_vec(N, (node_p[]){__VA_ARGS__});  \
        assert(list_body_immed(lb, N, __VA_ARGS__));                        \
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
        CLU_HANDLER_UNREGISTER(ND(i));

    assert(clu_mem_is_empty());
}



void test_list_body_remove(bool show)
{
    printf("\n\t%s\t\t", __func__);

    for(long int i=1; i<4; i++)
        CLU_HANDLER_REGISTER(ND(i));

    #define TEST_LIST_BODY_REMOVE(TAG, NODE, ...)           \
    {                                                       \
        list_body_p lb[2];                                  \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        list_body_create_vec_immed(lb, 2, __VA_ARGS__);     \
        lb[0] = list_body_remove(lb[0], NODE);              \
        assert(list_body(lb[0], lb[1]));                \
    }

    TEST_LIST_BODY_REMOVE(1, ND(1),
        1, ND(1),
        0
    );
    TEST_LIST_BODY_REMOVE(2, ND(1),
        2, ND(1), ND(2),
        1, ND(2)
    );
    TEST_LIST_BODY_REMOVE(3, ND(2),
        2, ND(1), ND(2),
        1, ND(1)
    );
    TEST_LIST_BODY_REMOVE(4, ND(1),
        3, ND(1), ND(2), ND(3),
        2, ND(2), ND(3)
    );
    TEST_LIST_BODY_REMOVE(5, ND(2),
        3, ND(1), ND(2), ND(3),
        2, ND(1), ND(3)
    );
    TEST_LIST_BODY_REMOVE(6, ND(3),
        3, ND(1), ND(2), ND(3),
        2, ND(1), ND(2)
    );

    #undef TEST_LIST_BODY_REMOVE

    if(show) printf("\n\t\t%s 6\t\t", __func__);
    TEST_REVERT_OPEN
    list_body_remove(NULL, ND(1));
    TEST_REVERT_CLOSE

    if(show) printf("\n\t\t%s 7\t\t", __func__);
    list_body_p lb = list_body_create_immed(1, ND(1));
    TEST_REVERT_OPEN
    list_body_remove(lb, NULL);
    TEST_REVERT_CLOSE
    list_body_free(lb);

    if(show) printf("\n\t\t%s 8\t\t", __func__);
    lb = list_body_create_immed(1, ND(1));
    TEST_REVERT_OPEN
    list_body_remove(lb, ND(2));
    TEST_REVERT_CLOSE
    list_body_free(lb);

    for(long int i=1; i<4; i++)
        CLU_HANDLER_UNREGISTER(ND(i));

    assert(clu_mem_is_empty());
}

void test_list_body_merge(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LIST_BODY_MERGE(TAG, ...)  \
    {   \
        list_body_p lb[3];  \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        list_body_create_vec_immed(lb, 3, __VA_ARGS__); \
        lb[0] = list_body_merge(lb[0], lb[1]);  \
        assert(list_body(lb[0], lb[2]));    \
    }

    TEST_LIST_BODY_MERGE(1,
        0,
        0,
        0
    );
    TEST_LIST_BODY_MERGE(2,
        1, ND(1),
        0,
        1, ND(1)
    );
    TEST_LIST_BODY_MERGE(3,
        0,
        1, ND(1),
        1, ND(1)
    );
    TEST_LIST_BODY_MERGE(4,
        1, ND(1),
        1, ND(2),
        2, ND(2), ND(1)
    );
    TEST_LIST_BODY_MERGE(5,
        1, ND(1),
        2, ND(2), ND(3),
        3, ND(2), ND(3), ND(1)
    );

    assert(clu_mem_is_empty());
}



void test_list_body()
{
    printf("\n%s\t\t", __func__);

    bool show = false;

    test_list_body_create(show);
    test_list_body_create_vec(show);

    test_list_body_remove(show);
    test_list_body_merge(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(5)
    test_list_body();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
