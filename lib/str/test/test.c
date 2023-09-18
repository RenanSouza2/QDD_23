#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_str_a()
{
    printf("\n\t%s\t\t", __func__);
}

void test_str()
{
    printf("\n%s\t\t", __func__);

    test_str_a();
}


int main() 
{
    setbuf(stdout, NULL);
    test_str();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
