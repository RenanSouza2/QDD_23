#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "../debug.h"

void test_amp_compare()
{
    printf("\n\ttest amp compare\t\t");

    amp_t amp_1 = (amp_t){1, 0};
    amp_t amp_2 = (amp_t){1, 0};
    int res = amp_compare(&amp_1, &amp_2);
    assert(res == true);
    
    amp_2 = (amp_t){1, 1};
    res = amp_compare(&amp_1, &amp_2);
    assert(res == false);
    
    
    amp_2 = (amp_t){0, 1};
    res = amp_compare(&amp_1, &amp_2);
    assert(res == false);
}

void test_amp()
{
    printf("\ntest amp library\t\t");

    test_amp_compare();
}

int main() 
{
    setbuf(stdout, NULL);
    test_amp();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
