#include "../debug.h"
#include "../../amp/debug.h"
#include "../../label/debug.h"
#include "../../macros/test.h"
#include "../../list/head/debug.h"
#include "../../../mods/clu/header.h"



void test_node_create_branch(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node = node_branch_create(LAB(V, 2));
    assert(node->lh == NULL);
    assert(label(node->lab, LAB(V, 2)));
    assert(BRANCH(node)[ELSE] == NULL);
    assert(BRANCH(node)[THEN] == NULL);
    free(node);

    assert(clu_mem_is_empty());
}

void test_node_create_amp(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node = node_amp_create(AMPI(1, 2));
    assert(node->lh == NULL);
    assert(label(node->lab, LAB(0, 0)));
    assert(amplitude(AMP(node), AMPI(1, 2)));
    free(node);

    assert(clu_mem_is_empty());
}



void test_node_eq_amp(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_NODE_EQ_AMP(TAG, LAB_1, LAB_2, RES)        \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_1 = node_amp_create(LAB_1);             \
        node_p node_2 = node_amp_create(LAB_2);             \
        bool res = node_eq_amp(node_1, node_2);             \
        assert(res == RES);                                 \
        free(node_1);                                       \
        free(node_2);                                       \
    }

    TEST_NODE_EQ_AMP(1, AMPI(1, 2), AMPI(1, 2), true);
    TEST_NODE_EQ_AMP(2, AMPI(1, 2), AMPI(1, 3), false);
    TEST_NODE_EQ_AMP(3, AMPI(1, 2), AMPI(2, 2), false);

    #undef TEST_NODE_EQ_AMP

    assert(clu_mem_is_empty());
}

void test_node_eq_el(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_NODE_EQ_EL(TAG, NODE_1, NODE_2, RES)       \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_1 = node_branch_create(LAB(V, 1));      \
        node_p node_2 = node_branch_create(LAB(V, 1));      \
        BRANCH(node_1)[ELSE] = NODE_1;                      \
        BRANCH(node_2)[ELSE] = NODE_2;                      \
        bool res = node_eq_el(node_1, node_2);              \
        assert(res == RES);                                 \
        free(node_1);                                       \
        free(node_2);                                       \
    }

    TEST_NODE_EQ_EL(1, ND(1), ND(1), true);
    TEST_NODE_EQ_EL(2, ND(1), ND(2), false);

    #undef TEST_NODE_EQ_EL

    assert(clu_mem_is_empty());
}

void test_node_eq_th(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_NODE_EQ_TH(TAG, NODE_1, NODE_2, RES)       \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_1 = node_branch_create(LAB(V, 1));      \
        node_p node_2 = node_branch_create(LAB(V, 1));      \
        BRANCH(node_1)[THEN] = NODE_1;                      \
        BRANCH(node_2)[THEN] = NODE_2;                      \
        bool res = node_eq_th(node_1, node_2);              \
        assert(res == RES);                                 \
        free(node_1);                                       \
        free(node_2);                                       \
    }

    TEST_NODE_EQ_TH(1, ND(1), ND(1), true);
    TEST_NODE_EQ_TH(2, ND(1), ND(2), false);

    #undef TEST_NODE_EQ_TH

    assert(clu_mem_is_empty());
}



void test_node_connect(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_NODE_CONNECT(TAG, SIDE, NODE_EL, NODE_TH, ...) \
    {                                                           \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);      \
        node_p node_top = node_branch_create(LAB(V, 2));        \
        node_p node_bot = node_branch_create(LAB(V, 1));        \
        node_connect(node_top, node_bot, SIDE);                 \
        assert(BRANCH(node_top)[ELSE] == NODE_EL);              \
        assert(BRANCH(node_top)[THEN] == NODE_TH);              \
        assert(list_head_immed(node_bot->lh, __VA_ARGS__));     \
        free(node_top);                                         \
        free(node_bot);                                         \
    }

    TEST_NODE_CONNECT(1, ELSE, node_bot, NULL, 1,
        LAB(V, 2), 1, node_top, 0
    );
    TEST_NODE_CONNECT(2, THEN, NULL, node_bot, 1,
        LAB(V, 2), 0, 1, node_top
    );

    #undef TEST_NODE_CONNECT

    #define TEST_NODE_CONNECT(TAG, SIDE)                    \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_top = node_branch_create(LAB(V, 2));    \
        node_p node_bot = node_branch_create(LAB(V, 1));    \
        node_connect(node_top, node_bot, SIDE);             \
        TEST_REVERT_OPEN                                    \
        node_connect(node_top, node_bot, SIDE);             \
        TEST_REVERT_CLOSE                                   \
        list_head_free(node_bot->lh);                       \
        free(node_top);                                     \
        free(node_bot);                                     \
    }

    TEST_NODE_CONNECT(3, ELSE);
    TEST_NODE_CONNECT(4, THEN);

    #undef TEST_NODE_CONNECT

    assert(clu_mem_is_empty());
}

void test_node_connect_both(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node_top = node_branch_create(LAB(V, 2));
    node_p node_el = node_branch_create(LAB(V, 1));
    node_p node_th = node_branch_create(LAB(V, 1));
    node_connect_both(node_top, node_el, node_th);
    assert(BRANCH(node_top)[ELSE] == node_el);
    assert(BRANCH(node_top)[THEN] == node_th);
    assert(list_head_immed(node_el->lh, 1,
        LAB(V, 2),  1, node_top, 0
    ));
    assert(list_head_immed(node_th->lh, 1,
        LAB(V, 2),  0, 1, node_top
    ));
    free(node_top);
    free(node_el);
    free(node_th);

    assert(clu_mem_is_empty());
}



void test_node_disconnect(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_NODE_DISCONNECT(TAG, SIDE)                 \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_top = node_branch_create(LAB(V, 2));    \
        node_p node_bot = node_branch_create(LAB(V, 1));    \
        node_connect(node_top, node_bot, SIDE);             \
        node_disconnect(node_top, SIDE);                    \
        assert(BRANCH(node_top)[ELSE] == NULL);             \
        assert(BRANCH(node_top)[THEN] == NULL);             \
        assert(list_head_immed(node_bot->lh, 0));           \
        free(node_top);                                     \
        free(node_bot);                                     \
    }

    TEST_NODE_DISCONNECT(1, ELSE);
    TEST_NODE_DISCONNECT(2, THEN);

    #undef TEST_NODE_DISCONNECT

    #define TEST_NODE_DISCONNECT(TAG, SIDE)                 \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        node_p node_top = node_branch_create(LAB(V, 2));    \
        node_p node_bot = node_branch_create(LAB(V, 1));    \
        TEST_REVERT_OPEN                                    \
        node_disconnect(node_top, SIDE);                    \
        TEST_REVERT_CLOSE                                   \
        free(node_top);                                     \
        free(node_bot);                                     \
    }

    TEST_NODE_DISCONNECT(3, ELSE);
    TEST_NODE_DISCONNECT(4, THEN);

    #undef TEST_NODE_DISCONNECT

    assert(clu_mem_is_empty());
}

void test_node_disconnect_both(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node_top = node_branch_create(LAB(V, 2));
    node_p node_el = node_branch_create(LAB(V, 1));
    node_p node_th = node_branch_create(LAB(V, 1));
    node_connect_both(node_top, node_el, node_th);
    node_disconnect_both(node_top);
    assert(BRANCH(node_top)[ELSE] == NULL);
    assert(BRANCH(node_top)[THEN] == NULL);
    assert(list_head_immed(node_el->lh, 0));
    assert(list_head_immed(node_th->lh, 0));
    free(node_top);
    free(node_el);
    free(node_th);

    assert(clu_mem_is_empty());
}



void test_node_merge(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s 1\t\t", __func__);
    node_p node_v1_1 = node_branch_create(LAB(V, 1));
    node_p node_v1_2 = node_branch_create(LAB(V, 1));
    node_p node_v2_1 = node_branch_create(LAB(V, 2));
    node_p node_v2_2 = node_branch_create(LAB(V, 2));
    node_p node_v3_1 = node_branch_create(LAB(V, 3));
    node_p node_v3_2 = node_branch_create(LAB(V, 3));
    node_connect(node_v3_1, node_v2_1, ELSE);
    node_connect(node_v3_2, node_v2_2, THEN);
    node_connect_both(node_v2_1, node_v1_1, node_v1_2);
    node_connect_both(node_v2_2, node_v1_1, node_v1_2);
    node_merge(node_v2_1, node_v2_2);
    assert(BRANCH(node_v3_1)[ELSE] == node_v2_1);
    assert(BRANCH(node_v3_2)[THEN] == node_v2_1);
    assert(list_head_immed(node_v2_1->lh, 1,
        LAB(V, 3),  1, node_v3_1, 1, node_v3_2
    ));
    assert(list_head_immed(node_v1_1->lh, 1,
        LAB(V, 2),  1, node_v2_1, 0
    ));
    assert(list_head_immed(node_v1_2->lh, 1,
        LAB(V, 2),  0, 1, node_v2_1
    ));
    free(node_v1_1);
    free(node_v1_2);
    free(node_v2_1);
    free(node_v3_1);
    free(node_v3_2);

    if(show) printf("\n\t\t%s 2\t\t", __func__);
    node_p node_amp = node_amp_create(AMPI(1, 2));
    node_p node_v2 = node_branch_create(LAB(V, 2));
    node_v3_1 = node_branch_create(LAB(V, 3));
    node_v3_2 = node_branch_create(LAB(V, 3));
    node_connect(node_v3_1, node_v2, ELSE);
    node_connect(node_v3_2, node_v2, THEN);
    node_connect_both(node_v2, node_amp, node_amp);
    node_merge(node_amp, node_v2);
    assert(BRANCH(node_v3_1)[ELSE] == node_amp);
    assert(BRANCH(node_v3_2)[THEN] == node_amp);
    assert(list_head_immed(node_amp->lh, 1,
        LAB(V, 3),  1, node_v3_1, 1, node_v3_2
    ));
    free(node_amp);
    free(node_v3_1);
    free(node_v3_2);

    if(show) printf("\n\t\t%s 3\t\t", __func__);
    node_p node_amp_1 = node_amp_create(AMPI(1, 2));
    node_p node_amp_2 = node_amp_create(AMPI(1, 2));
    node_v2 = node_branch_create(LAB(V, 2));
    node_connect_both(node_v2, node_amp_1, node_amp_2);
    node_merge(node_amp_1, node_amp_2);
    assert(BRANCH(node_v2)[ELSE] == node_amp_1);
    assert(BRANCH(node_v2)[THEN] == node_amp_1);
    assert(list_head_immed(node_amp_1->lh, 1,
        LAB(V, 2),  1, node_v2, 1, node_v2
    ));
    free(node_amp_1);
    free(node_v2);

    assert(clu_mem_is_empty());
}



void test_node()
{
    printf("\n%s\t\t", __func__);

    bool show = true;

    test_node_create_branch(show);
    test_node_create_amp(show);

    test_node_eq_amp(show);
    test_node_eq_el(show);
    test_node_eq_th(show);

    test_node_connect(show);
    test_node_connect_both(show);

    test_node_disconnect(show);
    test_node_disconnect_both(show);

    test_node_merge(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_node();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
