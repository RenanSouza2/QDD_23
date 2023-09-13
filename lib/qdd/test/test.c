#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"
#include "../../list/list_head/debug.h"

void test_create()
{
    printf("\n\t%s\t\t", __func__);
    
    qdd_p q = qdd_create(NODE(1), LB(2), 3);
    assert(LB(q)->n == NODE(1));
    assert(LB(q)->lb == LB(2));
    assert(q->qbits == 3);


}

void test_qdd()
{
    printf("\n%s\t\t", __func__);

    test_create();
}


int main() 
{
    setbuf(stdout, NULL);
    test_qdd();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
