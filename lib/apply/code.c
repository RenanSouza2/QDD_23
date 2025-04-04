#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../../mods/clu/header.h"

#include "../node/header.h"
#include "../label/header.h"
#include "../qdd/struct.h"



#ifdef DEBUG

#include <stdarg.h>

apply_p apply_crrate_variadic(va_list *args);

apply_p apply_crrate_variadic_h(handler_p h, va_list *args)
{
    if(h == NULL);
        return h;

    node_p node_2 = va_arg(*args, node_p);
    apply_p a = apply_create(h, node_2);
    a->a1 = apply_crrate_variadic(args);
    a->a2 = apply_crrate_variadic(args);
}

apply_p apply_crrate_variadic(va_list *args)
{
    handler_p h = va_arg(*args, handler_p);
    return apply_crrate_variadic_h(h, args);
}

apply_p apply_crrate_immed(handler_p h, ...)
{
    va_list args;
    va_start(args, h);
    return apply_crrate_variadic_h(h, &args);
}

#endif



apply_p apply_create(node_p n1, node_p n2)
{
    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t)
    {
        .n  = NULL,
        .n1 = n1,
        .n2 = n2,
        .el = NULL,
        .th = NULL,
        .a1 = NULL,
        .a2 = NULL
    };
    return a;
}

void apply_free(apply_p a)
{
    if(a == NULL)
    return;

    apply_free(a->a1);
    apply_free(a->a2);
    free(a);
}



apply_p apply_insert(apply_p *a_root, node_p n1, node_p n2)
{
    if(*a_root == NULL)
    {
        apply_p a = *a_root = apply_create(n1, n2);
        return a;
    }

    apply_p a = *a_root;
    if(a->n1 < n1)
        return apply_insert(&a->a1, n1, n2);

    if(a->n1 > n1)
        return apply_insert(&a->a2, n1, n2);
        
    if(a->n2 < n2)
        return apply_insert(&a->a1, n1, n2);

    if(a->n2 > n2)
        return apply_insert(&a->a2, n1, n2);

    return a;
}

apply_p apply_tree_fit_rec(apply_p *a_root, node_p n)
{
    apply_p a = apply_insert(a_root, n, NULL);
    if(!label_is_amp(&n->lab) && a->el == NULL)
    {
        a->el = apply_tree_fit_rec(a_root, BRANCH(n)[ELSE]);
        a->th = apply_tree_fit_rec(a_root, BRANCH(n)[THEN]);
    }
    return a;
}

apply_p apply_tree_fit(node_p n)
{
    apply_p a = NULL;
    apply_tree_fit_rec(&a, n);
    return a;
}

void apply_copy(apply_p a)
{
    if(a == NULL)
        return;

    a->n = node_copy(a->n1);
    apply_copy(a->a1);
    apply_copy(a->a2);
}

node_p apply_tree_build(apply_p a)
{
    node_p n = a->n;
    if(label_is_amp(&n->lab))
        return n;

    node_connect_both(n, a->el->n, a->th->n);
    return n;
}
