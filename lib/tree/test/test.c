#include "../debug.h"
#include "../../amp/debug.h"
#include "../../label/debug.h"
#include "../../list/body/debug.h"
#include "../../list/head/debug.h"
#include "../../macros/test.h"
#include "../../../mods/clu/header.h"



void test_tree_enlist(bool show)
{
    printf("\n\t%s\t\t", __func__);

    if(show) printf("\n\t\t%s  1\t\t", __func__);
    node_p node_amp = node_amp_create(AMPI(1, 2));
    list_head_p lh = tree_enlist(node_amp);
    assert(list_head_immed(lh, 1,
        LAB(0, 0), 1, node_amp, 0
    ));
    tree_free(node_amp);

    if(show) printf("\n\t\t%s  2\t\t", __func__);
    node_p node_amp_1 = node_amp_create(AMPI(1, 2));
    node_p node_amp_2 = node_amp_create(AMPI(1, 3));
    node_p node_v1 = node_branch_create(LAB(V, 1));
    node_connect_both(node_v1, node_amp_1, node_amp_2);
    lh = tree_enlist(node_v1);
    assert(list_head_immed(lh, 2,
        LAB(0, 0), 2, node_amp_2, node_amp_1, 0,
        LAB(V, 1), 1, node_v1, 0
    ));
    tree_free(node_v1);

    if(show) printf("\n\t\t%s  3\t\t", __func__);
    node_amp_1 = node_amp_create(AMPI(1, 2));
    node_amp_2 = node_amp_create(AMPI(1, 3));
    node_v1 = node_branch_create(LAB(V, 1));
    node_p node_v2 = node_branch_create(LAB(V, 2));
    node_connect_both(node_v2, node_amp_1, node_v1);
    node_connect_both(node_v1, node_amp_1, node_amp_2);
    lh = tree_enlist(node_v2);
    assert(list_head_immed(lh, 3,
        LAB(0, 0), 2, node_amp_2, node_amp_1, 0,
        LAB(V, 1), 1, node_v1, 0,
        LAB(V, 2), 1, node_v2, 0
    ));
    tree_free(node_v2);

    assert(clu_mem_is_empty());
}



void test_list_body_reduce_repeated(bool show)
{
    TEST_FN;

    TEST_CASE_OPEN(1);
    {
        node_p node_amp[] = {
            node_amp_create(AMPI(1, 2))
        };
        list_body_p lb = list_body_create_immed(1, node_amp[0]);
        list_body_p lb_res = list_body_reduce_repeated(lb, node_eq_amp, true);
        assert(list_body_immed(lb, 1, node_amp[0]));
        assert(list_body_immed(lb_res, 0));
        free(node_amp[0]);
    }
    TEST_CASE_CLOSE

    TEST_CASE_OPEN(2);
    {
        node_p node_amp[] = {
            node_amp_create(AMPI(1, 2))
        };
        list_body_p lb = list_body_create_immed(1, node_amp[0]);
        list_body_p lb_res = list_body_reduce_repeated(lb, node_eq_amp, true);
        assert(list_body_immed(lb, 1, node_amp[0]));
        assert(list_body_immed(lb_res, 0));
        free(node_amp[0]);
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}



void test_tree()
{
    printf("\n%s\t\t", __func__);

    bool show = true;

    test_tree_enlist(show);

    test_list_body_reduce_repeated(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_tree();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
