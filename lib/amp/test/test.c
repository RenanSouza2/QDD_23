#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_hello()
{
    printf("\n\ttest hello\t\t");
}

void test_amp()
{
    printf("\ntest amp library\t\t");

    test_hello();
}


int main() 
{
    setbuf(stdout, NULL);
    test_amp();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
