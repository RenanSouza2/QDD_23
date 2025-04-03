#include "../debug.h"
#include "../../amp/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"
#include "../../tree/debug.h"
#include "../../macros/test.h"
#include "../../list/body/debug.h"



void test_qdd_create(bool show)
{
    TEST_FN

    TEST_CASE_OPEN(1)
    {
        CLU_HANDLER_REGISTER(ND(1));
        CLU_HANDLER_REGISTER(LB(2));

        qdd_p q = qdd_create(ND(1), LB(2), 3);
        assert(q->node == ND(1));
        assert(q->lb == LB(2));
        assert(q->qbits == 3);
        free(q);

        CLU_HANDLER_UNREGISTER(ND(1));
        CLU_HANDLER_UNREGISTER(LB(2));
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}

void test_qdd_create_immed(bool show)
{
    TEST_FN

    label_t amp, V1, V2;
    amp = LAB(0, 0);
    V1 = LAB(V, 1);
    V2 = LAB(V, 2);

    TEST_CASE_OPEN(1)
    {
        qdd_p q_res = qdd_create_immed(1,
            2, AMPI(0, 0), AMPI(0, 1),
            1,  V1, 1, amp, 0, amp, 1
        );
        node_p node_amp[] = {
            node_amp_create(AMPI(0, 0)),
            node_amp_create(AMPI(0, 1))
        };
        node_p node_v1 = node_branch_create(V1);
        node_connect_both(node_v1, node_amp[0], node_amp[1]);
        list_body_p lb = list_body_create_immed(2, node_amp[0], node_amp[1]);
        qdd_p q = qdd_create(node_v1, lb, 1);
        assert(qdd(q_res, q));
    }
    TEST_CASE_CLOSE

    TEST_CASE_OPEN(2)
    {
        qdd_p q_res = qdd_create_immed(1,
            1, AMPI(0, 0),
            0
        );
        node_p node_amp = node_amp_create(AMPI(0, 0));
        list_body_p lb = list_body_create_immed(1, node_amp);
        qdd_p q = qdd_create(node_amp, lb, 1);
        assert(qdd(q_res, q));
    }
    TEST_CASE_CLOSE

    TEST_CASE_OPEN(3)
    {
        qdd_p q_res = qdd_create_immed(2,
            4, AMPI(0, 0), AMPI(0, 1), AMPI(0, 2), AMPI(0, 3),
            2,  V1, 2, amp, 0, amp, 1, amp, 2, amp, 3,
                V2, 1, V1, 0, V1, 1
        );
        node_p node_amp[] = {
            node_amp_create(AMPI(0, 0)),
            node_amp_create(AMPI(0, 1)),
            node_amp_create(AMPI(0, 2)),
            node_amp_create(AMPI(0, 3))
        };
        node_p node_v1[] = {
            node_branch_create(V1),
            node_branch_create(V1),
        };
        node_p node_v2 = node_branch_create(V2);
        node_connect_both(node_v2, node_v1[0], node_v1[1]);
        node_connect_both(node_v1[0], node_amp[0], node_amp[1]);
        node_connect_both(node_v1[1], node_amp[2], node_amp[3]);
        list_body_p lb = list_body_create_immed(4,
            node_amp[0],
            node_amp[1],
            node_amp[2],
            node_amp[3]
        );
        qdd_p q = qdd_create(node_v2, lb, 2);
        assert(qdd(q_res, q));
    }
    TEST_CASE_CLOSE
    
    TEST_CASE_OPEN(4)
    {
        qdd_p q_res = qdd_create_immed(2,
            2, AMPI(0, 0), AMPI(0, 1),
            2,  V1, 1, amp, 0, amp, 1,
                V2, 1, amp, 0, V1, 0
        );
        node_p node_amp[] = {
            node_amp_create(AMPI(0, 0)),
            node_amp_create(AMPI(0, 1))
        };
        node_p node_v1 = node_branch_create(V1);
        node_p node_v2 = node_branch_create(V2);
        node_connect_both(node_v2, node_amp[0], node_v1);
        node_connect_both(node_v1, node_amp[0], node_amp[1]);
        list_body_p lb = list_body_create_immed(2, node_amp[0], node_amp[1]);
        qdd_p q = qdd_create(node_v2, lb, 2);
        assert(qdd(q_res, q));
    }
    TEST_CASE_CLOSE

    TEST_CASE_OPEN(5)
    {
        qdd_p q_res = qdd_create_immed(2,
            3, AMPI(0, 0), AMPI(0, 1), AMPI(0, 2),
            2,  V1, 2, amp, 0, amp, 1, amp, 0, amp, 2,
                V2, 1, V1, 0, V1, 1
        );
        node_p node_amp[] = {
            node_amp_create(AMPI(0, 0)),
            node_amp_create(AMPI(0, 1)),
            node_amp_create(AMPI(0, 2))
        };
        node_p node_v1[] = {
            node_branch_create(V1),
            node_branch_create(V1),
        };
        node_p node_v2 = node_branch_create(V2);
        node_connect_both(node_v2, node_v1[0], node_v1[1]);
        node_connect_both(node_v1[0], node_amp[0], node_amp[1]);
        node_connect_both(node_v1[1], node_amp[0], node_amp[2]);
        list_body_p lb = list_body_create_immed(3,
            node_amp[0],
            node_amp[1],
            node_amp[2]
        );
        qdd_p q = qdd_create(node_v2, lb, 2);
        assert(qdd(q_res, q));
    }
    TEST_CASE_CLOSE

    assert(clu_mem_is_empty());
}

void test_qdd_arr(bool show)
{
    TEST_FN

    label_t amp = LAB(0, 0);
    label_t v1 = LAB(V, 1);
    label_t v2 = LAB(V, 2);

    #define TEST_QDD_ARR(TAG, QBITS, ARR, ...)          \
    {                                                   \
        TEST_CASE_OPEN(TAG)                             \
        {                                               \
            qdd_p q = qdd_create_arr(QBITS, ARR);       \
            assert(qdd_immed(q, QBITS, __VA_ARGS__));   \
        }                                               \
        TEST_CASE_CLOSE                                 \
    }

    TEST_QDD_ARR(1, 1,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1)}),
        2,  AMPI(0, 0), AMPI(0, 1),
        1,  v1, 1, amp, 0, amp, 1
    );
    TEST_QDD_ARR(2, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 2), AMPI(0, 3)}),
        4,  AMPI(0, 0), AMPI(0, 1), AMPI(0, 2), AMPI(0, 3),
        2,  v1, 2, amp, 0, amp, 1, amp, 2, amp, 3,
            v2, 1, v1, 0, v1, 1
    );

    #undef TEST_QDD_ARR

    assert(clu_mem_is_empty());
}

void test_qdd_reduce(bool show)
{
    TEST_FN

    label_t amp = LAB(0, 0);
    label_t v1 = LAB(V, 1);

    #define TEST_QDD_REDUCE(TAG, QBITS, QDD, ...)       \
    {                                                   \
        TEST_CASE_OPEN(TAG)                             \
        {                                               \
            qdd_p q = qdd_create_arr(QBITS, QDD);       \
            qdd_reduce(q);                              \
            assert(qdd_immed(q, QBITS, __VA_ARGS__));   \
        }                                               \
        TEST_CASE_CLOSE                                 \
    }

    TEST_QDD_REDUCE(1, 1,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1)}),
        2, AMPI(0, 0), AMPI(0, 1),
        1, v1, 1, amp, 0, amp, 1
    );
    TEST_QDD_REDUCE(2, 1,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 0)}),
        1, AMPI(0, 0),
        0
    );
    TEST_QDD_REDUCE(3, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 0), AMPI(0, 1)}),
        2, AMPI(0, 0), AMPI(0, 1),
        1,  v1, 1, amp, 0, amp, 1
    );

    #undef TEST_QDD_REDUCE

    assert(clu_mem_is_empty());
}

void test_qdd_copy(bool show)
{
    TEST_FN

    #define TEST_QDD_COPY(TAG, QBITS, QDD, ...)         \
    {                                                   \
        TEST_CASE_OPEN(TAG)                             \
        {                                               \
            qdd_p q = qdd_create_arr(QBITS, QDD);       \
            qdd_reduce(q);                              \
            qdd_p q_res = qdd_copy(q);                  \
            assert(qdd(q_res, q));                      \
        }                                               \
        TEST_CASE_CLOSE                                 \
    }

    TEST_QDD_COPY(1, 1,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1)})
    );
    TEST_QDD_COPY(2, 1,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 0)})
    );
    TEST_QDD_COPY(3, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 2), AMPI(0, 3)})
    );
    TEST_QDD_COPY(4, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 0), AMPI(0, 3)})
    );
    TEST_QDD_COPY(5, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 0), AMPI(0, 1)})
    );
    TEST_QDD_COPY(6, 2,
        ((amp_t[]){AMPI(0, 0), AMPI(0, 1), AMPI(0, 1), AMPI(0, 0)})
    );
    TEST_QDD_COPY(7, 3,
        ((amp_t[]){
            AMPI(0, 0), AMPI(0, 1), AMPI(0, 1), AMPI(0, 0),
            AMPI(0, 1), AMPI(0, 0), AMPI(0, 0), AMPI(0, 1)
        })
    );

    #undef TEST_QDD_COPY

    assert(clu_mem_is_empty());
}



void test_qdd()
{
    printf("\n%s\t\t", __func__);

    bool show = false;

    test_qdd_create(show);
    test_qdd_create_immed(show);
    test_qdd_arr(show);
    test_qdd_reduce(show);
    test_qdd_copy(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_qdd();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
