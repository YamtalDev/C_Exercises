#include <dlfcn.h>  /* dlopen, dlsym, dlclose */
#include <stdio.h>  /*         printf         */
#include <unistd.h>

#include "duplicate_global_variable.h" /*       Internal use     */
/*****************************************************************************/
int Explicit(void);
/*****************************************************************************/
int main(void)
{

/*
	PrintGlobalVariableAddress();
	Foo1();
	Foo2();
*/
	Explicit();
	printf("Process ID: %d\n", getpid());
	sleep(150);

	return (0);
}

int Explicit(void)
{
	char libpath1[70] = "/home/tal/Documents/Infinity/work/tal.aharon/c/ex22/libni1.so";
	char libpath2[70] = "/home/tal/Documents/Infinity/work/tal.aharon/c/ex22/libni2.so";

	void *mylib1 = dlopen(libpath1, RTLD_LOCAL | RTLD_LAZY);


	void (*foo1)(void) = NULL;
	void (*foo2)(void) = NULL;
	char *error1 = NULL;
	char *error2 = NULL;
	int eret1 = 0;
	int eret2 = 0;

	if(NULL == mylib1)
	{
		fprintf(stderr, "%s\n", dlerror());;
		return (-1);
	}

	dlerror();

	foo1 = (void (*)(void))dlsym(mylib1, "Foo1");
	if(NULL !=(error1 = dlerror()))
	{
		fprintf(stderr, "%s\n", error1);
		return (-1);
	}

	PrintGlobalVariableAddress();
	foo1();

	eret1 = dlclose(mylib1);
	if(eret1)
	{
		fprintf(stderr, "%s\n", dlerror());
		return (-1);
	}

	void *mylib2 = dlopen(libpath2, RTLD_LOCAL | RTLD_LAZY);
	if(NULL == mylib2)
	{
		fprintf(stderr, "%s\n", dlerror());
		return (-1);
	}

	dlerror();

	foo2 = (void (*)(void))dlsym(mylib2, "Foo2");

	if(NULL !=(error2 = dlerror()))
	{
		fprintf(stderr, "%s\n", error2);
		return (-1);
	}

	foo2();

	eret2 = dlclose(mylib2);
	if(eret2)
	{
		fprintf(stderr, "%s\n", dlerror());
		return (-1);
	}
}
/*****************************************************************************/
