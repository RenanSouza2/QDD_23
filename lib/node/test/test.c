#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_create_str()
{
    printf("\n\t\ttest node create str");

    node_p ne = node_str_create(V, 2);

    assert(LB(ne)->n  == NULL);
    assert(LB(ne)->lb == NULL);
    assert(LH(ne)->lh == NULL);
    assert(NODE_LAB(ne)->cl == V);
    assert(NODE_LAB(ne)->lv == 2);
    assert(NODE_STR(ne)->el == NULL);
    assert(NODE_STR(ne)->th == NULL);
}

void test_create()
{
    printf("\n\ttest node create");

    test_create_str();
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
