#ifndef __AMP_DEBUG_H__
#define __AMP_DEBUG_H__

#include "header.h"

#ifdef DEBUG

#define AMPI(RE, IM) ((amp_t){RE, IM})

bool amplitude(amp_t amp_1, amp_t amp_2);

#endif

#endif
