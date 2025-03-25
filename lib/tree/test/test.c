#include <stdio.h>

#include "../debug.h"
#include "../../label/struct.h"
#include "../../amp/struct.h"
#include "../../list/list_head/debug.h"
#include "../../../mods/clu/header.h"



void test_tree_enlist()
{
    printf("\n\t%s\t\t", __func__);

    node_p n  = node_str_create(&LAB(V, 1));
    node_p n1 = node_amp_create(&(amp_t){0, 0});
    node_p n2 = node_amp_create(&(amp_t){0, 1});
    node_connect_both(n, n1, n2);

    list_head_p lh = tree_enlist(n);
    assert(list_head(lh, 2, 
        LAB(0, 0), 2, n2, n1, 0,
        LAB(V, 1), 1, n, 0
    ));
    tree_free(n);
    list_head_free(lh);

    assert(clu_mem_is_empty());
}

void test_tree_assert()
{
    printf("\n\t%s\t\t", __func__);

    printf("\n\t\t%s 1\t\t", __func__);
    node_p na, n1, n2;
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 1));
    na = node_str_create(&LAB(V, 1));
    node_connect_both(na, n1, n2);
    
    node_p nb;
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 1));
    nb = node_str_create(&LAB(V, 1));
    node_connect_both(nb, n1, n2);

    assert(tree(na, nb));
    tree_free(na);
    tree_free(nb);

    printf("\n\t\t%s 2\t\t", __func__);
    node_p n3;
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 1));
    n3 = node_str_create(&LAB(V, 1));
    node_connect_both(n3, n1, n2);

    node_p n4;
    n2 = node_amp_create(&AMP(0, 2));
    n4 = node_str_create(&LAB(V, 1));
    node_connect_both(n4, n1, n2);

    na = node_str_create(&LAB(V, 2));
    node_connect_both(na, n3, n4);
    
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 2));
    n4 = node_str_create(&LAB(V, 1));
    node_connect_both(n4, n1, n2);

    n2 = node_amp_create(&AMP(0, 1));
    n3 = node_str_create(&LAB(V, 1));
    node_connect_both(n3, n1, n2);

    nb = node_str_create(&LAB(V, 2));
    node_connect_both(nb, n3, n4);
    
    assert(tree(na, nb));
    tree_free(na);
    tree_free(nb);

    assert(clu_mem_is_empty());
}

void test_tree()
{
    printf("\n%s\t\t", __func__);

    test_tree_enlist();
    test_tree_assert();

    assert(clu_mem_is_empty());
}


int main() 
{
    setbuf(stdout, NULL);
    test_tree();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
