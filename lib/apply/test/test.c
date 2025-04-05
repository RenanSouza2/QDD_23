#include "../debug.h"
#include "../../node/debug.h"
#include "../../macros/test.h"
#include "../../utils/debug.h"
#include "../../../mods/clu/header.h"



void test_apply_create(bool show)
{
    TEST_FN

    TEST_CASE_OPEN(1)
    {
        CLU_HANDLER_REGISTER(ND(1));
        CLU_HANDLER_REGISTER(ND(2));
        
        apply_p a = apply_create(ND(1), ND(2));
        assert(a->n  == NULL);
        assert(a->n1 == ND(1));
        assert(a->n2 == ND(2));
        assert(a->el == NULL);
        assert(a->th == NULL);
        assert(a->a1 == NULL);
        assert(a->a2 == NULL);
        free(a);
        
        CLU_HANDLER_UNREGISTER(ND(1));
        CLU_HANDLER_UNREGISTER(ND(2));
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}

void test_apply_insert(bool show)
{
    TEST_FN
    
    #define TEST_APPLY_INSERT(TAG, NODE_1, NODE_2, APPLY_IN, APPLY_OUT) \
    {                                                                   \
        TEST_CASE_OPEN(TAG)                                             \
        {                                                               \
            CLU_HANDLER_REGISTER(NODE_1);                               \
            CLU_HANDLER_REGISTER(NODE_2);                               \
            apply_p a_in = apply_create_immed APPLY_IN;                 \
            apply_p a_res = apply_insert(&a_in, NODE_1, NODE_2);        \
            apply_p a_out = apply_create_immed APPLY_OUT;               \
            CLU_HANDLER_VALIDATE(a_res);                                \
            assert(handler(a_res->n1, NODE_1));                         \
            assert(handler(a_res->n2, NODE_2));                         \
            assert(apply(a_in, a_out));                                 \
            CLU_HANDLER_UNREGISTER(NODE_1);                             \
            CLU_HANDLER_UNREGISTER(NODE_2);                             \
        }                                                               \
        TEST_CASE_CLOSE                                                 \
    }

    TEST_APPLY_INSERT(1, ND(1), ND(2),
        (0),
        (1, ND(1), ND(2), 0, 0, 0, 0)
    );
    TEST_APPLY_INSERT(2, ND(1), ND(2),
        (1, ND(1), ND(2), 0, 0, 0, 0),
        (1, ND(1), ND(2), 0, 0, 0, 0)
    );
    TEST_APPLY_INSERT(2, ND(3), ND(5),
        (1, ND(2), ND(5), 0, 0, 0, 0),
        (   
            2,
            ND(2), ND(5), 0, 0, 0, 2,
            ND(3), ND(5), 0, 0, 0, 0
        )
    );

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
    TEST_TIMEOUT_OPEN(30) // TODO
    test_apply();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
