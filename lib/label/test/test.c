#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_label()
{
    printf("\ntest label library\t\t");
}


int main() 
{
    setbuf(stdout, NULL);
    test_label();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
