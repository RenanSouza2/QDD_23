#include <stdlib.h>

#include "debug.h"
#include "../list/list_head/struct.h"
#include "../list/list_body/struct.h"
#include "../macros/assert.h"
#include "../../mods/clu/header.h"



#ifdef DEBUG

#include "../utils/debug.h"
#include "../label/debug.h"
#include "../amp/debug.h"



#define NODE_BRANCH(NODE) (((node_branch_p)(NODE))->branch)



void node_branch_display(node_p ns)
{
    PRINT("\nnode (branch) display: %p", ns);
    PRINT("\nlabel: ");
    label_display(node_label(ns));
    
    branch_p branch = node_branch(ns);
    PRINT("\nel: %p\tth: %p", branch->el, branch->th);
    PRINT("\n");
}

void node_amp_display(node_p na)
{
    PRINT("\nnode (amp) display: %p", na);
    PRINT("\nlabel: %d %d", na->lab.cl, na->lab.lv);
    PRINT("\namp: ");
    amp_display(node_amp(na));
    PRINT("\n");
}

void node_display(node_p n)
{
    if(node_is_amp(n)) node_amp_display(n);
    else               node_branch_display(n);
}

void branch_display(branch_p branch)
{
    PRINT("%p\t\t%p", branch->el, branch->th);
}

#endif



node_p node_branch_create(label_p lab)
{
    node_branch_p ns = malloc(sizeof(node_branch_t));
    assert(ns);

    *ns = (node_branch_t){{NULL, *lab}, {NULL, NULL}};
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
    list_head_free(n->lh);
    free(n);
}



bool node_is_amp(node_p n)
{
    label_p lab = node_label(n);
    return label_is_amp(lab);
}

node_p node_first(node_p n)
{
    return list_head_first(n->lh);
}

bool node_amp_eq(node_p n1, node_p n2)
{
    return amp_eq(node_amp(n1), node_amp(n2));
}

bool node_el_eq(node_p n1, node_p n2)
{
    branch_p branch_1 = node_branch(n1);
    branch_p branch_2 = node_branch(n2);
    return branch_1->el == branch_2->el;
}

bool node_th_eq(node_p n1, node_p n2)
{
    branch_p branch_1 = node_branch(n1);
    branch_p branch_2 = node_branch(n2);
    return branch_1->th == branch_2->th;
}



void node_connect(node_p n1, node_p n0, int side)
{
    assert(V_STR(n1)[side] == NULL);
    V_STR(n1)[side] = n0;
    n0->lh = list_head_insert(n0->lh, n1, side);
}

void node_connect_both(node_p n, node_p n_el, node_p n_th)
{
    branch_p branch = node_branch(n);
    assert(branch->el == NULL);
    assert(branch->th == NULL);
    *branch = (branch_t){n_el, n_th};
    n_el->lh = list_head_insert(n_el->lh, n, ELSE);
    n_th->lh = list_head_insert(n_th->lh, n, THEN);
}

void node_disconnect(node_p n, int side)
{
    node_p n0 = V_STR(n)[side];
    assert(n0);

    V_STR(n)[side] = NULL;
    n0->lh = list_head_remove(n0->lh, n, side);
}

void node_disconnect_both(node_p n)
{
    branch_p branch = node_branch(n);
    node_p n_el = branch->el;
    node_p n_th = branch->th;
    assert(n_el);
    assert(n_th);
    *branch = (branch_t){NULL, NULL};
    
    n_el->lh = list_head_remove(n_el->lh, n, ELSE);
    n_th->lh = list_head_remove(n_th->lh, n, THEN);
}



void node_merge(node_p n1, node_p n2)
{
    assert(n1);
    assert(n2);

    for(list_head_p lh = n2->lh; lh; lh = lh->lh)
    {
        for(list_body_p lb = lh->lb[ELSE]; lb; lb = lb->lb)
            NODE_BRANCH(lb->n)->
    }
    for(int side = 0; side < 2; side++)
    for(list_body_p lb = lh->lb[side]; lb; lb = lb->lb)
    {
        branch_p branch = node_branch(lb->n);
        if(side == ELSE) branch->el = n1;
        else             branch->th = n1;
    }

    n1->lh = list_head_merge(n1->lh, n2->lh);
    if(!node_is_amp(n2))
        node_disconnect_both(n2);

    free(n2);
}
