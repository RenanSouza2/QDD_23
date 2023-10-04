#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

// apply_p apply_create(node_p n1, node_p n2)
void test_apply_create()
{
    printf("\n%s\t\t", __func__);

    apply_p a = apply_create(ND(1), ND(2));
    assert(a);

    assert(mem_empty());
}

void test_apply()
{
    printf("\n%s\t\t", __func__);

    test_apply_create();

    assert(mem_empty());
}


int main() 
{
    setbuf(stdout, NULL);
    test_apply();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
