#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h" 

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
    for(i=0; lb != NULL; i++, lb = lb->lb)
    {
        PRINT("\n\tnode %3d: %p\t\t", i, lb->n);
        label_display(node_label(lb->n));
    }
}

#endif

list_body_p list_body_create(node_p n, list_body_p lb_next)
{
    list_body_p lb;
    lb = malloc(sizeof(list_body_t));
    assert(lb);

    *lb = (list_body_t){n, lb_next};
    return lb;
}

list_body_p list_body_copy(list_body_p lb)
{
    list_body_p lb_new;
    lb_new = malloc(sizeof(list_body_t));
    assert(lb_new);

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
    while(lb)
        lb = list_body_pop(lb);
}



void list_body_insert(list_body_p lb, node_p n)
{
    if(lb->n) lb->lb = list_body_create(n, lb->lb);
    else      lb->n = n;
}

int list_body_remove(list_body_p lb, node_p n)
{
    if(lb->n == n)
    {
        list_body_p lb_aux = lb->lb;
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

void list_body_merge(list_body_p lb_1, list_body_p lb_2)
{
    for(; lb_1->lb; lb_1 = lb_1);
    lb_1->lb = list_body_copy(lb_2);
}
