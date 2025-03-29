#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../debug.h"
#include "../../body/debug.h"
#include "../../../amp/debug.h"
#include "../../../label/debug.h"
#include "../../../utils/debug.h"
#include "../../../node/debug.h"
#include "../../../macros/test.h"
#include "../../../../mods/clu/header.h"



void test_list_head_create_body(bool show)
{
    printf("\n\t%s\t\t", __func__);

    CLU_HANDLER_REGISTER(LH(2));

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node = node_amp_create(AMPI(1, 1));
    list_body_p lb = list_body_create(node, NULL);
    list_head_p lh = list_head_create_body(lb, ELSE, LH(2));
    assert(label(lh->lab, LAB(0, 0)));
    assert(list_body_immed(lh->lb[ELSE], 1, node));
    assert(list_body_immed(lh->lb[THEN], 0));
    assert(lh->next == LH(2));
    free(node);
    free(lh);

    if(show) printf("\n\t\t%s 2\t\t", __func__);
    node = node_branch_create(LAB(V, 2));
    lb = list_body_create(node, NULL);
    lh = list_head_create_body(lb, THEN, NULL);
    assert(label(lh->lab, LAB(V, 2)));
    assert(list_body_immed(lh->lb[ELSE], 0));
    assert(list_body_immed(lh->lb[THEN], 1, node));
    assert(lh->next == NULL);
    free(node);
    free(lh);

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_create_body(NULL, ELSE, NULL);
    TEST_REVERT_CLOSE

    if(show) printf("\n\t\t%s 4\t\t", __func__);
    lb = list_body_create(NULL, NULL);
    TEST_REVERT_OPEN
    list_head_create_body(NULL, ELSE, NULL);
    TEST_REVERT_CLOSE
    free(lb);

    CLU_HANDLER_UNREGISTER(LH(2));

    assert(clu_mem_is_empty());
}

void test_list_head_create(bool show)
{
    printf("\n\t%s\t\t", __func__);

    CLU_HANDLER_REGISTER(LH(2));

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node = node_amp_create(AMPI(1, 1));
    list_head_p lh = list_head_create(node, ELSE, LH(2));
    assert(label(lh->lab, LAB(0, 0)));
    assert(list_body_immed(lh->lb[ELSE], 1, node));
    assert(list_body_immed(lh->lb[THEN], 0));
    assert(lh->next == LH(2));
    free(node);
    free(lh);

    if(show) printf("\n\t\t%s 2\t\t", __func__);
    node = node_branch_create(LAB(V, 2));
    lh = list_head_create(node, THEN, NULL);
    assert(label(lh->lab, LAB(V, 2)));
    assert(list_body_immed(lh->lb[ELSE], 0));
    assert(list_body_immed(lh->lb[THEN], 1, node));
    assert(lh->next == NULL);
    free(node);
    free(lh);

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_create(NULL, ELSE, NULL);
    TEST_REVERT_CLOSE

    CLU_HANDLER_UNREGISTER(LH(2));

    assert(clu_mem_is_empty());
}

void test_list_head_pop(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    list_head_p lh = list_head_create_immed(1,
        LAB(V, 1), 0, 0
    );
    lh = list_head_pop(lh);
    assert(lh == NULL);

    if(show) printf("\n\t\t%s 2\t\t", __func__);
    lh = list_head_create_immed(2,
        LAB(V, 1), 0, 0,
        LAB(V, 2), 0, 0
    );
    lh = list_head_pop(lh);
    assert(lh != NULL);
    assert(label(lh->lab, LAB(V, 2)));
    free(lh);

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_pop(NULL);
    TEST_REVERT_CLOSE

    assert(clu_mem_is_empty());
}



void test_list_head_first(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LIST_HEAD_FIRST(TAG, RES, ...)                 \
    {                                                           \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);      \
        list_head_p lh = list_head_create_immed(__VA_ARGS__);   \
        node_p node = list_head_first(lh);                      \
        assert(node == RES);                                    \
        list_head_free(lh);                                     \
    }

    TEST_LIST_HEAD_FIRST(1, ND(1), 2,
        LAB(V, 1), 1, ND(1), 1, ND(2),
        LAB(V, 2), 1, ND(3), 1, ND(4)
    );
    TEST_LIST_HEAD_FIRST(2, ND(2), 2,
        LAB(V, 1), 0, 1, ND(2),
        LAB(V, 2), 1, ND(3), 1, ND(4)
    )

    #undef TEST_LIST_HEAD_FIRST

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_first(NULL);
    TEST_REVERT_CLOSE

    assert(clu_mem_is_empty());
}

void test_list_head_occupied(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LIST_HEAD_OCCUPIED(TAG, RES, ...)              \
    {                                                           \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);      \
        list_head_p lh = list_head_create_immed(__VA_ARGS__);   \
        bool node = list_head_occupied(lh);                     \
        assert(node == RES);                                    \
        list_head_free(lh);                                     \
    }

    TEST_LIST_HEAD_OCCUPIED(1, false, 1,
        LAB(V, 1), 0, 0
    );
    TEST_LIST_HEAD_OCCUPIED(2, true, 1,
        LAB(V, 1), 1, ND(1), 0
    );
    TEST_LIST_HEAD_OCCUPIED(3, true, 1,
        LAB(V, 1), 0, 1, ND(2)
    );
    TEST_LIST_HEAD_OCCUPIED(4, true, 1,
        LAB(V, 1), 1, ND(1), 1, ND(2)
    );

    #undef TEST_LIST_HEAD_OCCUPIED

    assert(clu_mem_is_empty());
}



void test_list_head_insert(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LIST_HEAD_INSERT(TAG, NODE, SIDE, ...)     \
    {                                                       \
        list_head_p lh[2];                                  \
        if(show) printf("\n\t\t%s %2d\t\t", __func__, TAG); \
        list_head_create_vec_immed(lh, 2, __VA_ARGS__);     \
        lh[0] = list_head_insert(lh[0], NODE, SIDE);        \
        assert(list_head(lh[0], lh[1]));                    \
    }


    node_p node[] = {
        node_amp_create(AMPI(1, 2)),
        node_amp_create(AMPI(1, 3)),

        node_branch_create(LAB(V, 1)),

        node_branch_create(LAB(V, 2)),
    };

    TEST_LIST_HEAD_INSERT(1, node[0], ELSE,
        0,
        1,  LAB(0, 0), 1, node[0], 0
    );
    TEST_LIST_HEAD_INSERT(2, node[0], THEN,
        0,
        1,  LAB(0, 0), 0, 1, node[0]
    );
    TEST_LIST_HEAD_INSERT(3, node[1], ELSE,
        1,  LAB(0, 0), 0, 1, node[0],
        1,  LAB(0, 0), 1, node[1], 1, node[0]
    );
    TEST_LIST_HEAD_INSERT(4, node[1], THEN,
        1,  LAB(0, 0), 0, 1, node[0],
        1,  LAB(0, 0), 0, 2, node[1], node[0]
    );
    TEST_LIST_HEAD_INSERT(5, node[1], THEN,
        1,  LAB(0, 0), 1, node[0], 0,
        1,  LAB(0, 0), 1, node[0], 1, node[1]
    );
    TEST_LIST_HEAD_INSERT(6, node[1], ELSE,
        1,  LAB(0, 0), 1, node[0], 0,
        1,  LAB(0, 0), 2, node[1], node[0], 0
    );
    TEST_LIST_HEAD_INSERT(7, node[0], ELSE,
        1,  LAB(V, 1), 1, node[2], 0,
        2,  LAB(0, 0), 1, node[0], 0,
            LAB(V, 1), 1, node[2], 0
    );
    TEST_LIST_HEAD_INSERT(8, node[2], ELSE,
        1,  LAB(0, 0), 1, node[0], 0,
        2,  LAB(0, 0), 1, node[0], 0,
            LAB(V, 1), 1, node[2], 0
    );
    TEST_LIST_HEAD_INSERT(9, node[2], ELSE,
        2,  LAB(0, 0), 1, node[0], 0,
            LAB(V, 2), 1, node[3], 0,
        3,  LAB(0, 0), 1, node[0], 0,
            LAB(V, 1), 1, node[2], 0,
            LAB(V, 2), 1, node[3], 0
    );

    #undef TEST_LIST_HEAD_INSERT

    if(show) printf("\n\t\t%s 10\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_insert(NULL, NULL, ELSE);
    TEST_REVERT_CLOSE

    for(int i=0; i<4; i++)
        free(node[i]);

    assert(clu_mem_is_empty());
}

void test_list_head_remove(bool show)
{
    printf("\n\t%s\t\t", __func__);

    node_p node[] = {
        node_amp_create(AMPI(1, 2)),
        node_amp_create(AMPI(1, 3)),

        node_branch_create(LAB(V, 1)),

        node_branch_create(LAB(V, 2)),
    };

    #define TEST_LIST_HEAD_REMOVE(TAG, NODE, SIDE, ...)     \
    {                                                       \
        list_head_p lh[2];                                  \
        if(show) printf("\n\t\t%s %2d\t\t", __func__, TAG); \
        list_head_create_vec_immed(lh, 2, __VA_ARGS__);     \
        lh[0] = list_head_remove(lh[0], NODE, SIDE);        \
        assert(list_head(lh[0], lh[1]));                    \
    }

    TEST_LIST_HEAD_REMOVE(1, node[0], ELSE,
        1,  LAB(0, 0), 1, node[0], 0,
        0
    );
    TEST_LIST_HEAD_REMOVE(2, node[0], ELSE,
        1,  LAB(0, 0), 1, node[0], 1, node[1],
        1,  LAB(0, 0), 0, 1, node[1]
    );
    TEST_LIST_HEAD_REMOVE(3, node[0], ELSE,
        1,  LAB(0, 0), 2, node[0], node[1], 0,
        1,  LAB(0, 0), 1, node[1], 0
    );
    TEST_LIST_HEAD_REMOVE(4, node[0], THEN,
        2,  LAB(0, 0), 0, 1, node[0],
            LAB(V, 1), 1, node[2], 0,
        1,  LAB(V, 1), 1, node[2], 0
    );
    TEST_LIST_HEAD_REMOVE(5, node[2], ELSE,
        2,  LAB(0, 0), 0, 1, node[0],
            LAB(V, 1), 1, node[2], 0,
        1,  LAB(0, 0), 0, 1, node[0]
    );
    TEST_LIST_HEAD_REMOVE(6, node[2], ELSE,
        3,  LAB(0, 0), 0, 1, node[0],
            LAB(V, 1), 1, node[2], 0,
            LAB(V, 2), 1, node[3], 0,
        2,  LAB(0, 0), 0, 1, node[0],
            LAB(V, 2), 1, node[3], 0
    );

    #undef TEST_LIST_HEAD_REMOVE

    if(show) printf("\n\t\t%s  7\t\t", __func__);
    TEST_REVERT_OPEN
    list_head_remove(NULL, node[0], ELSE);
    TEST_REVERT_CLOSE

    #define TEST_LIST_HEAD_REMOVE(TAG, NODE, SIDE, ...)         \
    {                                                           \
        if(show) printf("\n\t\t%s %2d\t\t", __func__, TAG);     \
        list_head_p lh = list_head_create_immed(__VA_ARGS__);   \
        TEST_REVERT_OPEN                                        \
        list_head_remove(lh, NODE, SIDE);                       \
        TEST_REVERT_CLOSE                                       \
        list_head_free(lh);                                     \
    }

    TEST_LIST_HEAD_REMOVE(8, NULL, ELSE, 1,
        LAB(V, 1), 1, node[2], 0
    );
    TEST_LIST_HEAD_REMOVE(9, node[0], ELSE, 1,
        LAB(V, 1), 1, node[2], 0
    );
    TEST_LIST_HEAD_REMOVE(10, node[3], ELSE, 1,
        LAB(V, 1), 1, node[2], 0
    );

    #undef TEST_LIST_HEAD_REMOVE

    for(int i=0; i<4; i++)
        free(node[i]);

    assert(clu_mem_is_empty());
}

void test_list_head_merge(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LIST_HEAD_MERGE(TAG, ...)                  \
    {                                                       \
        list_head_p lh[3];                                  \
        if(show) printf("\n\t\t%s %2d\t\t", __func__, TAG); \
        list_head_create_vec_immed(lh, 3, __VA_ARGS__);     \
        lh[0] = list_head_merge(lh[0], lh[1]);              \
        assert(list_head(lh[0], lh[2]));                    \
    }

    TEST_LIST_HEAD_MERGE(1,
        0,
        0,
        0
    );
    TEST_LIST_HEAD_MERGE(2,
        1,  LAB(V, 1), 1, ND(1), 0,
        0,
        1,  LAB(V, 1), 1, ND(1), 0
    );
    TEST_LIST_HEAD_MERGE(3,
        0,
        1,  LAB(V, 1), 1, ND(1), 0,
        1,  LAB(V, 1), 1, ND(1), 0
    );
    TEST_LIST_HEAD_MERGE(4,
        1,  LAB(V, 1), 1, ND(1), 0,
        1,  LAB(V, 1), 0, 1, ND(2),
        1,  LAB(V, 1), 1, ND(1), 1, ND(2)
    );
    TEST_LIST_HEAD_MERGE(5,
        1,  LAB(V, 1), 1, ND(1), 0,
        1,  LAB(V, 2), 0, 1, ND(2),
        2,  LAB(V, 1), 1, ND(1), 0,
            LAB(V, 2), 0, 1, ND(2)
    );
    TEST_LIST_HEAD_MERGE(6,
        1,  LAB(V, 2), 0, 1, ND(2),
        1,  LAB(V, 1), 1, ND(1), 0,
        2,  LAB(V, 1), 1, ND(1), 0,
            LAB(V, 2), 0, 1, ND(2)
    );

    assert(clu_mem_is_empty());
}



void test_list_head()
{
    printf("\n%s\t\t", __func__);

    bool show = false;

    test_list_head_create_body(show);
    test_list_head_create(show);
    test_list_head_pop(show);

    test_list_head_first(show);
    test_list_head_occupied(show);

    test_list_head_insert(show);
    test_list_head_remove(show);
    test_list_head_merge(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_list_head();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
