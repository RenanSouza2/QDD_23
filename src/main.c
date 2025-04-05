#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../lib/qdd/header.h"
#include "../lib/amp/header.h"
#include "../lib/macros/U64.h"


uint64_t altutime()
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return time.tv_sec * 1e3 + time.tv_nsec / 1e6;
}


amp_t amp_fn(int index)
{
    return (amp_t)
    {
        .re = 0, 
        .im = (number_t)index
    };
}



int main()
{
    setbuf(stdout, NULL);
    for(int i=1; i<25; i++)
    {
        printf("\ni: %d", i);
        qdd_p q = qdd_create_fn(i, 0, amp_fn);
        qdd_reduce(q);
        
        uint64_t begin = altutime();
        printf("\t%lu", begin);
        qdd_p q2 = qdd_copy(q);
        uint64_t end = altutime();
        printf("\t%lu", end);

        qdd_free(q);
        qdd_free(q2);
    }

    printf("\n");
    return 0;
}