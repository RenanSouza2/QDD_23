#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"
#include "../../tree/debug.h"
#include "../../list/list_head/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"



void test_create()
{
    printf("\n\t%s\t\t", __func__);
    
    qdd_p q = qdd_create(ND(1), LB(2), 3);
    assert(LB(q)->n == ND(1));
    assert(LB(q)->lb == LB(2));
    assert(q->qbits == 3);
    free(q);

    assert(mem_empty());
}

void test_vector()
{
    printf("\n\t%s\t\t", __func__);
    
    qdd_p q = qdd_create_vector(1, (amp_t[]){{0, 0}, {0, 1}});
    qdd_free(q);

    assert(mem_empty());
}

void test_qdd()
{
    printf("\n%s\t\t", __func__);

    test_create();
    test_vector();

    assert(mem_empty());
}


int main() 
{
    setbuf(stdout, NULL);
    test_qdd();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
