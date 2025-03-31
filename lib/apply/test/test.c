#include <stdio.h>
#include <assert.h>

#include "../debug.h"
#include "../../node/debug.h"
#include "../../../mods/clu/header.h"

void test_apply_create()
{
    printf("\n\t%s\t\t", __func__);

    apply_p a = apply_create(ND(1), ND(2));
    assert(a->n  == NULL);
    assert(a->n1 == ND(1));
    assert(a->n2 == ND(2));
    assert(a->el == NULL);
    assert(a->th == NULL);
    assert(a->a1 == NULL);
    assert(a->a2 == NULL);
    free(a);

    assert(clu_mem_is_empty());
}

void test_apply()
{
    printf("\n%s\t\t", __func__);

    test_apply_create();

    assert(clu_mem_is_empty());
}


int main() 
{
    setbuf(stdout, NULL);
    test_apply();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
