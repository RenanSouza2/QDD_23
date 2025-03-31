#include <stdio.h>

#include "../debug.h"

void test_utils()
{
    printf("\ntest utils library\t\t");
}


int main()
{
    return 0;

    setbuf(stdout, NULL);
    test_utils();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
