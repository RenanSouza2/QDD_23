#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "debug.h"
#include "../list_body/struct.h"

#ifdef DEBUG

#include "../list_body/debug.h"
#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void list_head_display_item(list_head_p lh)
{
    if(display_header("LIST HEAD", lh)) return;

    PRINT("\nlb[ELSE]  : %p", lh->lb[ELSE]);
    PRINT("\nlb[THEN]  : %p", lh->lb[THEN]);
    PRINT("\nlh  : %p", lh->lh);
}

void list_head_display(list_head_p lh)
{
    if(lh == NULL) PRINT("\nnull list");

   for(; lh; lh = lh->lh)
    {
        PRINT("\n--------");
        for(int side=0; side<2; side++)
        if(lh->lb[side])
        {
            PRINT("\n");
            label_display(&lh->lab);
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
    for(; lh && (i<tot_h); i++, lh = lh->lh)
    {
        label_t lab = va_arg(args, label_t);
        if(label_compare(&lh->lab, &lab) != 0)
        {
            PRINT("\nERROR LIST HEAD VECTOR 1 | LABEL MISMATCH | ");
            label_display(&lh->lab);
            PRINT(" ");
            label_display(&lab);
            PRINT("\t\t");
            return false;
        }

        
        for(int side=0; side<2; side++)
        {
            int tot_b = va_arg(args, int);
            if(!list_body_vargs(lh->lb[side], tot_b, &args))
            {
                PRINT("\nERROR LIST HEAD VECTOR 2 | LIST BODY %s MISMATCH | %d %d\t\t", side ? "THEN" : "ELSE", i, tot_h);
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
        list_head_p lh_aux = lh->lh;

        lh->lh = lh_new;
        lh_new = lh;

        lh = lh_aux;
    }
    return lh_new;
}

#endif

list_head_p list_head_create_cold()
{
    list_head_p lh = malloc(sizeof(list_head_t));
    assert(lh);
    return lh;
}

list_head_p list_head_create(node_p n, list_head_p lh_next, int side)
{
    list_head_p lh = list_head_create_cold();
    label_p lab = node_label(n);
    *lh = (list_head_t){*lab, {NULL, NULL}, lh_next};
    lh->lb[side] = list_body_create(n, NULL);
    return lh;
}

list_head_p list_head_create_body(list_body_p lb, list_head_p lh_next, int side)
{
    list_head_p lh = list_head_create_cold();
    label_p lab = node_label(lb->n);
    *lh = (list_head_t){*lab, {NULL, NULL}, lh_next};
    lh->lb[side] = lb;
    return lh;
}

list_head_p list_head_pop(list_head_p lh)
{
    list_head_p lh_aux = lh->lh;
    free(lh);
    return lh_aux;
}

void list_head_free(list_head_p lh)
{
    for(; lh; lh = list_head_pop(lh))
    for(int side = 0; side < 2; side ++)
        list_body_free(lh->lb[side]);
}



label_p list_label(list_head_p lh)
{
    return &lh->lab;
}

int label_list_compare(label_p lab, list_head_p lh)
{
    return label_compare(lab, list_label(lh));
}

int list_compare(list_head_p lh_1, list_head_p lh_2)
{
    return label_compare(list_label(lh_1), list_label(lh_2));
}

node_p list_head_first(list_head_p lh)
{
    if(lh == NULL) return NULL;
    if(lh->lb[ELSE]) return lh->lb[ELSE]->n;
    if(lh->lb[THEN]) return lh->lb[THEN]->n;
    return NULL;
}

bool list_head_occupied(list_head_p lh)
{
    return lh->lb[ELSE] || lh->lb[THEN];
}



list_head_p list_head_insert(list_head_p lh, node_p n, int side)
{
    if(lh == NULL) return list_head_create(n, NULL, side);
    
    label_p lab = node_label(n);
    switch (label_list_compare(lab, lh))
    {
        case -1: return list_head_create(n, lh, side);
        
        case 0: 
        lh->lb[side] = list_body_create(n, lh->lb[side]);
        return lh;

        case 1:
        lh->lh = list_head_insert(lh->lh, n, side);
        return lh;
    }
    assert(false);
}

list_head_p list_head_remove(list_head_p lh, node_p n, int side)
{
    label_p lab = node_label(n);
    switch(label_list_compare(lab, lh))
    {
        case 0:
        lh->lb[side] = list_body_remove(lh->lb[side], n);
        return list_head_occupied(lh) ? lh : list_head_pop(lh);

        case 1:
        lh->lh = list_head_remove(lh->lh, n, side);
        return lh;
    }
    assert(false);
}

list_head_p list_head_merge(list_head_p lh_1, list_head_p lh_2)
{
    if(lh_1 == NULL) return lh_2;
    if(lh_2 == NULL) return lh_1;

    switch (list_compare(lh_1, lh_2))
    {
        case -1:
        lh_1->lh = list_head_merge(lh_1->lh, lh_2);
        return lh_1;
    
        case 0:
        lh_1->lb[ELSE] = list_body_merge(lh_1->lb[ELSE], lh_2->lb[ELSE]);
        lh_1->lb[THEN] = list_body_merge(lh_1->lb[THEN], lh_2->lb[THEN]);
        lh_1->lh = list_head_merge(lh_1->lh, lh_2->lh);
        free(lh_2);
        return lh_1;

        case 1:
        lh_2->lh = list_head_merge(lh_1, lh_2->lh);
        return lh_2;
    }
    assert(false);
}
