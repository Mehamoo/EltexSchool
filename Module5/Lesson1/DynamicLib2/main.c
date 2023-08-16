#include <stdio.h>
#include <dlfcn.h>

int main()
{
	int n1, n2;

	n1 = 4;
	n2 = 5;

	void* pExtLib = dlopen("/home/EltexSchool/Module5/Lesson1/DynamicLib2/libexp34dyn.so", RTLD_LAZY);
	if(pExtLib == NULL)
	{
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		return 1;	
	}

	int (*exp3)(int x);
	int (*exp4)(int x);
	
	exp3 = dlsym(pExtLib, "exp3");
	exp4 = dlsym(pExtLib, "exp4");

	printf("%d^3 = %d\n", n1, (*exp3)(n1));
	printf("%d^4 = %d\n", n2, (*exp4)(n2));

	dlclose(pExtLib);

	return 0;
}
