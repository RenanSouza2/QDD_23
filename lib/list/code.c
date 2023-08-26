#include <stdlib.h>
#include <assert.h>

#include "../label/header.h"
#include "debug.h"

#ifdef DEBUG
#endif

list_body_p list_body_create(node_p n, list_body_p lb_next)
{
    list_body_p lb;
    lb = malloc(sizeof(list_body_t));
    assert(lb);

    *lb = (list_body_t){n, lb_next};
    return lb;
}



list_head_p list_head_create_ampty()
{
    list_head_p lh;
    lh = malloc(sizeof(list_head_t));
    assert(lh);
    return lh;
}

list_head_p list_head_create(node_p n, list_head_p lh_next)
{
    list_head_p lh = list_head_create_ampty();
    *lh = (list_head_t){{n, NULL}, lh_next};
    return lh;
}

list_head_p list_head_copy(list_head_p lh)
{
    list_head_p lh_new = list_head_create_ampty();
    *lh_new = *lh;
    return lh_new;
}


// void free_list_body_item(list_body_p lb)
#define free_list_body_item(lb) free(lb)

// void free_list_head_item(list_head_p lh)
#define free_list_head_item(lh) free(lh)



void free_list_body(list_body_p lb)
{
    while(lb != NULL)
    {
        list_body_p lb_aux = lb;
        lb = lb->lb;

        free_list_body_item(lb_aux);
    }
}

void free_list_head(list_head_p lh)
{
    while(lh != NULL)
    {
        list_head_p lh_aux = lh;
        lh = lh->lh;

        free_list_body(LB(lh_aux)->lb);
        free_list_head_item(lh_aux);
    }
}



label_p list_label(list_head_p lh)
{
    return node_label(LB(lh)->n);
}

int list_label_compare(label_p lab, list_head_p lh)
{
    return label_compare(lab, list_label(lh));
}



void list_include_node(list_head_p lh, node_p n)
{
    if(LB(lh)->n == NULL)
    {
        LB(lh)->n = n;
        return;
    }

    label_p lab;
    lab = node_label(n);

    if(list_label_compare(lab, lh) == 0)
    {
        LB(lh)->lb = list_body_create(n, LB(lh)->lb);
        return;
    }

    if(list_label_compare(lab, lh) < 0)
    {
        list_head_p lh_aux = list_head_copy(lh);
        *lh = (list_head_t){{n, NULL}, lh_aux};
        return;
    }

    while(lh->lh && list_label_compare(lab, lh->lh) < 0)
        lh = lh->lh;

    if(list_label_compare(lab, lh) != 0)
    {
        lh->lh = list_head_create(n, lh->lh);
        return;
    }

    LB(lh)->lb = list_body_create(n, LB(lh)->lb);
}
