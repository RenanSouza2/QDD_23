#include <stdlib.h>

#include "debug.h"
#include "../../node/struct.h"
#include "../../macros/assert.h"
#include "../../../mods/clu/header.h"



#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"



list_body_p list_body_create_variadic_item(va_list *args)
{
    node_p node = va_arg(*args, node_p);
    return list_body_create(node, NULL);
}

list_body_p list_body_create_variadic_n(int n, va_list *args)
{
    if(n == 0)
        return NULL;

    list_body_p lb_0, lb;
    lb_0 = lb = list_body_create_variadic_item(args);
    for(int i=1; i<n; i++)
        lb = lb->next = list_body_create_variadic_item(args);

    return lb_0;
}

list_body_p list_body_create_variadic(va_list *args)
{
    int n = va_arg(*args, int);
    return list_body_create_variadic_n(n, args);
}

list_body_p list_body_create_immed(int n, ...)
{
    va_list args;
    va_start(args, n);
    return list_body_create_variadic_n(n, &args);
}

void list_body_create_vec_immed(list_body_p lb[], int n, ...)
{
    va_list args;
    va_start(args, n);
    for(int i=0; i<n; i++)
        lb[i] = list_body_create_variadic(&args);
}



void list_body_display_item(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    if(display_header("LIST BODY", lb)) return;

    PRINT("\nnode: %p", lb->node);
    PRINT("\nnext: %p", lb->next);
    PRINT("\n");
}

void list_body_display(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    int i;
    for(i=0; lb; i++, lb = lb->next)
    {
        PRINT("\n\tnode %3d: %p\t\t", i, lb->node);
        label_display(lb->node->lab);
    }
}

void list_body_display_node(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    int i;
    for(i=0; lb; i++, lb = lb->next)
        PRINT("\n\tnode %3d: %p\t\t", i, lb->node);
}

void list_body_display_full(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    for(; lb; lb = lb->next)
        node_display(lb->node);
}



bool list_body_str_inner(list_body_p lb_1, list_body_p lb_2)
{
    CLU_IS_SAFE(lb_1);
    CLU_IS_SAFE(lb_2);

    for(int i=0; lb_1 && lb_2; i++)
    {
        if(lb_1->node != lb_2->node)
        {
            PRINT("\n\n\tLIST BODY ASSERTION ERROR\t| NODE MISMATCH | %p %p | i: %d\t\t", lb_1->node, lb_2->node, i);
            return false;
        }

        lb_1 = lb_1->next;
        lb_2 = lb_2->next;
    }

    if(lb_1)
    {
        PRINT("\n\n\tERROR LIST BODY VECTOR 2 | LIST LONGER\t\t");
        return false;
    }

    return true;
}

bool list_body_str(list_body_p lb_1, list_body_p lb_2)
{
    CLU_IS_SAFE(lb_1);
    CLU_IS_SAFE(lb_2);

    if(!list_body_str_inner(lb_1, lb_2))
    {
        PRINT("\n");
        list_body_display(lb_1);
        list_body_display(lb_2);
        return false;
    }

    list_body_free(lb_1);
    list_body_free(lb_2);
    return true;
}

bool list_body_variadic(list_body_p lb, int n, va_list *args)
{
    list_body_p lb_2 = list_body_create_variadic_n(n, args);
    return list_body_str(lb, lb_2);
}

bool list_body_immed(list_body_p lb, int n, ...)
{
    CLU_IS_SAFE(lb);

    va_list args;
    va_start(args, n);
    return list_body_variadic(lb, n, &args);
}

#endif



list_body_p list_body_create(node_p node, list_body_p next)
{
    CLU_IS_SAFE(next);

    list_body_p lb = malloc(sizeof(list_body_t));
    assert(lb);

    *lb = (list_body_t){
        .node = node, 
        .next = next
    };
    return lb;
}

list_body_p list_body_create_vec(int size, node_p node[])
{
    assert(size);

    list_body_p lb_0 = list_body_create(node[0], NULL);
    
    list_body_p lb = lb_0;
    for(int i=1; i<size; i++)
        lb = lb->next = list_body_create(node[i], NULL);

    return lb_0;
}

list_body_p list_body_copy(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    if(lb == NULL)
        return NULL;

    list_body_p lb_res_0, lb_res;
    lb_res = lb_res_0 = list_body_create(lb->node, NULL);
    for(lb = lb->next; lb; lb = lb->next)
        lb_res = lb_res->next = list_body_create(lb->node, NULL);

    return lb_res_0;
}

list_body_p list_body_pop(list_body_p lb)
{
    CLU_IS_SAFE(lb);

    assert(lb);
    list_body_p lb_aux = lb->next;
    free(lb);
    return lb_aux;
}

void list_body_free(list_body_p lb)
{
    while(lb)
        lb = list_body_pop(lb);
}



list_body_p list_body_remove(list_body_p lb, node_p node)
{
    CLU_IS_SAFE(lb);
    CLU_IS_SAFE(node);

    assert(lb);
    assert(node);

    if(lb->node == node)
        return list_body_pop(lb);

    list_body_p lb_0 = lb;
    for(; lb->next; lb = lb->next)
        if(lb->next->node == node)
            break;

    assert(lb->next);
    lb->next = list_body_pop(lb->next);
    return lb_0;
}

list_body_p list_body_merge(list_body_p lb_1, list_body_p lb_2)
{
    CLU_IS_SAFE(lb_1);
    CLU_IS_SAFE(lb_2);

    if(lb_1 == NULL) return lb_2;
    if(lb_2 == NULL) return lb_1;

    list_body_p lb_2_0 = lb_2;
    for(; lb_2->next; lb_2 = lb_2->next);

    lb_2->next = lb_1;
    return lb_2_0;
}
