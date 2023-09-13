#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/struct.h"
#include "../../amp/struct.h"
#include "../../list/list_head/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void test_tree_enlist()
{
    printf("\n\t%s\t\t", __func__);

    node_p n  = node_str_create(&(label_t){V, 1});
    node_p n1 = node_amp_create(&(amp_t){0, 0});
    node_p n2 = node_amp_create(&(amp_t){0, 1});
    node_connect_both(n, n1, n2);

    list_head_p lh = tree_enlist(n);
    assert(list_head_vector(lh, 2, 2, n1, n2, 1, n));
    tree_free(n);
    list_head_free(lh);

    assert(mem_empty());
}

void test_tree()
{
    printf("\n%s\t\t", __func__);

    test_tree_enlist();
}


int main() 
{
    setbuf(stdout, NULL);
    test_tree();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
