#ifndef __UTILS_H__
#define __UTILS_H__

#define DEFAULT "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

#define FPRINT(POINTER,ARGS...) fprintf(POINTER,ARGS)
#define FCOLOR(POINTER,CODE) FPRINT(POINTER,CODE)
#define FCPRINT(POINTER,CODE,ARGS...)   \
    {                                   \
        FCOLOR(POINTER,CODE);           \
        FPRINT(POINTER,ARGS);           \
        FCOLOR(POINTER,DEFAULT);        \
    }
#define PRINT(ARGS...) FPRINT(stdout,ARGS)
#define CPRINT(CODE,ARGS...) FCPRINT(stdout,CODE,ARGS)

#endif
