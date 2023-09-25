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

    *ns = (node_str_t){{{NULL, NULL}, *lab}, {NULL, NULL}};
    return ND(ns);
}

node_p node_amp_create(amp_p amp)
{
    node_amp_p na = malloc(sizeof(node_amp_t));
    assert(na);

    *na = (node_amp_t){{{NULL, NULL}, {0, 0}}, *amp};
    return ND(na);
}

void node_free(node_p n)
{
    list_head_free(n->lh[ELSE]);
    list_head_free(n->lh[THEN]);
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

node_p node_first(node_p n)
{
    if(n->lh[ELSE]) return LB(n->lh[ELSE])->n;
    if(n->lh[THEN]) return LB(n->lh[THEN])->n;
    return NULL;
}

bool node_amp_eq(node_p n1, node_p n2)
{
    return amp_eq(node_amp(n1), node_amp(n2));
}

bool node_str_eq(node_p n1, node_p n2)
{
    return str_eq(node_str(n1), node_str(n2));
}



void node_connect(node_p n1, node_p n2, int side)
{
    assert(V_STR(n1)[side] == NULL);
    V_STR(n1)[side] = n2;
    n2->lh[side] = list_head_insert(n2->lh[side], n1);
}

void node_connect_both(node_p n, node_p n_el, node_p n_th)
{
    str_p str = node_str(n);
    assert(str->el == NULL);
    assert(str->th == NULL);
    *ND_STR(n) = (str_t){n_el, n_th};
    n_el->lh[ELSE] = list_head_insert(n_el->lh[ELSE], n);
    n_th->lh[THEN] = list_head_insert(n_th->lh[THEN], n);
}

void node_disconnect(node_p n, int side)
{
    assert(n);

    node_p n1 = V_STR(n)[side];
    assert(n1);

    V_STR(n)[side] = NULL;
    n1->lh[side] = list_head_remove(n1->lh[side], n);
}

void node_disconnect_both(node_p n)
{
    str_p str = node_str(n);
    node_p n_el = str->el;
    node_p n_th = str->th;
    assert(n_el);
    assert(n_th);
    
    n_el->lh[ELSE] = list_head_remove(n_el->lh[ELSE], n);
    n_th->lh[THEN] = list_head_remove(n_th->lh[THEN], n);
    *str = (str_t){NULL, NULL};
}



void node_merge(node_p n1, node_p n2)
{
    assert(n1);
    assert(n2);

    for(int side = 0; side < 2; side ++)
    for(list_head_p lh = n2->lh[side]; lh; lh = lh->lh)
    for(list_body_p lb = LB(lh); lb; lb = lb->lb)
    {
        str_p str = node_str(lb->n);
        if(str->el == n2) str->el = n1;
        if(str->th == n2) str->th = n1;
    }

    n1->lh[ELSE] = list_head_merge(n1->lh[ELSE], n2->lh[ELSE]);
    n1->lh[THEN] = list_head_merge(n1->lh[THEN], n2->lh[THEN]);
}
