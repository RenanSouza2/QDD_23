#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_apply()
{
    printf("\n%s\t\t", __func__);
}


int main() 
{
    setbuf(stdout, NULL);
    test_apply();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
