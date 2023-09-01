#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../../utils/debug.h"
#include "../list_body/debug.h"

void list_head_display_item(list_head_p lh)
{
    if(display_header("LIST HEAD", lh)) return;

    PRINT("\nnode: %p", LB(lh)->n);
    PRINT("\nlb  : %p", LB(lh)->lb);
    PRINT("\nlh  : %p", lh->lh);

}

void list_head_display(list_head_p lh)
{
   for(; lh; lh = lh->lh)
    {
        PRINT("\n");
        list_body_display(LB(lh));
    }
    printf("\t\t");
}

#endif

list_head_p list_head_create_cold()
{
    list_head_p lh;
    lh = malloc(sizeof(list_head_t));
    assert(lh);
    return lh;
}

list_head_p list_head_create(node_p n, list_head_p lh_next)
{
    list_head_p lh = list_head_create_cold();
    *lh = (list_head_t){{n, NULL}, lh_next};
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
    while(lh)
        lh = list_head_pop(lh);
}



label_p list_label(list_head_p lh)
{
    return node_label(LB(lh)->n);
}

int label_list_compare(label_p lab, list_head_p lh)
{
    return label_compare(lab, list_label(lh));
}

int list_compare(list_head_p lh_1, list_head_p lh_2)
{
    return label_compare(list_label(lh_1), list_label(lh_2));
}



void list_head_insert(list_head_p lh, node_p n)
{
    if(LB(lh)->n == NULL)
    {
        LB(lh)->n = n;
        return;
    }

    label_p lab;
    lab = node_label(n);
    if(label_list_compare(lab, lh) == 0)
    {
        LB(lh)->lb = list_body_create(n, LB(lh)->lb);
        return;
    }

    if(label_list_compare(lab, lh) < 0)
    {
        list_head_p lh_aux = list_head_copy(lh);
        *lh = (list_head_t){{n, NULL}, lh_aux};
        return;
    }

    for(; lh->lh; lh = lh->lh)
        if(label_list_compare(lab, lh->lh) < 0)
            break;

    if(label_list_compare(lab, lh) != 0)
    {
        lh->lh = list_head_create(n, lh->lh);
        return;
    }

    LB(lh)->lb = list_body_create(n, LB(lh)->lb);
}

void list_head_remove(list_head_p lh, node_p n)
{
    label_p lab = node_label(n);
    if(label_list_compare(lab, lh) == 0)
    {
        list_head_p lh_aux = lh->lh;
        if(!list_body_remove(LB(lh), n) || lh_aux == NULL) return;
        
        *lh = *lh_aux;
        free(lh_aux);
        return;
    }

    for(; lh->lh; lh = lh->lh)
        if(label_list_compare(lab, lh->lh) <= 0)
            break;

    list_head_p lh_aux = lh->lh;
    assert(lh_aux);
    assert(label_list_compare(lab, lh_aux) == 0);

    if(!list_body_remove(LB(lh_aux), n)) return;

    lh->lh = lh_aux->lh;
    free(lh_aux);
}

void list_head_merge(list_head_p lh_1, list_head_p lh_2)
{
    if(list_compare(lh_2, lh_1) < 0)
    {
        list_head_t lh;
         lh   = *lh_1;
        *lh_1 = *lh_2;
        *lh_2 =  lh;
    }

    if(list_compare(lh_1, lh_2) == 0)
    {
        list_body_merge(LB(lh_1), LB(lh_2));
        lh_2 = list_head_pop(lh_2);
    }

    list_head_p lh = lh_1;
    lh_1 = lh->lh;

    while(lh_1 && lh_2)
    {
        switch (list_compare(lh_1, lh_2))
        {
            case -1:
            lh = lh->lh = lh_1;
            lh_1 = lh_1->lh;
            break;
        
            case 0:
            lh = lh->lh = lh_1;
            list_body_merge(LB(lh), LB(lh_2));

            lh_1 = lh_1->lh;
            lh_2 = list_head_pop(lh_2);
            break;

            case 1:
            lh = lh->lh = lh_2;
            lh_2 = lh_2->lh;
            break;
        }
    }

    lh->lh = (list_head_p)((long)lh_1 | (long)lh_2);
}
