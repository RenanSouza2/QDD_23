#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../static_utils/struct.h"
#include "../lib/qdd/header.h"
#include "../lib/amp/struct.h"

amp_t amp_fn(int index)
{
    return AMP(0, 0);
}


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
        // qdd_display(q);
        qdd_free(q);
    }

    printf("\n");
    return 0;
}