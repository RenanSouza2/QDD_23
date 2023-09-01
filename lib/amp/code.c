#include <stdbool.h>

#include "debug.h"

#ifdef DEBUG
#endif

number_t eps = 1e-5;

void set_eps(number_t _eps)
{
    eps = _eps;
}

int amp_compare(amp_c const amp_1, amp_c const amp_2)
{
    number_t re = amp_1->re - amp_2->re;
    if(re < -eps || re > eps) return false;

    number_t im = amp_1->im - amp_2->im;
    return !(im < -eps || im > eps);
}
