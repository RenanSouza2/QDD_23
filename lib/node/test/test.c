#include <stdio.h>
#include <assert.h>

#include "../debug.h"



void test_node_create_str()
{
    printf("\n\t\ttest node create str\t\t");

    node_p ne = node_str_create(V, 2);

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

    node_p ne = node_amp_create(1, 2);
    
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



void test_node_connection_one()
{
    printf("\n\t\ttest node connection one\t\t");

    node_p n = node_str_create(V, 2);
    
    node_p n_el = node_str_create(V,1);
    node_connect(n, n_el, ELSE);
    assert(NODE_STR(n)->el == n_el);
    assert(LB(n_el)->n == n);
    
    node_p n_th = node_str_create(V,1);
    node_connect(n, n_th, THEN);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_th)->n == n);
}

void test_node_connection_both()
{
    printf("\n\t\ttest node connection both\t\t");

    node_p n   = node_str_create(V, 2);
    node_p n_el = node_str_create(V,1);
    node_p n_th = node_str_create(V,1);
    
    node_connect_both(n, n_el, n_th);
    assert(NODE_STR(n)->el == n_el);
    assert(NODE_STR(n)->th == n_th);
    assert(LB(n_el)->n == n);
    assert(LB(n_th)->n == n);
}

void test_node_connection()
{
    printf("\n\ttest node connection\t\t");

    test_node_connection_one();
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
