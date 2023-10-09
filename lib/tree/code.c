#include <stdlib.h>

#include "debug.h"
#include "../apply/header.h"
#include "../node/struct.h"
#include "../list/list_body/struct.h"
#include "../list/list_head/struct.h"

#ifdef DEBUG

#include <string.h>

#include "../utils/header.h"
#include "../node/debug.h"
#include "../label/debug.h"
#include "../list/list_head/debug.h"
#include "../../static_utils/mem_report/bin/header.h"

void tree_display(node_p n)
{
    list_head_p lh = tree_enlist(n);
    lh = list_head_invert(lh);
    list_head_display(lh);
}

bool tree_rec(node_p n, node_p n1, node_p n2)
{
    assert(n1);
    assert(n2);
    
    if(n && (list_head_first(n1->lh) != n)) return true;
    
    if(label_compare(node_label(n1), node_label(n2)) != 0)
    {
        PRINT("\nERROR TREE ASSSERT 1 | LABEL MISMATCH | ");
        label_display(node_label(n1));
        printf(" ");
        label_display(node_label(n2));
        printf("\t\t");
        return false;
    }
    
    if(node_is_amp(n2))
    {
        if(!amp_eq(node_amp(n1), node_amp(n2)))
        {
            PRINT("\nERROR TREE ASSSERT 2 | AMP MISMATCH");
            return false;
        }
        return true;
    }

    for(int side=0; side<2; side++)
    {
        if(!tree_rec(n1, V_STR(n1)[side], V_STR(n2)[side]))
        {
            PRINT("\nERROR TREE ASSSERT 3 | %s MISMATCH", side ? "THEN" : "ELSE");
            return false;
        }
    }

    return true;
}

bool tree(node_p n1, node_p n2)
{
    return tree_rec(NULL, n1, n2);
}

node_p tree_create_variadic(int qbits, va_list args)
{
    node_p *N[qbits+1][3];
    memset(N, 0, sizeof(N));

    int size = va_arg(args, int);
    N[0][0] = malloc(size * sizeof(node_p));
    node_p n;
    for(int i=0; i<size; i++)
    {
        amp_t amp = va_arg(args, amp_t);
        N[0][0][i] = n = node_amp_create(&amp);
    }

    int max = va_arg(args, int);
    for(int i=0; i<max; i++)
    {
        label_t lab = va_arg(args, label_t);
        int size = va_arg(args, int);

        node_p *N_1 = N[IDX(lab)] = malloc(size * sizeof(node_p));
        for(int j=0; j<size; j++)
        {
            N_1[j] = n = node_str_create(&lab);
            for(int side=0; side<2; side++)
            {
                label_t lab_0 = va_arg(args, label_t);
                node_p *N_0 = N[IDX(lab_0)];
                assert(N_0);

                int index = va_arg(args, int);
                node_connect(n, N_0[index], side);
            }
        }
    }

    for(int i=0; i<=qbits; i++)
    for(int j=0; j<3; j++)
    if(N[i][j]) free(N[i][j]);

    return n;
}

node_p tree_create_description(int qbits, ...)
{
    va_list args;
    va_start(args, qbits);
    return tree_create_variadic(qbits, args);
}

#endif

void tree_free(node_p n)
{
    assert(n);

    if(n->lh) return;

    if(node_is_amp(n))
    {
        free(n);
        return;
    }

    str_p str = node_str(n);
    node_p n1 = str->el;
    node_p n2 = str->th;
    node_disconnect_both(n);
    free(n);

    tree_free(n1);
    tree_free(n2);
}

list_head_p tree_enlist_rec(list_head_p lh, node_p n0, node_p n)
{
    if(n0 && (node_first(n) != n0)) return lh;

    lh = list_head_insert(lh, n, ELSE);
    if(node_is_amp(n)) return lh;

    str_p str = node_str(n);
    lh = tree_enlist_rec(lh, n, str->el);
    return tree_enlist_rec(lh, n, str->th);
}

list_head_p tree_enlist(node_p n)
{
    assert(n);

    return tree_enlist_rec(NULL, NULL, n);
}

list_body_p tree_enlist_amplitude(node_p n)
{
    list_head_p lh = tree_enlist(n);
    list_body_p lb = lh->lb[ELSE];
    list_head_free(lh->lh);
    free(lh);
    return lb;
}

node_p tree_copy(node_p n)
{
    apply_p a = apply_tree_fit(n);
    apply_copy(a);
    n = apply_tree_build(a);
    apply_free(a);
    return n;
}
