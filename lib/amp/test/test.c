#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "../debug.h"

void test_amp_eq()
{
    printf("\n\t%s\t\t", __func__);

    amp_t amp_1 = (amp_t){1, 0};
    amp_t amp_2 = (amp_t){1, 0};
    int res = amp_eq(&amp_1, &amp_2);
    assert(res == true);
    
    amp_2 = (amp_t){1, 1};
    res = amp_eq(&amp_1, &amp_2);
    assert(res == false);
    
    
    amp_2 = (amp_t){0, 1};
    res = amp_eq(&amp_1, &amp_2);
    assert(res == false);
}

void test_amp()
{
    printf("\n%s\t\t", __func__);

    test_amp_eq();
}

int main() 
{
    setbuf(stdout, NULL);
    test_amp();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
