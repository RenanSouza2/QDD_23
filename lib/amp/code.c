#include <stdbool.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../utils/header.h"

void amp_display(amp_p amp)
{
    PRINT("%.1e, %.1e", amp->re, amp->im);
}

#endif

number_t eps = 1e-5;

void set_eps(number_t _eps)
{
    eps = _eps;
}

bool amp_eq(amp_p amp_1, amp_p amp_2)
{
    assert(amp_1);
    assert(amp_2);

    number_t re = amp_1->re - amp_2->re;
    if(re < -eps || re > eps) return false;

    number_t im = amp_1->im - amp_2->im;
    return !(im < -eps || im > eps);
}
