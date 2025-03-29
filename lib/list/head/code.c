#include <stdlib.h>

#include "debug.h"
#include "../../../mods/clu/header.h"

#include "../body/struct.h"
#include "../../node/struct.h"
#include "../../label/header.h"
#include "../../macros/assert.h"



#ifdef DEBUG

#include "../body/debug.h"
#include "../../label/debug.h"
#include "../../utils/debug.h"



list_head_p list_head_create_variadic_item(va_list *args)
{
    label_t lab = va_arg(*args, label_t);
    list_body_p lb_el = list_body_create_variadic(args);
    list_body_p lb_th = list_body_create_variadic(args);

    list_head_p lh = malloc(sizeof(list_head_t));
    assert(lh);
    *lh = (list_head_t)
    {
        .lab = lab,
        .lb = {lb_el, lb_th},
        .next = NULL
    };
    return lh;
}

list_head_p list_head_create_variadic_n(int n, va_list *args)
{
    if(n == 0)
        return NULL;

    list_head_p lh_0, lh;
    lh_0 = lh = list_head_create_variadic_item(args);
    for(int i=1; i<n; i++)
        lh= lh->next = list_head_create_variadic_item(args);

    return lh_0;
}

list_head_p list_head_create_variadic(va_list *args)
{
    int n = va_arg(*args, int);
    return list_head_create_variadic_n(n, args);
}

list_head_p list_head_create_immed(int n, ...)
{
    va_list args;
    va_start(args, n);
    return list_head_create_variadic_n(n, &args);
}

void list_head_create_vec_immed(list_head_p lh[], int n, ...)
{
    va_list args;
    va_start(args, n);
    for(int i=0; i<n; i++)
        lh[i] = list_head_create_variadic(&args);
}



void list_head_display(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    if(lh == NULL)
    {
        printf("\nLIST HEAD EMPTY");
        return;
    }

    for(; lh; lh = lh->next)
    {
        PRINT("\n--------");
        printf("\nLABEL: ");
        label_display(lh->lab);
        printf("\nELSE");
        list_body_display(lh->lb[ELSE]);
        printf("\nTHEN");
        list_body_display(lh->lb[THEN]);
    }
}

void list_head_display_full(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    if(lh == NULL) PRINT("\nnull list");

   for(; lh; lh = lh->next)
    {
        PRINT("\n--------");
        for(int side=0; side<2; side++)
        if(lh->lb[side])
        {
            PRINT("\n");
            label_display(lh->lab);
            PRINT(" %s", side ? "THEN" : "ELSE");
            list_body_display_full(lh->lb[side]);
        }
    }
    printf("\t\t");
}



list_head_p list_head_invert(list_head_p lh)
{
    list_head_p lh_new = NULL;

    while(lh)
    {
        list_head_p lh_aux = lh->next;

        lh->next = lh_new;
        lh_new = lh;

        lh = lh_aux;
    }
    return lh_new;
}



bool list_head_inner(list_head_p lh_1, list_head_p lh_2)
{
    CLU_HANDLER_IS_SAFE(lh_1);
    CLU_HANDLER_IS_SAFE(lh_2);

    for(int i=0; lh_1 && lh_2; i++)
    {
        CLU_HANDLER_IS_SAFE(lh_1);

        if(!label(lh_1->lab, lh_2->lab))
        {
            printf("\n\tLIST HEAD ASSERTION ERROR\t| LABEL MISMATCH %d", i);
            return false;
        }

        for(int side=0; side<2; side++)
        {
            if(!list_body_inner(lh_1->lb[side], lh_2->lb[side]))
            {
                printf("\n\tLIST HEAD ASSERTION ERROR\t| LIST BODY MISMATCH | %d ", i);
                label_display(lh_1->lab);
                printf(" %s", side ? "THEN" : "ELSE");
                return false;
            }
        }

        lh_1 = lh_1->next;
        lh_2 = lh_2->next;
    }

    if(lh_1)
    {
        printf("\n\tLIST HEAD ASSERTION ERROR\t| LIST LONGER");
        return false;
    }

    if(lh_2)
    {
        printf("\n\tLIST HEAD ASSERTION ERROR\t| LIST shorter");
        return false;
    }

    return true;
}

bool list_head(list_head_p lh_1, list_head_p lh_2)
{
    if(!list_head_inner(lh_1, lh_2)) // TODO reevaluate
    {
        printf("\n\nLIST HEAD 1");
        list_head_display(lh_1);
        printf("\n\nLIST HEAD 2");
        list_head_display(lh_2);
        return false;
    }

    list_head_free(lh_1);
    list_head_free(lh_2);
    return true;
}

bool list_head_immed(list_head_p lh, int n, ...)
{
    va_list args;
    va_start(args, n);
    list_head_p lh_2 = list_head_create_variadic_n(n, &args);
    return list_head(lh, lh_2);
}

#endif



list_head_p list_head_create_body(list_body_p lb, int side, list_head_p next)
{
    CLU_HANDLER_IS_SAFE(lb);
    CLU_HANDLER_IS_SAFE(lb->node);
    CLU_HANDLER_IS_SAFE(next);

    assert(lb);
    assert(lb->node);

    list_head_p lh = malloc(sizeof(list_head_t));
    assert(lh);

    lh->lab = lb->node->lab;
    lh->lb[ side] = lb;
    lh->lb[!side] = NULL;
    lh->next = next;

    return lh;
}

list_head_p list_head_create(node_p node, int side, list_head_p next)
{
    CLU_HANDLER_IS_SAFE(node);
    CLU_HANDLER_IS_SAFE(next);

    list_body_p lb = list_body_create(node, NULL);
    return list_head_create_body(lb, side, next);
}

list_head_p list_head_pop(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    assert(lh);

    list_head_p lh_aux = lh->next;
    free(lh);
    return lh_aux;
}

void list_head_free(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    for(; lh; lh = list_head_pop(lh))
    for(int side = 0; side < 2; side ++)
        list_body_free(lh->lb[side]);
}



node_p list_head_first(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    assert(lh);

    if(lh->lb[ELSE])
        return lh->lb[ELSE]->node;

    return lh->lb[THEN]->node;
}

bool list_head_occupied(list_head_p lh)
{
    CLU_HANDLER_IS_SAFE(lh);

    return lh->lb[ELSE] || lh->lb[THEN];
}



list_head_p list_head_insert(list_head_p lh, node_p node, int side)
{
    CLU_HANDLER_IS_SAFE(lh);
    CLU_HANDLER_IS_SAFE(node);

    assert(node);

    if(lh == NULL)
        return list_head_create(node, side, NULL);

    switch (label_compare(&node->lab, &lh->lab))
    {
        case -1:
        {
            return list_head_create(node, side, lh);
        }

        case 0:
        {
            lh->lb[side] = list_body_create(node, lh->lb[side]);
            return lh;
        }
    }

    lh->next = list_head_insert(lh->next, node, side);
    return lh;
}

list_head_p list_head_remove(list_head_p lh, node_p node, int side)
{
    CLU_HANDLER_IS_SAFE(lh);
    CLU_HANDLER_IS_SAFE(node);

    assert(lh);
    assert(node);

    switch(label_compare(&node->lab, &lh->lab))
    {
        case 0:
        {
            lh->lb[side] = list_body_remove(lh->lb[side], node);
            return list_head_occupied(lh) ? lh : list_head_pop(lh);
        }

        case 1:
        {
            lh->next = list_head_remove(lh->next, node, side);
            return lh;
        }
    }
    assert(false);
}

list_head_p list_head_merge(list_head_p lh_1, list_head_p lh_2)
{
    if(lh_1 == NULL) return lh_2;
    if(lh_2 == NULL) return lh_1;

    switch (label_compare(&lh_1->lab, &lh_2->lab))
    {
        case -1:
        {
            lh_1->next = list_head_merge(lh_1->next, lh_2);
            return lh_1;
        }

        case 0:
        {
            lh_1->lb[ELSE] = list_body_merge(lh_1->lb[ELSE], lh_2->lb[ELSE]);
            lh_1->lb[THEN] = list_body_merge(lh_1->lb[THEN], lh_2->lb[THEN]);
            lh_1->next = list_head_merge(lh_1->next, list_head_pop(lh_2));
            return lh_1;
        }

        case 1:
        {
            lh_2->next = list_head_merge(lh_1, lh_2->next);
            return lh_2;
        }
    }
    assert(false);
}
