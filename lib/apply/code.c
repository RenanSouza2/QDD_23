#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../../mods/clu/header.h"

#include "../node/header.h"
#include "../label/header.h"
#include "../qdd/struct.h"



#ifdef DEBUG
#endif



apply_p apply_create(node_p n1, node_p n2)
{
    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t){NULL, n1, n2, NULL, NULL, NULL, NULL};
    return a;
}

void apply_free(apply_p a)
{
    if(a == NULL) return;

    apply_free(a->a1);
    apply_free(a->a2);
    free(a);
}



apply_p apply_insert(apply_p *a_root, node_p n1, node_p n2)
{
    if(*a_root == NULL)
    {
        apply_p a = *a_root = apply_create(n1, n2);
        return a;
    }

    apply_p a = *a_root;
    if(a->n1 < n1)
        return apply_insert(&a->a1, n1, n2);

    if(a->n1 > n1)
        return apply_insert(&a->a2, n1, n2);
        
    if(a->n2 < n2)
        return apply_insert(&a->a1, n1, n2);

    if(a->n2 > n2)
        return apply_insert(&a->a2, n1, n2);

    return a;
}

apply_p apply_tree_fit_rec(apply_p *a_root, node_p n)
{
    label_t lab = n->lab;
    apply_p a = apply_insert(a_root, n, NULL);
    if(label_is_amp(&lab) || a->el) return a;

    a->el = apply_tree_fit_rec(a_root, BRANCH(n)[ELSE]);
    a->th = apply_tree_fit_rec(a_root, BRANCH(n)[THEN]);
    return a;
}

apply_p apply_tree_fit(node_p n)
{
    apply_p a = NULL;
    apply_tree_fit_rec(&a, n);
    return a;
}

void apply_copy(apply_p a)
{
    if(a == NULL) return;
    a->n = node_copy(a->n1);
    apply_copy(a->a1);
    apply_copy(a->a2);
}

apply_p apply_qdd_fit(qdd_p q)
{
    apply_p a = NULL;
    return apply_tree_fit_rec(&a, q->node);
}

node_p apply_tree_build(apply_p a)
{
    node_p n = a->n;
    if(label_is_amp(&n->lab) || BRANCH(n)[ELSE])
        return n;

    node_p n_el, n_th;
    n_el = apply_tree_build(a->el);
    n_th = apply_tree_build(a->th);
    node_connect_both(n, n_el, n_th);
    return n;
}
