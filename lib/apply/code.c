#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "debug.h"
#include "../node/struct.h"
#include "../label/struct.h"
#include "../qdd/struct.h"

#ifdef DEBUG

#include "../../static_utils/mem_report/bin/header.h"

#endif

apply_p apply_create(node_p n1, node_p n2, apply_p a_next)
{
    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t){NULL, n1, n2, a, NULL, NULL};
    return a;
}

apply_p apply_insert(apply_p *a_root, node_p n1, node_p n2, bool *is_new)
{
    *is_new = false;

    for(apply_p a = *a_root; a; a = a->a)
        if(a->n1 == n1 && a->n2 == n2)
            return a;

    *is_new = true;
    return *a_root = apply_create(n1, n2, *a_root);
}

apply_p apply_tree_fit(apply_p A[][3], node_p n)
{
    bool is_new;
    label_t lab = *node_label(n);
    apply_p a = apply_insert(&A[IDX(lab)], n, NULL, &is_new);
    if(!is_new) return a;

    a->n = node_copy(n);
    if(label_is_amp(&lab)) return a;

    str_p str = node_str(n);
    a->el = apply_tree_fit(A, str->el);
    a->th = apply_tree_fit(A, str->th);
    return a;
}

apply_p apply_qdd_fit(qdd_p q)
{
    apply_p A[q->qbits + 1][3];
    memset(A, 0, sizeof(A));

    return apply_tree_fit(A, q->n);
}

node_p apply_tree_build(apply_p a)
{
    node_p n = a->n;
    if(node_is_amp(n) || node_str(n)->el) return n;


    node_p n_el, n_th;
    n_el = apply_tree_build(a->el);
    n_th = apply_tree_build(a->th);
    node_connect_both(n, n_el, n_th);
    return n;
}