#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    setbuf(stdout, NULL);
    for(int i=1; i<30; i++)
    {
        printf("\ni: %d", i);
        qdd_p q = qdd_create_fn(i, 0, amp_fn);
        printf("\tHere");
        qdd_reduce(q);
        printf("\tThere");
        qdd_display(q);
        qdd_free(q);
    }

    printf("\n");
    return 0;
}