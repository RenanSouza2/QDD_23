#include <stdlib.h>

#include "debug.h"
#include "../../node/struct.h"
#include "../../../mods/clu/header.h"



#ifdef DEBUG

#include "../../utils/debug.h"
#include "../../label/debug.h"
#include "../../node/debug.h"



void list_body_display_item(list_body_p lb)
{
    if(display_header("LIST BODY", lb)) return;

    PRINT("\nnode: %p", lb->node);
    PRINT("\nnext: %p", lb->next);
    PRINT("\n");
}

void list_body_display(list_body_p lb)
{
    int i;
    for(i=0; lb; i++, lb = lb->next)
    {
        PRINT("\n\tnode %3d: %p\t\t", i, lb->node);
        label_display(node_label(lb->node));
    }
}

void list_body_display_full(list_body_p lb)
{
    for(; lb; lb = lb->next)
        node_display(lb->node);
}



bool list_body_variadic(list_body_p lb, int tot_b, va_list * args)
{
    int i = 0;
    for(; lb && (i<tot_b); i++, lb = lb->next)
    {
        node_p node = va_arg(*args, node_p);
        if(lb->node != node)
        {
            PRINT("\n\n\tERROR LIST BODY VECTOR 1 | NODE MISMATCH | %d %d\t\t", i, tot_b);
            return false;
        }
    }

    if(lb)
    {
        PRINT("\n\n\tERROR LIST BODY VECTOR 2 | LIST LONGER | %d\t\t", tot_b);
        return false;
    }

    if(i < tot_b)
    {
        PRINT("\n\n\tERROR LIST BODY VECTOR 3 | LIST SHORTER | %d %d\t\t", i, tot_b);
        return false;
    }

    return true;
}

bool list_body_immed(list_body_p lb, int tot_b, ...)
{
    va_list args;
    va_start(args, tot_b);
    return list_body_variadic(lb, tot_b, &args);
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

list_body_p list_body_create_vector(int size, node_p node[])
{
    list_body_p lb_0 = list_body_create(node[0], NULL);
    
    list_body_p lb = lb_0;
    for(int i=1; i<size; i++)
        lb = lb->next = list_body_create(node[i], NULL);

    return lb_0;
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

    if(lb->node == node)
        return list_body_pop(lb);

    list_body_p lb_0 = lb;
    for(; lb->next; lb = lb->next)
        if(lb->next->node == node)
            break;

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



bool list_body_reduce_node_item(list_body_p lb, node_eq_f node_eq, bool remove, node_p node_1)
{
    CLU_IS_SAFE(lb);
    CLU_IS_SAFE(node_1);

    bool insert = false;
    while(lb->next)
    {
        node_p node_2 = lb->next->node;
        if(!node_eq(node_1, node_2))
        {
            lb = lb->next;
            continue;
        }

        insert = true;
        node_merge(node_1, node_2);

        if(remove)
            lb->next = list_body_pop(lb->next);
    }

    return insert;
}

list_body_p list_body_reduce_node(list_body_p lb, node_eq_f node_eq, bool remove)
{
    CLU_IS_SAFE(lb);

    list_body_p lb_res = NULL;
    for(; lb && lb->next; lb = lb->next)
    {
        node_p node_1 = lb->node;
        if(!list_body_reduce_node_item(lb, node_eq, remove, node_1))
            lb_res = list_body_create(node_1, lb_res);
    }

    return lb_res;
}

list_body_p list_body_reduce_path(node_p node_0, list_body_p lb)
{
    list_body_t lb_0;
    lb_0.next = lb;
    for(lb = &lb_0; ; )
    {
        node_p node = lb->next->node;
        node_p branch[] = NODE_BRANCH(lb->node);
        if(branch[ELSE] != branch[THEN])
            lb = lb->next;
        else
            node_merge(node_0, node);
    }
}
