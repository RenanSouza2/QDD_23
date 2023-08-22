#include <stdio.h>
#include <assert.h>

#include "../debug.h"

void test_node()
{
    printf("\ntest node library\t\t");
}

int main() 
{
    setbuf(stdout, NULL);
    test_node();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
