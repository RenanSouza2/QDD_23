#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "../../mods/clu/header.h"

#include "../node/header.h"
#include "../label/header.h"
#include "../qdd/struct.h"



#ifdef DEBUG

#include <stdarg.h>
#include "../utils/debug.h"

apply_p apply_get(apply_p a[], va_list *args) // TODO rename
{
    int index = va_arg(*args, int);
    return index  ? a[index-1]: NULL;
}

apply_p apply_create_variadic(int N, va_list *args)
{
    if(N == 0)
        return NULL;

    apply_p a[N];
    for(int i=0; i<N; i++)
        a[i] = apply_create(NULL, NULL);

    for(int i=0; i<N; i++)
    {
        a[i]->n1 = va_arg(*args, node_p);
        a[i]->n2 = va_arg(*args, node_p);

        a[i]->el = apply_get(a, args);
        a[i]->th = apply_get(a, args);

        a[i]->a1 = apply_get(a, args);
        a[i]->a2 = apply_get(a, args);
    }

    return a[0];
}

apply_p apply_create_immed(int N, ...)
{
    va_list args;
    va_start(args, N);
    return apply_create_variadic(N, &args);
}



void apply_display_rec(apply_p a)
{
    if(a == NULL)
        return;

    printf("\n%p\t\t%p %p\t\t%p %p\t\t%p %p", a, a->n1, a->n2, a->el, a->th, a->a1, a->a2);
    apply_display_rec(a->a1);
    apply_display_rec(a->a2);
}

void apply_display(apply_p a)
{
    if(a == NULL)
        printf("\nAPPLY EMPTY");
    else
        apply_display_rec(a);
}



bool apply_first_pass(apply_p a_1, apply_p a_2)
{
    CLU_HANDLER_VALIDATE(a_1);
    CLU_HANDLER_VALIDATE(a_2);

    if(a_1 == NULL)
    {
        if(a_2 != NULL)
        {
            printf("\n\n\tAPPLY ASSERT ERROR\t| FIRST | A1 IS NULL A2 IS NOT");
            return false;
        }

        return true;
    }

    if(a_2 == NULL)
    {
        printf("\n\n\tAPPLY ASSERT ERROR\t| FIRST | A1 IS NOT NULL A2 IS");
        return false;
    }

    if(!handler(a_1->n1, a_2->n1))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| FIRST | N1 MISMATCH");
        return false;
    }

    if(!handler(a_1->n2, a_2->n2))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| FIRST | N2 MISMATCH");
        return false;
    }

    if(!apply_first_pass(a_1->a1, a_2->a1))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| FIRST | A1 MISMATCH");
        return false;
    }

    if(!apply_first_pass(a_1->a2, a_2->a2))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| FIRST | A2 MISMATCH");
        return false;
    }

    a_1->n = ND(a_2);
    return true;
}

bool apply_second_pass(apply_p a_1, apply_p a_2)
{
    if(a_1 == NULL)
    {
        if(a_2 != NULL)
        {
            printf("\n\n\tAPPLY ASSERT ERROR\t| SECOND | A1 IS NULL A2 IS NOT");
            return false;
        }

        return true;
    }

    if(a_2 == NULL)
    {
        printf("\n\n\tAPPLY ASSERT ERROR\t| SECOND | A1 IS NOT NULL A2 IS");
        return false;
    }

    if(!handler(a_1->n, a_2))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| SECOND | MISMATCH");
        return false;
    }

    if(!apply_second_pass(a_1->el, a_2->el))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| SECOND | EL MISMATCH");
        return false;
    }

    if(!apply_second_pass(a_1->th, a_2->th))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| SECOND | TH MISMATCH");
        return false;
    }

    return true;
}

bool apply_inner(apply_p a_1, apply_p a_2)
{
    if(!apply_first_pass(a_1, a_2))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| FIRST PASS ERROR");
        return false;
    }
    
    if(!apply_second_pass(a_1, a_2))
    {
        printf("\n\tAPPLY ASSERT ERROR\t| SECOND PASS ERROR");
        return false;
    }

    return true;
}

bool apply(apply_p a_1, apply_p a_2)
{
    if(!apply_inner(a_1, a_2))
    {
        printf("\n\nA 1");
        apply_display(a_1);
        printf("\n\nA 2");
        apply_display(a_2);
        return false;
    }

    apply_free(a_1);
    apply_free(a_2);
    return true;
}

bool apply_immed(apply_p a, int N, ...)
{
    va_list args;
    va_start(args, N);
    apply_p a_2 = apply_create_variadic(N, &args);
    return apply(a, a_2);
}

#endif



apply_p apply_create(node_p n1, node_p n2)
{
    CLU_HANDLER_VALIDATE(n1);
    CLU_HANDLER_VALIDATE(n2);

    apply_p a = malloc(sizeof(apply_t));
    assert(a);

    *a = (apply_t)
    {
        .n  = NULL,
        .n1 = n1,
        .n2 = n2,
        .el = NULL,
        .th = NULL,
        .a1 = NULL,
        .a2 = NULL
    };
    return a;
}

void apply_free(apply_p a)
{
    CLU_HANDLER_VALIDATE(a);

    if(a == NULL)
    return;

    apply_free(a->a1);
    apply_free(a->a2);
    free(a);
}



// returns the apply refering to N1 and N2
apply_p apply_insert(apply_p *a_root, node_p n1, node_p n2)
{
    CLU_HANDLER_VALIDATE(*a_root);
    CLU_HANDLER_VALIDATE(n1);
    CLU_HANDLER_VALIDATE(n2);

    apply_p a = *a_root;
    if(a == NULL)
        return *a_root = apply_create(n1, n2);

    if(a->n1 < n1)
    {
        printf("\napply_insert leaving here 1");
        return apply_insert(&a->a1, n1, n2);
    }

    if(a->n1 > n1)
    {
        printf("\napply_insert leaving here 2");
        return apply_insert(&a->a2, n1, n2);
    }
        
    if(a->n2 < n2)
    {
        printf("\napply_insert leaving here 3");
        return apply_insert(&a->a1, n1, n2);
    }

    if(a->n2 > n2)
    {
        printf("\napply_insert leaving here 4");
        return apply_insert(&a->a2, n1, n2);
    }

    return a;
}

apply_p apply_tree_fit_rec(apply_p *a_root, node_p n)
{
    CLU_HANDLER_VALIDATE(*a_root);
    CLU_HANDLER_VALIDATE(n);

    apply_p a = apply_insert(a_root, n, NULL);
    if(!label_is_amp(&n->lab) && a->el == NULL)
    {
        a->el = apply_tree_fit_rec(a_root, BRANCH(n)[ELSE]);
        a->th = apply_tree_fit_rec(a_root, BRANCH(n)[THEN]);
    }
    return a;
}

apply_p apply_tree_fit(node_p n)
{
    CLU_HANDLER_VALIDATE(n);

    apply_p a = NULL;
    apply_tree_fit_rec(&a, n);
    return a;
}

void apply_copy(apply_p a)
{
    CLU_HANDLER_VALIDATE(a);

    if(a == NULL)
        return;

    a->n = node_copy(a->n1);
    apply_copy(a->a1);
    apply_copy(a->a2);
}

node_p apply_tree_build(apply_p a)
{
    CLU_HANDLER_VALIDATE(a);

    node_p n = a->n;
    if(label_is_amp(&n->lab))
        return n;

    node_connect_both(n, a->el->n, a->th->n);
    return n;
}
