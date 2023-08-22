#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_list()
{
    printf("\ntest lib library\t\t");
}

int main() 
{
    setbuf(stdout, NULL);
    test_list();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
