#include <stdlib.h>
#include <assert.h>

#include "debug.h"

#ifdef DEBUG
#endif

list_body_p list_body_create(node_p n, list_body_p lb_next)
{
    list_body_p lb;
    lb = malloc(sizeof(list_body_t));
    assert(lb);

    *lb = (list_body_t){n, lb_next};
    return lb;
}

list_head_p list_head_create(node_p n, list_head_p lh_next)
{
    list_head_p lh;
    lh = malloc(sizeof(list_head_t));
    assert(lh);
    
    *lh = (list_head_t){{n, NULL}, lh_next};
    return lh;
}



// void free_list_body_item(list_body_p lb)
#define free_list_body_item(lb) free(lb)

// void free_list_head_item(list_head_p lh)
#define free_list_head_item(lh) free(lh)



void free_list_body(list_body_p lb)
{
    while(lb != NULL)
    {
        list_body_p lb_aux = lb;
        lb = lb->lb;

        free_list_body_item(lb_aux);
    }
}

void free_list_head(list_head_p lh)
{
    while(lh != NULL)
    {
        list_head_p lh_aux = lh;
        lh = lh->lh;

        free_list_body(LB(lh_aux)->lb);
        free_list_head_item(lh_aux);
    }
}
