#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG

#include <stdio.h>

void node_str_display(node_p ns)
{
    printf("\n");
    printf("\nnode (str) display: %p", ns);
    printf("\nlabel: %d %d", ns->lab.cl, ns->lab.lv);
    printf("\n");
}

void node_amp_display(node_p na)
{
    printf("\n");
    printf("\nnode (amp) display: %p", na);
    printf("\nlabel: %d %d", na->lab.cl, na->lab.lv);
    printf("\nlabel: %.2e %.2e", NODE_AMP(na)->re, NODE_AMP(na)->im);
    printf("\n");
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
