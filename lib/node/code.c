#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include "../utils/debug.h"

void node_str_display(node_p ns)
{
    PRINT("\n");
    PRINT("\nnode (str) display: %p", ns);
    PRINT("\nlabel: %d %d", ns->lab.cl, ns->lab.lv);
    PRINT("\n");
}

void node_amp_display(node_p na)
{
    PRINT("\n");
    PRINT("\nnode (amp) display: %p", na);
    PRINT("\nlabel: %d %d", na->lab.cl, na->lab.lv);
    PRINT("\nlabel: %.2e %.2e", NODE_AMP(na)->re, NODE_AMP(na)->im);
    PRINT("\n");
}

void str_display(str_p str)
{
    PRINT("%p\t\t%p", str->el, str->th);
}

#endif

node_p node_str_create(int cl, int lv)
{
    node_str_p ns;
    ns = malloc(sizeof(node_str_t));
    assert(ns);

    *ns = (node_str_t){{{{NULL, NULL}, NULL}, {cl, lv}}, {NULL, NULL}};
    return NODE(ns);
}

node_p node_amp_create(number_t re, number_t im)
{
    node_amp_p na;
    na = malloc(sizeof(node_amp_t));
    assert(na);

    *na = (node_amp_t){{{{NULL, NULL}, NULL}, {0, 0}}, {re, im}};
    return NODE(na);
}

// void node_free(node_p n)
#define node_free(n) free(n)

label_p node_label(node_p n)
{
    return &n->lab;
}