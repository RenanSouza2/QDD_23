#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdbool.h>

#define DEFAULT "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"

#define FCPRINT(POINTER,CODE,ARGS...)   \
    {                                   \
        fprintf(POINTER,CODE);          \
        fprintf(POINTER,ARGS);          \
        fprintf(POINTER,DEFAULT);       \
    }
#define PRINT(ARGS...) fprintf(stdout,ARGS)
#define CPRINT(CODE,ARGS...) FCPRINT(stdout,CODE,ARGS)

#endif
