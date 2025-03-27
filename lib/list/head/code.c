#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../../macros/assert.h"
#include "../../../mods/clu/header.h"

#include "debug.h"
#include "../body/struct.h"
#include "../../node/struct.h"



#ifdef DEBUG

#include "../body/debug.h"
#include "../../utils/debug.h"
#include "../../label/debug.h"



void list_head_display_item(list_head_p lh)
{
    if(display_header("LIST HEAD", lh))
        return;

    PRINT("\nlb[ELSE] : %p", lh->lb[ELSE]);
    PRINT("\nlb[THEN] : %p", lh->lb[THEN]);
    PRINT("\nnext     : %p", lh->next);
}

void list_head_display(list_head_p lh)
{
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

bool list_head(list_head_p lh, int tot_h, ...)
{
    va_list args;
    va_start(args, tot_h);

    int i=0;

    for(; lh && (i<tot_h); i++, lh = lh->next)
    {
        label_t lab = va_arg(args, label_t);
        if(!label(lh->lab, lab))
        {
            PRINT("\nLIST HEAD ASSERTION ERROR\t| LABEL MISMATCH ");
            return false;
        }

        for(int side=0; side<2; side++)
        {
            int tot_b = va_arg(args, int);
            if(!list_body_variadic(lh->lb[side], tot_b, &args))
            {
                PRINT("\nLIST HEAD ASSERTION ERROR\t| LIST BODY %s MISMATCH | %d %d\t\t", side ? "THEN" : "ELSE", i, tot_h);
                return false;
            }
        }
    }

    if(lh)
    {
        PRINT("\nERROR LIST HEAD VECTOR 4 | LIST LONGER | %d\t\t", tot_h);
        return false;
    }

    if(i < tot_h)
    {
        PRINT("\nERROR LIST HEAD VECTOR 5 | LIST SHORTER | %d %d\t\t", i, tot_h);
        return false;
    }

    return true;
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

#endif



list_head_p list_head_create_body(list_body_p lb, int side, list_head_p next)
{
    CLU_IS_SAFE(lb);
    CLU_IS_SAFE(next);

    list_head_p lh = malloc(sizeof(list_head_t));
    assert(lh);

    lh->lab = lb->node->lab;
    lh->lb[side] = lb;
    lh->next = next;

    return lh;
}

list_head_p list_head_create(node_p node, int side, list_head_p next)
{
    CLU_IS_SAFE(node);
    CLU_IS_SAFE(next);

    list_body_p lb = list_body_create(node, NULL);
    return list_head_create_body(lb, side, next);
}

list_head_p list_head_pop(list_head_p lh)
{
    CLU_IS_SAFE(lh);

    list_head_p lh_aux = lh->next;
    free(lh);
    return lh_aux;
}

void list_head_free(list_head_p lh)
{
    CLU_IS_SAFE(lh);

    for(; lh; lh = list_head_pop(lh))
    for(int side = 0; side < 2; side ++)
        list_body_free(lh->lb[side]);
}



node_p list_head_first(list_head_p lh)
{
    CLU_IS_SAFE(lh);

    if(lh == NULL)
        return NULL;

    if(lh->lb[ELSE])
        return lh->lb[ELSE]->node;

    return lh->lb[THEN]->node;
}

bool list_head_occupied(list_head_p lh)
{
    CLU_IS_SAFE(lh);

    return lh->lb[ELSE] || lh->lb[THEN];
}



list_head_p list_head_insert(list_head_p lh, node_p node, int side)
{
    CLU_IS_SAFE(lh);
    CLU_IS_SAFE(node);

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

        case 1:
        {
            lh->next = list_head_insert(lh->next, node, side);
            return lh;
        }
    }
    assert(false);
}

list_head_p list_head_remove(list_head_p lh, node_p node, int side)
{
    CLU_IS_SAFE(lh);
    CLU_IS_SAFE(node);

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
            lh_1->next = list_head_merge(lh_1->next, lh_2->next);
            free(lh_2);
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
