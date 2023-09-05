/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: name family               ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date : xx.xx.2023                   ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <dlfcn.h>  /* dlopen, dlsym, dlclose */
#include <unistd.h> /*      getpid, sleep     */
#include <stdlib.h>  /*     malloc, free      */
#include <stdio.h>  /*         printf         */

#include "memory_mapping_full.h"
/*****************************************************************************/
static const int main_const_static_global = 5;
static int main_static_global =5;
const int main_const_global = 5;
int main_global = 5;
/*****************************************************************************/
static void main_StaticFunction(void)
{
	return;
}
/*****************************************************************************/
extern void main_ExternFunction(void)
{
	return;
}
/*****************************************************************************/
int main(int argc, char **argv, char **env)
{
    int main_local = 5;
    const int main_const_local = 5;

    static int main_static_local = 0;
    static const int main_const_static_local = 0;

    char *main_literal = "my string";
    const char *main_const_liternal = "my const string";

    int main_local_command_number = argc;
    const int main_const_local_command_number = argc;

    char **main_local_command_argv = argv;
    char **main_local_command_env = env;

    int *main_p_heap_var = (int*)malloc(sizeof(int));
    char *main_p_heap_var2 = (char*)malloc(sizeof(char));
    short *main_p_heap_var3 = (short*)malloc(sizeof(short));

	char libpath[70] = "/home/tal/Documents/Infinity/work/tal.aharon/c/ex23/libshared.so";
	void *mylib = dlopen(libpath, RTLD_LOCAL | RTLD_LAZY);
	int (*Map)(int argc, char **, char **) = NULL;
	char *error = NULL;
	int eret = 0;

	if(NULL == mylib)
	{
		fprintf(stderr, "%s\n", dlerror());;
		return (-1);
	}

	dlerror();

	Map = dlsym(mylib, "Mapping");
	if(NULL !=(error = dlerror()))
	{
		fprintf(stderr, "%s\n", error);
		return (-1);
	}

	Map(argc, argv, env);
	
	printf("\nProcess ID: %d\n", getpid());
	sleep(100);
	eret = dlclose(mylib);
	if(eret)
	{
		fprintf(stderr, "%s\n", dlerror());
		return (-1);
	}
	
	/*
	Mapping(argc, argv, env);
	*/
	
	puts("\n\n");
    printf("\n&main_const_static_global %p\n", (void *)&main_const_static_global);
    printf("\n&main_static_global %p\n", (void *)&main_static_global);

    printf("\n&main_const_global %p\n", (void *)&main_const_global);
    printf("\n&main_global %p\n", (void *)&main_global);

    printf("\nmain_StaticFunction %p\n", main_StaticFunction);
    printf("\nmain_ExternFunction %p\n", main_ExternFunction);
    
    printf("\n&main_local %p\n", (void *)&main_local);
    printf("\n&main_const_local %p\n", (void *)&main_const_local);

    printf("\n&main_static_local %p\n", (void *)&main_static_local);
    printf("\n&main_const_static_local %p\n", (void *)&main_const_static_local);

    printf("\nmain_literal %p\n", (void *)main_literal);
    printf("\nmain_const_liternal %p\n", (void *)main_const_liternal);

    printf("\nmain_p_heap_var %p\n", (void *)main_p_heap_var);
    printf("\nmain_p_heap_var2 %p\n", (void *)main_p_heap_var2);
    printf("\nmain_p_heap_var3 %p\n", (void *)main_p_heap_var3);

    printf("\n&main_local_command_number %p\n", (void *)&main_local_command_number);
    printf("\n&main_const_local_command_number %p\n", (void *)&main_const_local_command_number);
    printf("\n&main_local_command_argv %p\n", (void *)main_local_command_argv);
    printf("\n&main_local_command_env %p\n", (void *)main_local_command_env);


    free(main_p_heap_var);
    free(main_p_heap_var2);
    free(main_p_heap_var3);

	return (0);
}
/*****************************************************************************/
