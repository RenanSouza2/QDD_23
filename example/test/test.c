#include <stdio.h>

#include "../debug.h"

void test_example()
{
    printf("\n%s\t\t", __func__);

    test_hello();
}


int main()
{
    setbuf(stdout, NULL);
    test_example();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
