#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../label/struct.h"
#include "../../amp/struct.h"
#include "../../list/list_head/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"



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

    assert(mem_empty());
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

    assert(mem_empty());
}

void test_tree_copy()
{
    printf("\n\t%s\t\t", __func__);
    
    label_t amp, V1, V2;
    amp = LAB(0, 0);
    V1  = LAB(V, 1);
    V2  = LAB(V, 2);

    printf("\n\t\t%s 1\t\t", __func__);
    node_p n1 = tree_create(1, 
        1, AMP(0, 0),
        0
    );
    node_p n2 = tree_copy(n1);
    assert(tree(n1, n2));
    tree_free(n1);
    tree_free(n2);

    printf("\n\t\t%s 2\t\t", __func__);
    n1 = tree_create(1, 
        2, AMP(0, 0), AMP(0, 1),
        1,
        V1, 1, amp, 0, amp, 1
    );
    n2 = tree_copy(n1);
    assert(tree(n1, n2));
    tree_free(n1);
    tree_free(n2);

    printf("\n\t\t%s 3\t\t", __func__);
    n1 = tree_create(2, 
        2, AMP(0, 0), AMP(0, 1),
        2,
        V1, 1, amp, 0, amp, 1,
        V2, 1, amp, 0, V1, 0
    );
    n2 = tree_copy(n1);
    assert(tree(n1, n2));
    tree_free(n1);
    tree_free(n2);

    assert(mem_empty());
}

void test_tree()
{
    printf("\n%s\t\t", __func__);

    test_tree_enlist();
    test_tree_assert();
    test_tree_copy();

    assert(mem_empty());
}


int main() 
{
    setbuf(stdout, NULL);
    test_tree();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
