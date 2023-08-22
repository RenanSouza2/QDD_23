#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_create_str()
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

void test_create_amp()
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


void test_create()
{
    printf("\n\ttest node create\t\t");

    test_create_str();
    test_create_amp();
}

void test_node()
{
    printf("\ntest node library\t\t");

    test_create();
}

int main() 
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
