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

    CLU_REGISTER(LH(2));

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

    CLU_UNREGISTER(LH(2));

    assert(clu_mem_is_empty());
}

void test_list_head_create(bool show)
{
    printf("\n\t%s\t\t", __func__);

    CLU_REGISTER(LH(2));

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

    CLU_UNREGISTER(LH(2));

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

    assert(clu_mem_is_empty());
}



void test_list_head()
{
    printf("\n%s\t\t", __func__);

    bool show = true;

    test_list_head_create_body(show);
    test_list_head_create(show);
    test_list_head_pop(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    test_list_head();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
