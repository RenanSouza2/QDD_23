#ifndef __APPLY_STRUCT_H__
#define __APPLY_STRUCT_H__

#include "header.h"

#include "../node/header.h"

STRUCT(apply)
{
    node_p n, n1, n2;
    apply_p el, th;
    apply_p a1, a2;
};

#endif
