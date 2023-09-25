#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../list_body/debug.h"
#include "../../utils/debug.h"
#include "../../../static_utils/mem_report/bin/header.h"

void list_head_display_item(list_head_p lh)
{
    if(display_header("LIST HEAD", lh)) return;

    PRINT("\nnode: %p", LB(lh)->n);
    PRINT("\nlb  : %p", LB(lh)->lb);
    PRINT("\nlh  : %p", lh->lh);
}

void list_head_display(list_head_p lh)
{
    if(lh == NULL) PRINT("\nnull list");

   for(; lh; lh = lh->lh)
    {
        PRINT("\n");
        list_body_display(LB(lh));
    }
    printf("\t\t");
}

bool list_head_vector(list_head_p lh, int tot_h, ...)
{
    va_list args;
    va_start(args, tot_h);

    int i=0;
    for(; lh && (i<tot_h); i++, lh = lh->lh)
    {
        int tot_b = va_arg(args, int);
        if(list_body_vector_vargs(lh->lb, tot_b, args)) continue;

        PRINT("\nERROR LIST HEAD VECTOR 1 | LIST BODY MISMATCH | %d %d\t\t", i, tot_h);
        return false;
    }

    if(lh)
    {
        PRINT("\nERROR LIST HEAD VECTOR 2 | LIST LONGER | %d\t\t", tot_h);
        return false;
    }

    if(i < tot_h)
    {
        PRINT("\nERROR LIST HEAD VECTOR | LIST SHORTER | %d %d\t\t", i, tot_h);
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

list_head_p list_head_create(node_p n, list_head_p lh_next)
{
    list_head_p lh = list_head_create_cold();
    list_body_p lb = n ? list_body_create(n, NULL) : NULL;
    *lh = (list_head_t){lb, lh_next};
    return lh;
}

list_head_p list_head_copy(list_head_p lh)
{
    list_head_p lh_new = list_head_create_cold();
    *lh_new = *lh;
    return lh_new;
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
        list_body_free(lh->lb);
}



label_p list_label(list_head_p lh)
{
    return node_label(lh->lb->n);
}

int label_list_compare(label_p lab, list_head_p lh)
{
    return label_compare(lab, list_label(lh));
}

int list_compare(list_head_p lh_1, list_head_p lh_2)
{
    return label_compare(list_label(lh_1), list_label(lh_2));
}



list_head_p list_head_insert(list_head_p lh, node_p n)
{
    if(lh == NULL) return list_head_create(n, NULL);
    
    label_p lab = node_label(n);
    switch (label_list_compare(lab, lh))
    {
        case -1: return list_head_create(n, lh);
        
        case 0: 
        lh->lb = list_body_create(n, lh->lb);
        return lh;

        case 1:
        lh->lh = list_head_insert(lh->lh, n);
        return lh;
    }
    assert(false);
}

list_head_p list_head_remove(list_head_p lh, node_p n)
{
    label_p lab = node_label(n);
    switch(label_list_compare(lab, lh))
    {
        case 0:
        lh->lb = list_body_remove(lh->lb, n);
        return lh->lb ? lh : list_head_pop(lh);

        case 1:
        lh->lh = list_head_remove(lh->lh, n);
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
    
        case 0:;
        list_head_p lh_next = list_head_merge(lh_1->lh, lh_2->lh);
        lh_1 = LH(list_body_merge(LB(lh_1), LB(lh_2)));
        lh_1->lh = lh_next;
        return lh_1;

        case 1:
        lh_2->lh = list_head_merge(lh_1, lh_2->lh);
        return lh_2;
    }
    assert(false);
}
