#include "../debug.h"
#include "../../node/debug.h"
#include "../../macros/test.h"
#include "../../../mods/clu/header.h"



void test_apply_create(bool show)
{
    TEST_FN

    TEST_CASE_OPEN(1)
    {
        apply_p a = apply_create(ND(1), ND(2));
        assert(a->n  == NULL);
        assert(a->n1 == ND(1));
        assert(a->n2 == ND(2));
        assert(a->el == NULL);
        assert(a->th == NULL);
        assert(a->a1 == NULL);
        assert(a->a2 == NULL);
        free(a);
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}

void test_apply_insert(bool show)
{
    TEST_FN

    TEST_CASE_OPEN(1)
    {
        apply_p a = NULL;
        apply_insert(&a, ND(1), ND(2));
        assert(a != NULL);
        assert(a->n1 == ND(1));
        assert(a->n2 == ND(2));
        apply_free(a);
    }
    TEST_CASE_CLOSE

    TEST_CASE_OPEN(2)
    {
        apply_p a = NULL;
        apply_insert(&a, ND(1), ND(2));
        assert(a != NULL);
        assert(a->n1 == ND(1));
        assert(a->n2 == ND(2));
        apply_free(a);
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}



void test_apply()
{
    TEST_LIB

    bool show = true;

    test_apply_create(show);
    test_apply_insert(show);

    assert(clu_mem_is_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_apply();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
