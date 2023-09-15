#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../list/list_head/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"



void test_node_create_str()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p ne = node_str_create(&(label_t){V, 2});

    assert(LB(ne)->n  == NULL);
    assert(LB(ne)->lb == NULL);
    assert(LH(ne)->lh == NULL);
    assert(ne->lab.cl == V);
    assert(ne->lab.lv == 2);
    assert(NODE_STR(ne)->el == NULL);
    assert(NODE_STR(ne)->th == NULL);

    free(ne);
    assert(mem_empty());
}

void test_node_create_amp()
{
    printf("\n\t\t%s\t\t", __func__);

    amp_t amp = (amp_t){1, 2};
    node_p na = node_amp_create(&amp);
    
    assert(LB(na)->n  == NULL);
    assert(LB(na)->lb == NULL);
    assert(LH(na)->lh == NULL);
    assert(na->lab.cl == 0);
    assert(na->lab.lv == 0);
    assert(NODE_AMP(na)->re == 1);
    assert(NODE_AMP(na)->im == 2);

    free(na);
    assert(mem_empty());
}

void test_node_create()
{
    printf("\n\t%s\t\t", __func__);

    test_node_create_str();
    test_node_create_amp();

    assert(mem_empty());
}



void test_node_connect_one()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n = node_str_create(&(label_t){V, 2});
    
    node_p n_el = node_str_create(&(label_t){V, 1});
    node_connect(n, n_el, ELSE);
    assert(NODE_STR(n)->el == n_el);
    assert(LB(n_el)->n == n);
    
    node_p n_th = node_str_create(&(label_t){V, 1});
    node_connect(n, n_th, THEN);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_th)->n == n);

    free(n_el);
    free(n_th);
    free(n);
    assert(mem_empty());
}

void test_node_connect_both()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_str_create(&(label_t){V, 2});
    node_p n_el = node_str_create(&(label_t){V, 1});
    node_p n_th = node_str_create(&(label_t){V, 1});
    
    node_connect_both(n, n_el, n_th);
    assert(NODE_STR(n)->el == n_el);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_el)->n == n);
    assert(LB(n_th)->n == n);

    free(n_el);
    free(n_th);
    free(n);
    assert(mem_empty());
}

void test_node_connect()
{
    printf("\n\t\t%s\t\t", __func__);

    test_node_connect_one();
    test_node_connect_both();

    assert(mem_empty());
}



void test_node_disconnect_one()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_str_create(&(label_t){V, 2});
    node_p n_el = node_str_create(&(label_t){V, 1});
    node_p n_th = node_str_create(&(label_t){V, 1});
    node_connect_both(n, n_el, n_th);

    node_disconnect(n, n_el);
    assert(NODE_STR(n)->el == NULL);
    assert(LB(n_el)->n == NULL);
    
    node_disconnect(n, n_th);
    assert(NODE_STR(n)->th == NULL);
    assert(LB(n_th)->n == NULL);

    free(n_el);
    free(n_th);
    free(n);
    assert(mem_empty());
}

void test_node_disconnect_both()
{
    printf("\n\t\t\t%s\t\t", __func__);

    node_p n    = node_str_create(&(label_t){V, 2});
    node_p n_el = node_str_create(&(label_t){V, 1});
    node_p n_th = node_str_create(&(label_t){V, 1});
    node_connect_both(n, n_el, n_th);

    node_disconnect_both(n);
    assert(NODE_STR(n)->el == NULL);
    assert(NODE_STR(n)->th == NULL);
    assert(LB(n_el)->n == NULL);
    assert(LB(n_th)->n == NULL);

    free(n_el);
    free(n_th);
    free(n);
    assert(mem_empty());
}

void test_node_disconnect()
{
    printf("\n\t\t%s\t\t", __func__);

    test_node_disconnect_one();
    test_node_disconnect_both();

    assert(mem_empty());
}


void test_node_merge()
{
    printf("\n\t\t%s\t\t", __func__);

    node_p n1 = node_amp_create(&(amp_t){0, 0});
    node_p n2 = node_amp_create(&(amp_t){0, 0});
    node_merge(n1, n2);

    node_p N1[] = {
        node_str_create(&(label_t){V, 1}),
        node_str_create(&(label_t){V, 1}),
        node_str_create(&(label_t){V, 2}),
        node_str_create(&(label_t){V, 2}),
    };
    n2 = node_amp_create(&(amp_t){0, 0});
    node_connect(N1[0], n2, ELSE);
    node_connect(N1[0], n2, THEN);
    for(int i=1; i<4; i++)
        node_connect(N1[i], n2, i&1);

    node_merge(n1, n2);
    assert(list_head_vector(LH(n1), 2, 3, N1[0], N1[1], N1[0], 2, N1[2], N1[3]));

    node_p N2[] = {
        node_str_create(&(label_t){V, 1}),
        node_str_create(&(label_t){V, 1}),
        node_str_create(&(label_t){V, 2}),
        node_str_create(&(label_t){V, 2}),
    };
    n2 = node_amp_create(&(amp_t){0, 0});
    for(int i=0; i<4; i++)
        node_connect(N2[i], n2, i&1);

    node_merge(n1, n2);

    assert(list_head_vector(LH(n1), 2, 
        5, N1[0], N1[1], N1[0], N2[0], N2[1],
        4, N1[2], N1[3], N2[2], N2[3]
    ));

    for(int i=0; i<4; i++)
    {
        free(N1[i]);
        free(N2[i]);
    }
    list_head_free(LH(n1));

    assert(mem_empty());
}



void test_node_connection()
{
    printf("\n\t%s\t\t", __func__);

    test_node_connect();
    test_node_disconnect();
    test_node_merge();

    assert(mem_empty());
}



void test_node()
{
    printf("\n%s\t\t", __func__);

    test_node_create();
    test_node_connection();

    assert(mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
