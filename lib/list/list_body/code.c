#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../../label/header.h"
#include "debug.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"

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

void list_body_free(list_body_p lb)
{
    while(lb != NULL)
    {
        list_body_p lb_aux = lb;
        lb = lb->lb;

        free(lb_aux);
    }
}

void list_body_insert(list_body_p lb, node_p n)
{
    if(lb->n) lb->lb = list_body_create(n, lb->lb);
    else      lb->n = n;
}

// return value: true if empty
int list_body_remove(list_body_p lb, node_p n)
{
    if(lb->n == n)
    {
        list_body_p lb_aux = lb->lb;
        if(lb_aux == NULL)
        {
            lb->n = NULL;
            return true;
        }

        *lb = *lb_aux;
        free(lb_aux);
        return false;
    }

    for(; lb->lb; lb = lb->lb)
        if(lb->lb->n == n)
            break;

    assert(lb->lb);
    
    list_body_p lb_aux = lb->lb;
    lb->lb = lb_aux->lb;
    free(lb_aux);
    return false;
}