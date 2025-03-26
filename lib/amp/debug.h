#ifndef __AMP_DEBUG_H__
#define __AMP_DEBUG_H__

#include "struct.h"

#ifdef DEBUG

#define AMP_IMMED(RE, IM) ((amp_t){RE, IM})

void amp_display(amp_p amp);

#endif

#endif
