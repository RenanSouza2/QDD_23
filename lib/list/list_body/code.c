#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void list_body_display_item(list_body_p lb)
{
    if(display_header("LIST BODY", lb)) return;

    PRINT("\nnode: %p", lb->n);
    PRINT("\nlb  : %p", lb->lb);
    PRINT("\n");
}

void list_body_display(list_body_p lb)
{
    int i;
    for(i=0; lb; i++, lb = lb->lb)
    {
        PRINT("\n\tnode %3d: %p\t\t", i, lb->n);
        label_display(node_label(lb->n));
    }
}

bool list_body_vector_vargs(list_body_p lb, int tot_b, va_list * args)
{
    int i = 0;
    for(; lb && (i<tot_b); i++, lb = lb->lb)
    {
        node_p n = va_arg(*args, node_p);
        if(lb->n == n) continue;

        PRINT("\nERROR LIST BODY VECTOR 1 | NODE MISMATCH | %d %d\t\t", i, tot_b);
        return false;
    }

    if(lb)
    {
        PRINT("\nERROR LIST BODY VECTOR 2 | LIST LONGER | %d\t\t", tot_b);
        return false;
    }

    if(i < tot_b)
    {
        PRINT("\nERROR LIST BODY VECTOR 3 | LIST SHORTER | %d %d\t\t", i, tot_b);
        return false;
    }

    return true;
}

bool list_body_vector(list_body_p lb, int tot_b, ...)
{
    va_list args;
    va_start(args, tot_b);
    return list_body_vector_vargs(lb, tot_b, &args);
}

#endif

list_body_p list_body_create_cold()
{
    list_body_p lb = malloc(sizeof(list_body_t));
    assert(lb);
    return lb;
}

list_body_p list_body_create(node_p n, list_body_p lb_next)
{
    list_body_p lb = list_body_create_cold();
    *lb = (list_body_t){n, lb_next};
    return lb;
}

list_body_p list_body_copy(list_body_p lb)
{
    list_body_p lb_new = list_body_create_cold();
    *lb_new = *lb;
    return lb_new;
}

list_body_p list_body_pop(list_body_p lb)
{
    list_body_p lb_aux = lb->lb;
    free(lb);
    return lb_aux;
}

void list_body_free(list_body_p lb)
{
    while(lb) lb = list_body_pop(lb);
}



list_body_p list_body_remove(list_body_p lb, node_p n)
{
    if(lb->n == n)
        return list_body_pop(lb);

    list_body_p lb_0 = lb;
    for(; lb->lb; lb = lb->lb)
        if(lb->lb->n == n)
            break;

    assert(lb->lb);
    lb->lb = list_body_pop(lb->lb);
    return lb_0;
}

list_body_p list_body_merge(list_body_p lb_1, list_body_p lb_2)
{
    if(lb_1 == NULL) return lb_2;
    if(lb_2 == NULL) return lb_1;

    list_body_p lb_2_0 = lb_2;
    for(; lb_2->lb; lb_2 = lb_2->lb);
    lb_2->lb = lb_1;
    return lb_2_0;
}
