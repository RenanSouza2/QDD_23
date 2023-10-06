#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void test_apply_create()
{
    printf("\n\t%s\t\t", __func__);

    apply_p a = apply_create(ND(1), ND(2), AP(3));
    assert(a->n  == NULL);
    assert(a->n1 == ND(1));
    assert(a->n2 == ND(2));
    assert(a->n  == NULL);
    assert(a->el == NULL);
    assert(a->th == NULL);
    free(a);

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
