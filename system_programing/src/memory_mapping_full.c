/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: name family               ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date : xx.xx.2023                   ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stdio.h>  /* printf, puts */
#include <stdlib.h> /*              */

#include "memory_mapping_full.h"   /* Internal use */

/*****************************************************************************/
static const int const_static_global = 5;
static int static_global =5;
const int const_global = 5;
int global =5;
/*****************************************************************************/
static void StaticFunction(void)
{
	return;
}
/*****************************************************************************/
extern void ExternFunction(void)
{
	return;
}
/*****************************************************************************/
int Mapping(int argc, char **argv, char **env)
{
    int local = 5;
    const int const_local = 5;

    static int static_local = 0;
    static const int const_static_local = 0;

    char *literal = "my string";
    const char *const_liternal = "my const string";

    int local_command_number = argc;
    const int const_local_command_number = argc;

    char **local_command_argv = argv;
    char **local_command_env = env;

    int *p_heap_var = (int*)malloc(sizeof(int));
    char *p_heap_var2 = (char*)malloc(sizeof(char));
    short *p_heap_var3 = (short*)malloc(sizeof(short));


    printf("\n&const_static_global %p\n", (void *)&const_static_global);
    printf("\n&static_global %p\n", (void *)&static_global);

    printf("\n&const_global %p\n", (void *)&const_global);
    printf("\n&global %p\n", (void *)&global);

    printf("\nStaticFunction %p\n", StaticFunction);
    printf("\nExternFunction %p\n", ExternFunction);
    
    printf("\n&local %p\n", (void *)&local);
    printf("\n&const_local %p\n", (void *)&const_local);

    printf("\n&static_local %p\n", (void *)&static_local);
    printf("\n&const_static_local %p\n", (void *)&const_static_local);

    printf("\nliteral %p\n", (void *)literal);
    printf("\nconst_liternal %p\n", (void *)const_liternal);

    printf("\np_heap_var %p\n", (void *)p_heap_var);
    printf("\np_heap_var2 %p\n", (void *)p_heap_var2);
    printf("\np_heap_var3 %p\n", (void *)p_heap_var3);

    printf("\n&local_command_number %p\n", (void *)&local_command_number);
    printf("\n&const_local_command_number %p\n", (void *)&const_local_command_number);
    printf("\n&local_command_argv %p\n", (void *)local_command_argv);
    printf("\n&local_command_env %p\n", (void *)local_command_env);


    free(p_heap_var);
    free(p_heap_var2);
    free(p_heap_var3);

    return (0);
}
/*****************************************************************************/
