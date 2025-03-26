#include <stdio.h>

#include "../debug.h"
#include "../../list/list_body/debug.h"
#include "../../list/list_head/debug.h"
#include "../../../mods/clu/header.h"



void test_node_create_str()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p ne = node_branch_create(&LAB(V, 2));

    assert(ne->lh == NULL);
    assert(ne->lab.cl == V);
    assert(ne->lab.lv == 2);
    assert(ND_STR(ne)->el == NULL);
    assert(ND_STR(ne)->th == NULL);

    free(ne);
    assert(clu_mem_is_empty());
}

void test_node_create_amp()
{
    printf("\n\t\t%s\t\t", __func__);

    amp_t amp = (amp_t){1, 2};
    node_p na = node_amp_create(&amp);
    
    assert(na->lh == NULL);
    assert(na->lab.cl == 0);
    assert(na->lab.lv == 0);
    assert(ND_AMP(na)->re == 1);
    assert(ND_AMP(na)->im == 2);

    free(na);
    assert(clu_mem_is_empty());
}

void test_node_life_cycle()
{
    printf("\n\t%s\t\t", __func__);

    test_node_create_str();
    test_node_create_amp();

    assert(clu_mem_is_empty());
}

void test_amp_eq()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p n1, n2;
    n1 = node_amp_create(&AMP(0, 0));
    n2 = node_amp_create(&AMP(0, 0));
    assert(node_amp_eq(n1, n2) == true);
    free(n2);

    n2 = node_amp_create(&AMP(0, 1));
    assert(node_amp_eq(n1, n2) == false);
    free(n1);
    free(n2);

    assert(clu_mem_is_empty());
}

void test_branch_eq()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p n0, n1, n2;
    n0 = node_amp_create(&AMP(0, 0));
    n1 = node_branch_create(&LAB(V, 1));
    n2 = node_branch_create(&LAB(V, 1));

    // typedef bool (*node_eq_f)(node_p, node_p);
    node_eq_f fn[] = {node_el_eq, node_th_eq};
    for(int side=0; side<2; side++)
    {
        assert(fn[side](n1, n2) == true);
        
        node_connect(n1, n0, side);
        assert(fn[side](n1, n2) == false);
        
        node_connect(n2, n0, side);
        assert(fn[side](n1, n2) == true);
    }
    node_free(n0);
    free(n1);
    free(n2);

    assert(clu_mem_is_empty());
}

void test_node_access()
{
    printf("\n\t%s\t\t", __func__);

    test_amp_eq();
    test_branch_eq();

    assert(clu_mem_is_empty());
}



void test_node_connect_one()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n = node_branch_create(&LAB(V, 2));
    node_p n_el = node_branch_create(&LAB(V, 1));
    node_connect(n, n_el, ELSE);
    assert(ND_STR(n)->el == n_el);
    assert(list_head(n_el->lh, 1, 
        LAB(V, 2), 1, n, 0
    ));
    
    node_p n_th = node_branch_create(&LAB(V, 1));
    node_connect(n, n_th, THEN);
    assert(ND_STR(n)->th == n_th);
    assert(list_head(n_th->lh, 1, 
        LAB(V, 2), 0, 1, n
    ));

    node_free(n_el);
    node_free(n_th);
    free(n);
    assert(clu_mem_is_empty());
}

void test_node_connect_both()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_branch_create(&LAB(V, 2));
    node_p n_el = node_branch_create(&LAB(V, 1));
    node_p n_th = node_branch_create(&LAB(V, 1));
    
    node_connect_both(n, n_el, n_th);
    assert(ND_STR(n)->el == n_el);
    assert(ND_STR(n)->th == n_th);
    assert(list_head(n_el->lh, 1, 
        LAB(V, 2), 1, n, 0
    ));
    assert(list_head(n_th->lh, 1, 
        LAB(V, 2), 0, 1, n
    ));

    node_free(n_el);
    node_free(n_th);
    free(n);
    assert(clu_mem_is_empty());
}

void test_node_connect()
{
    printf("\n\t\t%s\t\t", __func__);

    test_node_connect_one();
    test_node_connect_both();

    assert(clu_mem_is_empty());
}



void test_node_disconnect_one()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_branch_create(&LAB(V, 2));
    node_p n_el = node_branch_create(&LAB(V, 1));
    node_p n_th = node_branch_create(&LAB(V, 1));
    node_connect_both(n, n_el, n_th);

    node_disconnect(n, ELSE);
    assert(ND_STR(n)->el == NULL);
    assert(n_el->lh == NULL);
    
    node_disconnect(n, THEN);
    assert(ND_STR(n)->th == NULL);
    assert(n_th->lh == NULL);

    free(n_el);
    free(n_th);
    free(n);
    assert(clu_mem_is_empty());
}

void test_node_disconnect_both()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_branch_create(&LAB(V, 2));
    node_p n_el = node_branch_create(&LAB(V, 1));
    node_p n_th = node_branch_create(&LAB(V, 1));
    node_connect_both(n, n_el, n_th);

    node_disconnect_both(n);
    assert(ND_STR(n)->el == NULL);
    assert(ND_STR(n)->th == NULL);
    assert(n_el->lh == NULL);
    assert(n_th->lh == NULL);

    free(n_el);
    free(n_th);
    free(n);
    assert(clu_mem_is_empty());
}

void test_node_disconnect()
{
    printf("\n\t\t%s\t\t", __func__);

    test_node_disconnect_one();
    test_node_disconnect_both();

    assert(clu_mem_is_empty());
}



void test_node_merge()
{
    printf("\n\t\t%s\t\t", __func__);

    printf("\n\t\t\t%s 1\t\t", __func__);
    node_p n1 = node_amp_create(&(amp_t){0, 0});
    node_p n2 = node_amp_create(&(amp_t){0, 0});
    node_merge(n1, n2);

    printf("\n\t\t\t%s 2\t\t", __func__);
    node_p N1[] = {
        node_branch_create(&LAB(V, 1)),
        node_branch_create(&LAB(V, 1)),
        node_branch_create(&LAB(V, 2)),
        node_branch_create(&LAB(V, 2)),
    };
    n2 = node_amp_create(&(amp_t){0, 0});
    node_connect(N1[0], n2, ELSE);
    node_connect(N1[0], n2, THEN);
    for(int i=1; i<4; i++)
        node_connect(N1[i], n2, i&1);
    node_merge(n1, n2);
    assert(list_head(n1->lh, 2,
        LAB(V, 1), 1, N1[0], 2, N1[1], N1[0], 
        LAB(V, 2), 1, N1[2], 1, N1[3]
    ));
    for(list_head_p lh = n1->lh; lh; lh = lh->lh)
    for(int side=0; side<2; side++)
    for(list_body_p lb = lh->lb[side]; lb; lb = lb->lb)
        assert(V_STR(lb->n)[side] == n1);

    printf("\n\t\t\t%s 3\t\t", __func__);
    node_p N2[] = {
        node_branch_create(&LAB(V, 1)),
        node_branch_create(&LAB(V, 1)),
        node_branch_create(&LAB(V, 2)),
        node_branch_create(&LAB(V, 2)),
    };
    n2 = node_amp_create(&(amp_t){0, 0});
    for(int i=0; i<4; i++)
        node_connect(N2[i], n2, i&1);
    node_merge(n1, n2);
    assert(list_head(n1->lh, 2,
        LAB(V, 1), 2, N2[0], N1[0], 3, N2[1], N1[1], N1[0], 
        LAB(V, 2), 2, N2[2], N1[2], 2, N2[3], N1[3]
    ));
    for(list_head_p lh = n1->lh; lh; lh = lh->lh)
    for(int side=0; side<2; side++)
    for(list_body_p lb = lh->lb[side]; lb; lb = lb->lb)
        assert(V_STR(lb->n)[side] == n1);

    for(int i=0; i<4; i++)
    {
        free(N1[i]);
        free(N2[i]);
    }
    node_free(n1);

    assert(clu_mem_is_empty());
}

void test_node_connection()
{
    printf("\n\t%s\t\t", __func__);

    test_node_connect();
    test_node_disconnect();
    test_node_merge();

    assert(clu_mem_is_empty());
}



void test_node()
{
    printf("\n%s\t\t", __func__);

    test_node_life_cycle();
    test_node_access();
    test_node_connection();

    assert(clu_mem_is_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
