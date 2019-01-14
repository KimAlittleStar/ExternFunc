#ifndef EXTERNFUNC_H_INCLUDED
#define EXTERNFUNC_H_INCLUDED

#include "stdio.h"
#include "string.h"

typedef struct
{
    const char * FuncName;
    void *( (*func)(void* args,...));
    const char * fmt;
    const char * Introduction;
} CALLFUNCTIONTABLE;

#define EXPOTRFUNC(NAME,FUNC,FTM,INTRO) {#NAME,(void *(*)(void* args,...))FUNC,#FTM,#INTRO}

extern const CALLFUNCTIONTABLE functable[];

void ExternFunc_excute(char* str);


#endif // EXTERNFUNC_H_INCLUDED
