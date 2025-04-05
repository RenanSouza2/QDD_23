#include "../debug.h"
#include "../../macros/test.h"
#include "../../../mods/clu/header.h"



void test_label_compare(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LABEL_COMPARE(TAG, CL1, LV1, EXPR, CL2, LV2)   \
    {                                                           \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);      \
        label_t lab_1 = LAB(CL1, LV1);                          \
        label_t lab_2 = LAB(CL2, LV2);                          \
        int res = label_compare(&lab_1, &lab_2);                \
        assert(res EXPR 0);                                     \
    }

    TEST_LABEL_COMPARE(1, V, 2, >, C, 1);
    TEST_LABEL_COMPARE(2, V, 2, >, V, 1);
    TEST_LABEL_COMPARE(3, V, 2, >, R, 1);

    TEST_LABEL_COMPARE(4, V, 2, >, C, 2);
    TEST_LABEL_COMPARE(5, V, 2, ==, V, 2);
    TEST_LABEL_COMPARE(6, V, 2, <, R, 2);

    TEST_LABEL_COMPARE(1, V, 2, <, C, 3);
    TEST_LABEL_COMPARE(1, V, 2, <, V, 3);
    TEST_LABEL_COMPARE(1, V, 2, <, R, 3);

    #undef TEST_LABEL_COMPARE

    assert(clu_mem_is_empty());
}

void test_label_is_amp(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_LABEL_IS_AMP(TAG, CL, LV, RES)             \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        label_t lab = LAB(CL, LV);                          \
        bool res = label_is_amp(&lab);                      \
        assert(res == RES);                                 \
    }

    TEST_LABEL_IS_AMP(1, 0, 0, true);
    TEST_LABEL_IS_AMP(2, V, 1, false);

    #undef TEST_LABEL_IS_AMP

    assert(clu_mem_is_empty());
}



void test_label()
{
    printf("\n%s\t\t", __func__);

    bool show = false;

    test_label_compare(show);

    assert(clu_mem_is_empty());
}



int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_label();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
