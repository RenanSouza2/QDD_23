#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../utils/debug.h"
#include "../label/debug.h"

void node_str_display(node_c const ns)
{
    PRINT("\n");
    PRINT("\nnode (str) display: %p", ns);
    PRINT("\nlabel: ");
    label_display(node_label(ns));
    PRINT("\n");
}

void node_amp_display(node_c const na)
{
    PRINT("\n");
    PRINT("\nnode (amp) display: %p", na);
    PRINT("\nlabel: %d %d", na->lab.cl, na->lab.lv);
    PRINT("\nlabel: %.2e %.2e", NODE_AMP(na)->re, NODE_AMP(na)->im);
    PRINT("\n");
}

void str_display(str_c const str)
{
    PRINT("%p\t\t%p", str->el, str->th);
}

#endif

node_p node_str_create(label_c const lab)
{
    node_str_p const ns = malloc(sizeof(node_str_t));
    assert(ns);

    *ns = (node_str_t){{{{NULL, NULL}, NULL}, *lab}, {NULL, NULL}};
    return NODE(ns);
}

node_p node_amp_create(amp_c const amp)
{
    node_amp_p na = malloc(sizeof(node_amp_t));
    assert(na);

    *na = (node_amp_t){{{{NULL, NULL}, NULL}, {0, 0}}, *amp};
    return NODE(na);
}



label_c node_label(node_c const n)
{
    return &n->lab;
}



void node_connect(node_p const n1, node_p const n2, int const side)
{
    assert(V_STR(n1)[side] == NULL);
    V_STR(n1)[side] = n2;
    list_head_insert(LH(n2), n1);
}

void node_connect_both(node_p const n, node_p const n_el, node_p const n_th)
{
    assert(NODE_STR(n)->el == NULL);
    assert(NODE_STR(n)->th == NULL);
    *NODE_STR(n) = (str_t){n_el, n_th};
    list_head_insert(LH(n_el), n);
    list_head_insert(LH(n_th), n);
}

void node_disconnect(node_p const n1, node_p const n2)
{
    int const side = SIDE(n1,n2);
    assert(V_STR(n1)[side] == n2);
    V_STR(n1)[side] = NULL;

    list_head_remove(LH(n2), n1);
}

void node_disconnect_both(node_p n)
{
    node_p const n_el = NODE_STR(n)->el;
    node_p const n_th = NODE_STR(n)->th;
    assert(n_el);
    assert(n_th);
    
    list_head_remove(LH(n_el), n);
    list_head_remove(LH(n_th), n);
    *NODE_STR(n) = (str_t){NULL, NULL};
}
