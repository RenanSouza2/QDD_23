#ifndef __APPLY_STRUCT_H__
#define __APPLY_STRUCT_H__

#include "../macros/struct.h"

PLACEHOLDER(node);

STRUCT(apply)
{
    node_p n, n1, n2;
    apply_p el, th;
    apply_p a1, a2;
};

#endif
