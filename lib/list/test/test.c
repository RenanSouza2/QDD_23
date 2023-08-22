#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"

void test_list_body_create()
{
    printf("\n\t\ttest list body create\t\t");

    list_body_p  lb = list_body_create(NODE(1), LB(2));
    assert(lb->n  == NODE(1));
    assert(lb->lb == LB(2));
}

void test_list_create()
{
    printf("\n\ttest lib create\t\t");

    test_list_body_create();
}

void test_list()
{
    printf("\ntest lib library\t\t");

    test_list_create();
}

int main() 
{
    setbuf(stdout, NULL);
    test_list();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
