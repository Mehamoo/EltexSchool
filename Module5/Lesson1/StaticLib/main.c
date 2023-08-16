#include <stdio.h>

extern int exp3(int x);
extern int exp4(int x);

int main()
{
	int n1, n2;

	n1 = 4;
	n2 = 5;

	printf("%d^3 = %d\n", n1, exp3(n1));
	printf("%d^4 = %d\n", n2, exp4(n2));

	return 0;
}
