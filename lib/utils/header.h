#ifndef __utils_H__
#define __utils_H__

#define FPRINT(POINTER,ARGS...) fprintf(POINTER,ARGS)

#define DEFAULT "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define FCOLOR(POINTER,CODE) FPRINT(CODIGO,CODE)

#define STDOUT stdout
#define FCPRINT(POINTER,CODE,ARGS...)   \
    {                                   \
        COLOR(POINTER,CODE);            \
        SAI(POINTER,ARGS);              \
        COLOR(POINTER,DEFAULT);         \
    }
#define PRINT(ARGS...) FPRINT(STDOUT,ARGS)
#define CPRINT(CODE,ARGS...) FCPRINT(STDOUT,CODE,ARGS)
#define FNL(POINTER) FPRINT(POINTER,"\n")
#define NL PRINT("\n")

void exit_program(const char s[]);

#endif
