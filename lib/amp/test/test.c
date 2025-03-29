// #include <stdio.h>
#include <stdbool.h>

#include "../debug.h"
#include "../../macros/test.h"
#include "../../../mods/clu/header.h"

void test_amp_eq(bool show)
{
    printf("\n\t%s\t\t", __func__);

    #define TEST_AMP_EQ(TAG, AMP_1, AMP_2, RES)       \
    {                                                       \
        if(show) printf("\n\t\t%s %d\t\t", __func__, TAG);  \
        int res = amp_eq(AMP_1, AMP_2);                     \
        assert(res == RES);                                 \
    }

    TEST_AMP_EQ(1, AMPI(1, 0), AMPI(1, 0), true);
    TEST_AMP_EQ(2, AMPI(1, 0), AMPI(1, 1), false);
    TEST_AMP_EQ(3, AMPI(1, 0), AMPI(0, 1), false);

    #undef TEST_AMP_EQ

    assert(clu_mem_is_empty());
}

void test_amp()
{
    printf("\n%s\t\t", __func__);

    bool show = false;

    test_amp_eq(show);

    assert(clu_mem_is_empty());
}

int main()
{
    setbuf(stdout, NULL);
    TEST_TIMEOUT_OPEN(TEST_TIMEOUT_DEFAULT)
    test_amp();
    TEST_TIMEOUT_CLOSE
    printf("\n\n\tTest successful\n\n");
    return 0;
}
