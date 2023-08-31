#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../label/header.h"
#include "debug.h"

#ifdef DEBUG

#include "../utils/debug.h"
#include "../label/debug.h"
#include "../node/debug.h"

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

list_body_p list_body_create(node_p n, list_body_p lb_next)
{
    list_body_p lb;
    lb = malloc(sizeof(list_body_t));
    assert(lb);

    *lb = (list_body_t){n, lb_next};
    return lb;
}



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



// void list_body_free_item(list_body_p lb)
#define list_body_free_item(lb) free(lb)

// void list_head_free_item(list_head_p lh)
#define list_head_free_item(lh) free(lh)



void free_list_body(list_body_p lb)
{
    while(lb != NULL)
    {
        list_body_p lb_aux = lb;
        lb = lb->lb;

        list_body_free_item(lb_aux);
    }
}

void free_list_head(list_head_p lh)
{
    while(lh != NULL)
    {
        list_head_p lh_aux = lh;
        lh = lh->lh;

        free_list_body(LB(lh_aux)->lb);
        list_head_free_item(lh_aux);
    }
}



label_p list_label(list_head_p lh)
{
    return node_label(LB(lh)->n);
}

int label_list_compare(label_p lab, list_head_p lh)
{
    return label_compare(lab, list_label(lh));
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
        list_body_free_item(lb_aux);
        return false;
    }

    for(; lb->lb; lb = lb->lb)
        if(lb->lb->n == n)
            break;

    assert(lb->lb);
    
    list_body_p lb_aux = lb->lb;
    lb->lb = lb_aux->lb;
    list_body_free_item(lb_aux);
    return false;
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

    for(;lh->lh; lh = lh->lh)
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
        list_head_free_item(lh_aux);
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
    list_head_free_item(lh_aux);
}

void list_head_merge(list_head_p lh_1, list_head_p lh_2)
{
    if(label_list_compare(L_LABEL(lh_2), lh_1) < 0)
    {
        DEBUG(DEBUG_TRANSFERE,"\nTrocando");

        lista_head lh;
        COPY_STRUCT(&lh, n1,lista_head);
        COPY_STRUCT( n1, n2,lista_head);
        COPY_STRUCT( n2,&lh,lista_head);
    }

    DEBUG(DEBUG_TRANSFERE,"\nBuscando posicao para inserir n2");
    lista_head *lh, *lh_1, *lh_2;
    label *lab;
    lab = NLABEL(n2);
    for(lh = HEAD(n1), lh_1 = lh->lh; lh_1 != NULL; lh = lh_1, lh_1 = lh->lh)
        if(COMPARE_LABEL(lab,<, NLABEL(lh_1)))
            break;

    DEBUG(DEBUG_TRANSFERE,"\nInserindo n2");
    lh_2 = HEAD(n2)->lh;
    if(COMPARE_LABEL(lab,==,NLABEL(lh)))
    {
        lista_body *lb;
        for(lb = BODY(n2); lb->lb != NULL; lb = lb->lb);
        lb->lb = BODY(lh)->lb;
        BODY(lh)->lb = cria_lista_body_copia(BODY(n2));
    }
    else
    {
        lh->lh = cria_lista_head_copia(HEAD(n2));
        lh = lh->lh;
    }
    LIBERA(libera_no,n2);

    while(lh_1 != NULL & lh_2 != NULL)
    {
        if(COMPARE_LABEL(NLABEL(lh_1), <, NLABEL(lh_2)))
        {
            lh->lh = lh_1;
            lh     = lh->lh;
            lh_1   = lh_1->lh;
            continue;
        }

        lh->lh = lh_2;
        lh     = lh->lh;
        lh_2   = lh_2->lh;

        if(COMPARE_LABEL(NLABEL(lh_1), ==, NLABEL(lh)))
        {
            lista_body *lb, *lb_next;
            for(lb = BODY(lh), lb_next = lb->lb; lb_next != NULL; lb = lb_next, lb_next = lb->lb);
            lb->lb = cria_lista_body_copia(BODY(lh_1));

            lista_head *lh_aux;
            lh_aux = lh_1;
            lh_1   = lh_1->lh;
            LIBERA(libera_lista_head_item,lh_aux);

            continue;
        }
    }

    if(lh_1 != NULL)
        lh->lh = lh_1;
    else if(lh_2 != NULL)
        lh->lh = lh_2;

    DEBUG(DEBUG_TRANSFERE,"\nSAINDO TRANSFERENCIA");
}
