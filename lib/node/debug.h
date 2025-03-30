#ifndef __ND_DEBUG_H__
#define __ND_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG

void node_branch_display(node_p node);
void node_amp_display(node_p node);
void node_display(node_p n);

void node_test_free(node_p node);

#endif

#endif
