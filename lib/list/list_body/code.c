#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void list_body_display_item(list_body_c const lb)
{
    if(display_header("LIST BODY", lb)) return;

    PRINT("\nnode: %p", lb->n);
    PRINT("\nlb  : %p", lb->lb);
    PRINT("\n");
}

void list_body_display(list_body_c lb)
{
    int i;
    for(i=0; lb; i++, lb = lb->lb)
    {
        PRINT("\n\tnode %3d: %p\t\t", i, lb->n);
        label_display(node_label(lb->n));
    }
}

bool list_body_vector(list_body_p lb, int tot_b, node_p n[])
{
    int i = 0;
    for(; lb && (i<tot_b); i++, lb = lb->lb)
    {
        if(lb->n == n[i]) continue;

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

#endif

list_body_p list_body_create_cold()
{
    list_body_p const lb = malloc(sizeof(list_body_t));
    assert(lb);
    return lb;
}

list_body_p list_body_create(node_p const n, list_body_p const lb_next)
{
    list_body_p const lb = list_body_create_cold();
    *lb = (list_body_t){n, lb_next};
    return lb;
}

list_body_p list_body_copy(list_body_c const lb)
{
    list_body_p const lb_new = list_body_create_cold();
    *lb_new = *lb;
    return lb_new;
}

list_body_p list_body_pop(list_body_p const lb)
{
    list_body_p const lb_aux = lb->lb;
    free(lb);
    return lb_aux;
}

void list_body_free(list_body_p lb)
{
    while(lb) lb = list_body_pop(lb);
}



void list_body_insert(list_body_p const lb, node_p const n)
{
    if(lb->n) lb->lb = list_body_create(n, lb->lb);
    else      lb->n  = n;
}

bool list_body_remove(list_body_p lb, node_c const n)
{
    if(lb->n == n)
    {
        list_body_p const lb_aux = lb->lb;
        if(lb_aux == NULL)
        {
            lb->n = NULL;
            return false;
        }

        *lb = *lb_aux;
        free(lb_aux);
        return true;
    }

    for(; lb->lb; lb = lb->lb)
        if(lb->lb->n == n)
            break;

    assert(lb->lb);
    lb->lb = list_body_pop(lb->lb);
    return true;
}

void list_body_merge(list_body_p lb_1, list_body_p const lb_2)
{
    for(; lb_1->lb; lb_1 = lb_1->lb);
    lb_1->lb = list_body_copy(lb_2);
}
