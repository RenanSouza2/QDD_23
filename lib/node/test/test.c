#include <stdio.h>

#include "../debug.h"
#include "../../amp/debug.h"
#include "../../label/debug.h"
#include "../../list/body/debug.h"
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



// void test_node_connect_one()
// {
//     printf("\n\t\t\t%s\t\t", __func__);

//     node_p n = node_branch_create(&LAB(V, 2));
//     node_p n_el = node_branch_create(&LAB(V, 1));
//     node_connect(n, n_el, ELSE);
//     assert(ND_STR(n)->el == n_el);
//     assert(list_head(n_el->lh, 1,
//         LAB(V, 2), 1, n, 0
//     ));

//     node_p n_th = node_branch_create(&LAB(V, 1));
//     node_connect(n, n_th, THEN);
//     assert(ND_STR(n)->th == n_th);
//     assert(list_head(n_th->lh, 1,
//         LAB(V, 2), 0, 1, n
//     ));

//     free(n_el);
//     free(n_th);
//     free(n);
//     assert(clu_mem_is_empty());
// }

// void test_node_connect_both()
// {
//     printf("\n\t\t\t%s\t\t", __func__);

//     node_p n    = node_branch_create(&LAB(V, 2));
//     node_p n_el = node_branch_create(&LAB(V, 1));
//     node_p n_th = node_branch_create(&LAB(V, 1));

//     node_connect_both(n, n_el, n_th);
//     assert(ND_STR(n)->el == n_el);
//     assert(ND_STR(n)->th == n_th);
//     assert(list_head(n_el->lh, 1,
//         LAB(V, 2), 1, n, 0
//     ));
//     assert(list_head(n_th->lh, 1,
//         LAB(V, 2), 0, 1, n
//     ));

//     free(n_el);
//     free(n_th);
//     free(n);
//     assert(clu_mem_is_empty());
// }



// void test_node_disconnect_one()
// {
//     printf("\n\t\t\t%s\t\t", __func__);

//     node_p n    = node_branch_create(&LAB(V, 2));
//     node_p n_el = node_branch_create(&LAB(V, 1));
//     node_p n_th = node_branch_create(&LAB(V, 1));
//     node_connect_both(n, n_el, n_th);

//     node_disconnect(n, ELSE);
//     assert(ND_STR(n)->el == NULL);
//     assert(n_el->lh == NULL);

//     node_disconnect(n, THEN);
//     assert(ND_STR(n)->th == NULL);
//     assert(n_th->lh == NULL);

//     free(n_el);
//     free(n_th);
//     free(n);
//     assert(clu_mem_is_empty());
// }

// void test_node_disconnect_both()
// {
//     printf("\n\t\t\t%s\t\t", __func__);

//     node_p n    = node_branch_create(&LAB(V, 2));
//     node_p n_el = node_branch_create(&LAB(V, 1));
//     node_p n_th = node_branch_create(&LAB(V, 1));
//     node_connect_both(n, n_el, n_th);

//     node_disconnect_both(n);
//     assert(ND_STR(n)->el == NULL);
//     assert(ND_STR(n)->th == NULL);
//     assert(n_el->lh == NULL);
//     assert(n_th->lh == NULL);

//     free(n_el);
//     free(n_th);
//     free(n);
//     assert(clu_mem_is_empty());
// }



// void test_node_merge()
// {
//     printf("\n\t\t%s\t\t", __func__);

//     printf("\n\t\t\t%s 1\t\t", __func__);
//     node_p n1 = node_amp_create(&(amp_t){0, 0});
//     node_p n2 = node_amp_create(&(amp_t){0, 0});
//     node_merge(n1, n2);

//     printf("\n\t\t\t%s 2\t\t", __func__);
//     node_p N1[] = {
//         node_branch_create(&LAB(V, 1)),
//         node_branch_create(&LAB(V, 1)),
//         node_branch_create(&LAB(V, 2)),
//         node_branch_create(&LAB(V, 2)),
//     };
//     n2 = node_amp_create(&(amp_t){0, 0});
//     node_connect(N1[0], n2, ELSE);
//     node_connect(N1[0], n2, THEN);
//     for(int i=1; i<4; i++)
//         node_connect(N1[i], n2, i&1);
//     node_merge(n1, n2);
//     assert(list_head(n1->lh, 2,
//         LAB(V, 1), 1, N1[0], 2, N1[1], N1[0],
//         LAB(V, 2), 1, N1[2], 1, N1[3]
//     ));
//     for(list_head_p lh = n1->lh; lh; lh = lh->lh)
//     for(int side=0; side<2; side++)
//     for(list_body_p lb = lh->lb[side]; lb; lb = lb->lb)
//         assert(V_STR(lb->n)[side] == n1);

//     printf("\n\t\t\t%s 3\t\t", __func__);
//     node_p N2[] = {
//         node_branch_create(&LAB(V, 1)),
//         node_branch_create(&LAB(V, 1)),
//         node_branch_create(&LAB(V, 2)),
//         node_branch_create(&LAB(V, 2)),
//     };
//     n2 = node_amp_create(&(amp_t){0, 0});
//     for(int i=0; i<4; i++)
//         node_connect(N2[i], n2, i&1);
//     node_merge(n1, n2);
//     assert(list_head(n1->lh, 2,
//         LAB(V, 1), 2, N2[0], N1[0], 3, N2[1], N1[1], N1[0],
//         LAB(V, 2), 2, N2[2], N1[2], 2, N2[3], N1[3]
//     ));
//     for(list_head_p lh = n1->lh; lh; lh = lh->lh)
//     for(int side=0; side<2; side++)
//     for(list_body_p lb = lh->lb[side]; lb; lb = lb->lb)
//         assert(V_STR(lb->n)[side] == n1);

//     for(int i=0; i<4; i++)
//     {
//         free(N1[i]);
//         free(N2[i]);
//     }
//     free(n1);

//     assert(clu_mem_is_empty());
// }




void test_node()
{
    printf("\n%s\t\t", __func__);

    bool show = true;

    test_node_create_branch(show);
    test_node_create_amp(show);

    test_node_eq_amp(show);
    test_node_eq_el(show);
    test_node_eq_th(show);

    // test_node_connect_one();
    // test_node_connect_both();

    // test_node_disconnect_one();
    // test_node_disconnect_both();

    // test_node_merge();

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
