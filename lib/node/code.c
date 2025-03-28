#include <stdlib.h>

#include "debug.h"
#include "../list/head/struct.h"
#include "../list/body/struct.h"
#include "../macros/assert.h"
#include "../../mods/clu/header.h"



#ifdef DEBUG

#include "../utils/debug.h"
#include "../label/debug.h"
#include "../amp/debug.h"



void node_branch_display(node_p node)
{
    CLU_HANDLER_IS_SAFE(node);

    PRINT("\nnode (branch): %p", node);
    PRINT("\nlabel: ");
    label_display(node->lab);

    PRINT("\nel: %p\tth: %p", BRANCH(node)[ELSE], BRANCH(node)[THEN]);
    PRINT("\n");
}

void node_amp_display(node_p node)
{
    CLU_HANDLER_IS_SAFE(node);

    PRINT("\nnode (amp): %p", node);
    label_display(node->lab);
    PRINT("\namp: ");
    amp_display(AMP(node));
    PRINT("\n");
}

void node_display(node_p node)
{
    CLU_HANDLER_IS_SAFE(node);

    if(label_is_amp(&node->lab))
        node_amp_display(node);
    else
        node_branch_display(node);
}

#endif



node_p node_branch_create(label_t lab)
{
    node_branch_p node = malloc(sizeof(node_branch_t));
    assert(node);

    *node = (node_branch_t)
    {
        .s =
        {
            .lh = NULL,
            .lab = lab
        },
        .branch = {NULL, NULL}
    };
    return ND(node);
}

node_p node_amp_create(amp_t amp)
{
    node_amp_p na = malloc(sizeof(node_amp_t));
    assert(na);

    *na = (node_amp_t){
        .s =
        {
            .lh = NULL,
            .lab =
            {
                .cl = 0,
                .lv = 0
            }
        },
        .amp = amp
    };
    return ND(na);
}



bool node_eq_amp(node_p node_1, node_p node_2)
{
    CLU_HANDLER_IS_SAFE(node_1);
    CLU_HANDLER_IS_SAFE(node_2);

    return amp_eq(AMP(node_1), AMP(node_2));
}

bool node_eq_el(node_p node_1, node_p node_2)
{
    CLU_HANDLER_IS_SAFE(node_1);
    CLU_HANDLER_IS_SAFE(node_2);

    return BRANCH(node_1)[ELSE] == BRANCH(node_2)[ELSE];
}

bool node_eq_th(node_p node_1, node_p node_2)
{
    CLU_HANDLER_IS_SAFE(node_1);
    CLU_HANDLER_IS_SAFE(node_2);

    return BRANCH(node_1)[THEN] == BRANCH(node_2)[THEN];
}



void node_connect(node_p node_top, node_p node_bot, int side)
{
    CLU_HANDLER_IS_SAFE(node_top);
    CLU_HANDLER_IS_SAFE(node_bot);

    assert(BRANCH(node_top)[side] == NULL);
    BRANCH(node_top)[side] = node_bot;
    node_bot->lh = list_head_insert(node_bot->lh, node_top, side);
}

void node_connect_both(node_p node_top, node_p node_el, node_p node_th)
{
    CLU_HANDLER_IS_SAFE(node_top);
    CLU_HANDLER_IS_SAFE(node_el);
    CLU_HANDLER_IS_SAFE(node_th);

    node_connect(node_top, node_el, ELSE);
    node_connect(node_top, node_th, THEN);
}

void node_disconnect(node_p node, int side)
{
    CLU_HANDLER_IS_SAFE(node);

    node_p node_bot = BRANCH(node)[side];
    assert(node_bot);

    BRANCH(node)[side] = NULL;
    node_bot->lh = list_head_remove(node_bot->lh, node, side);
}

void node_disconnect_both(node_p node)
{
    CLU_HANDLER_IS_SAFE(node);

    node_disconnect(node, ELSE);
    node_disconnect(node, THEN);
}



void node_merge(node_p node_1, node_p node_2)
{
    CLU_HANDLER_IS_SAFE(node_1);
    CLU_HANDLER_IS_SAFE(node_2);

    assert(node_1);
    assert(node_2);

    for(list_head_p lh = node_2->lh; lh; lh = lh->next)
    {
        for(int side = 0; side < 2; side ++)
        for(list_body_p lb = lh->lb[side]; lb; lb = lb->next)
            BRANCH(lb->node)[side] = node_1;
    }

    node_1->lh = list_head_merge(node_1->lh, node_2->lh);
    if(!label_is_amp(&node_2->lab))
        node_disconnect_both(node_2);

    free(node_2);
}
