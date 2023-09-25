#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

#include "../utils/debug.h"
#include "../label/debug.h"

void node_str_display(node_p ns)
{
    PRINT("\n");
    PRINT("\nnode (str) display: %p", ns);
    PRINT("\nlabel: ");
    label_display(node_label(ns));
    PRINT("\n");
}

void node_amp_display(node_p na)
{
    PRINT("\n");
    PRINT("\nnode (amp) display: %p", na);
    PRINT("\nlabel: %d %d", na->lab.cl, na->lab.lv);
    PRINT("\nlabel: %.2e %.2e", ND_AMP(na)->re, ND_AMP(na)->im);
    PRINT("\n");
}

void str_display(str_p str)
{
    PRINT("%p\t\t%p", str->el, str->th);
}

#endif



node_p node_str_create(label_p lab)
{
    node_str_p ns = malloc(sizeof(node_str_t));
    assert(ns);

    *ns = (node_str_t){{NULL, *lab}, {NULL, NULL}};
    return ND(ns);
}

node_p node_amp_create(amp_p amp)
{
    node_amp_p na = malloc(sizeof(node_amp_t));
    assert(na);

    *na = (node_amp_t){{NULL, {0, 0}}, *amp};
    return ND(na);
}

void node_free(node_p n)
{
    list_body_free(LB(n)->lb);
    list_head_free(LH(n)->lh);
    free(n);
}



label_p node_label(node_p n)
{
    return &n->lab;
}

bool node_is_amp(node_p n)
{
    label_p lab = node_label(n);
    return label_is_amp(lab);
}

str_p node_str(node_p n)
{
    assert(!node_is_amp(n));
    return ND_STR(n);
}

amp_p node_amp(node_p n)
{
    assert(node_is_amp(n));
    return ND_AMP(n);
}



void node_connect(node_p n1, node_p n2, int side)
{
    assert(V_STR(n1)[side] == NULL);
    V_STR(n1)[side] = n2;
    list_head_insert(LH(n2), n1);
}

void node_connect_both(node_p n, node_p n_el, node_p n_th)
{
    assert(ND_STR(n)->el == NULL);
    assert(ND_STR(n)->th == NULL);
    *ND_STR(n) = (str_t){n_el, n_th};
    list_head_insert(LH(n_el), n);
    list_head_insert(LH(n_th), n);
}

void node_disconnect(node_p n1, node_p n2)
{
    int side = SIDE(n1,n2);
    assert(V_STR(n1)[side] == n2);
    V_STR(n1)[side] = NULL;

    list_head_remove(LH(n2), n1);
}

void node_disconnect_both(node_p n)
{
    node_p n_el = ND_STR(n)->el;
    node_p n_th = ND_STR(n)->th;
    assert(n_el);
    assert(n_th);
    
    list_head_remove(LH(n_el), n);
    list_head_remove(LH(n_th), n);
    *ND_STR(n) = (str_t){NULL, NULL};
}



void node_merge(node_p n1, node_p n2)
{
    assert(n1);
    assert(n2);
    
    if(LB(n2)->n == NULL)
    {
        free(n2);
        return;
    }

    for(list_head_p lh = LH(n2); lh; lh = lh->lh)
    for(list_body_p lb = LB(lh); lb; lb = lb->lb)
    {
        str_p str = node_str(lb->n);
        if(str->el == n2) str->el = n1;
        if(str->th == n2) str->th = n1;
    }

    if(LB(n1)->n == NULL)
    {
        *LH(n1) = *LH(n2);
        free(n2);
        return;
    }

    list_head_merge(LH(n1), LH(n2));
}

