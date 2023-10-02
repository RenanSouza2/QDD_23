#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../../node/struct.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"
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

void list_body_display_full(list_body_p lb)
{
    for(; lb; lb = lb->lb)
        node_display(lb->n);
}

bool list_body_vargs(list_body_p lb, int tot_b, va_list * args)
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

bool list_body(list_body_p lb, int tot_b, ...)
{
    va_list args;
    va_start(args, tot_b);
    return list_body_vargs(lb, tot_b, &args);
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

list_body_p list_body_create_vector(int max, node_p N[])
{
    list_body_p lb_0 = list_body_create(N[0], NULL);
    
    list_body_p lb = lb_0;
    for(int i=1; i<max; i++)
        lb = lb->lb = list_body_create(N[i], NULL);

    return lb_0;
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

bool list_body_reduce_equivalence_1(list_body_p lb, node_eq_f fn, node_p n1, bool remove)
{
    bool insert = false;
    for(; lb->lb; )
    {
        node_p n2 = lb->lb->n;
        if(!fn(n1, n2)) 
        {
            lb = lb->lb;
            continue;
        }

        insert = true;
        node_merge(n1, n2);
        if(remove) lb->lb = list_body_pop(lb->lb);
    }

    return insert;
}

list_body_p list_body_reduce_equivalence(list_body_p lb, node_eq_f fn, bool remove)
{
    if(lb == NULL) return NULL;

    list_body_p lb_res = NULL;
    for(; lb && lb->lb; lb = lb->lb)
    {
        node_p n1 = lb->n;
        if(!list_body_reduce_equivalence_1(lb, fn, n1, remove))
            continue;
            
        lb_res = list_body_create(n1, lb_res);
        if(lb->lb == NULL) break;
    }

    return lb_res;
}

bool list_body_reduce_redundance(list_body_p *lb_p, node_p n0)
{
    if(*lb_p == NULL) return false;

    node_p n1 = (*lb_p)->n;
    str_p str = node_str(n1);
    if(str->el != str->th) return false;

    node_disconnect_both(n1);
    node_merge(n0, n1);
    return true;
}

void list_body_reduce_redundance_rec(list_body_p *lb_p, node_p n0)
{
    while(list_body_reduce_redundance(lb_p, n0));

    if(*lb_p == NULL) return;

    list_body_reduce_redundance_rec(&(*lb_p)->lb, n0);
}
