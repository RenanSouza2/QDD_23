#include "debug.h"
#include "../utils/header.h"

#ifdef DEBUG

void amp_display(amp_t amp)
{
    PRINT("%.1e, %.1e", amp.re, amp.im);
}



bool amplitude(amp_t amp_1, amp_t amp_2)
{
    if(!amp_eq(amp_1, amp_2))
    {
        printf("\n\n\tAMP ASSERTION ERROR\t| AMP MISMATCH | (");
        amp_display(amp_1);
        printf(") (");
        amp_display(amp_2);
        printf(")\t\t");
        return false;
    }

    return true;
}

#endif

number_t eps = 1e-10;

void set_eps(number_t _eps)
{
    eps = _eps;
}

bool amp_eq(amp_t amp_1, amp_t amp_2)
{
    number_t re = amp_1.re - amp_2.re;
    number_t im = amp_1.im - amp_2.im;
    return re * re + im * im < eps;
}

void amp_display(amp_t amp)
{
    PRINT("%.1e, %.1e", amp.re, amp.im);
}
