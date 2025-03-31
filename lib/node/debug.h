#ifndef __ND_DEBUG_H__
#define __ND_DEBUG_H__

#include "header.h"
#include "struct.h"

#ifdef DEBUG

<<<<<<< HEAD
void node_str_display(node_p ns);
void node_amp_display(node_p na);
void node_vector_free(int len, node_p N[]);
=======
void node_display_short(node_p node);
void node_display(node_p n);
>>>>>>> main

void node_test_free(node_p node);

#endif

#endif
