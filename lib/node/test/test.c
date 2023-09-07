#include <stdio.h>
#include <assert.h>

#include "../debug.h"


node_p node_str_create_test(int const cl, int const lv)
{
    label_t const lab = (label_t){cl, lv};
    return node_str_create(&lab);
}


void test_node_create_str()
{
    printf("\n\t\ttest node create str\t\t");

    node_p ne = node_str_create_test(V, 2);

    assert(LB(ne)->n  == NULL);
    assert(LB(ne)->lb == NULL);
    assert(LH(ne)->lh == NULL);
    assert(ne->lab.cl == V);
    assert(ne->lab.lv == 2);
    assert(NODE_STR(ne)->el == NULL);
    assert(NODE_STR(ne)->th == NULL);
}

void test_node_create_amp()
{
    printf("\n\t\ttest node create amp\t\t");

    amp_t amp = (amp_t){1, 2};
    node_p ne = node_amp_create(&amp);
    
    assert(LB(ne)->n  == NULL);
    assert(LB(ne)->lb == NULL);
    assert(LH(ne)->lh == NULL);
    assert(ne->lab.cl == 0);
    assert(ne->lab.lv == 0);
    assert(NODE_AMP(ne)->re == 1);
    assert(NODE_AMP(ne)->im == 2);
}

void test_node_create()
{
    printf("\n\ttest node create\t\t");

    test_node_create_str();
    test_node_create_amp();
}



void test_node_connect_one()
{
    printf("\n\t\t\ttest node connect one\t\t");

    node_p n = node_str_create_test(V, 2);
    
    node_p n_el = node_str_create_test(V,1);
    node_connect(n, n_el, ELSE);
    assert(NODE_STR(n)->el == n_el);
    assert(LB(n_el)->n == n);
    
    node_p n_th = node_str_create_test(V,1);
    node_connect(n, n_th, THEN);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_th)->n == n);
}

void test_node_connect_both()
{
    printf("\n\t\t\ttest node connect both\t\t");

    node_p n   = node_str_create_test(V, 2);
    node_p n_el = node_str_create_test(V,1);
    node_p n_th = node_str_create_test(V,1);
    
    node_connect_both(n, n_el, n_th);
    assert(NODE_STR(n)->el == n_el);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_el)->n == n);
    assert(LB(n_th)->n == n);
}

void test_node_connect()
{
    printf("\n\t\ttest node connect\t\t");

    test_node_connect_one();
    test_node_connect_both();
}



void test_node_disconnect_one()
{
    printf("\n\t\t\ttest node disconnect one\t\t");

    node_p n   = node_str_create_test(V, 2);
    node_p n_el = node_str_create_test(V,1);
    node_p n_th = node_str_create_test(V,1);
    node_connect_both(n, n_el, n_th);

    node_disconnect(n, n_el);
    assert(NODE_STR(n)->el == NULL);
    assert(LB(n_el)->n == NULL);
    
    node_disconnect(n, n_th);
    assert(NODE_STR(n)->th == NULL);
    assert(LB(n_th)->n == NULL);
}

void test_node_disconnect_both()
{
    printf("\n\t\t\ttest node disconnect both\t\t");

    node_p n   = node_str_create_test(V, 2);
    node_p n_el = node_str_create_test(V,1);
    node_p n_th = node_str_create_test(V,1);
    node_connect_both(n, n_el, n_th);

    node_disconnect_both(n);
    assert(NODE_STR(n)->el == NULL);
    assert(NODE_STR(n)->th == NULL);
    assert(LB(n_el)->n == NULL);
    assert(LB(n_th)->n == NULL);
}

void test_node_disconnect()
{
    printf("\n\t\ttest node disconnect\t\t");

    test_node_disconnect_one();
    test_node_disconnect_both();
}



void test_node_connection()
{
    printf("\n\ttest node connection\t\t");

    test_node_connect();
    test_node_disconnect();
}



void test_node()
{
    printf("\ntest node library\t\t");

    test_node_create();
    test_node_connection();
}



int main() 
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
