#include <stdio.h>

double g(double,int);

extern void f(double arg)
{
	printf("%f\n",arg);
}

int main()
{
	g(5.99,7);
	return 0;
}
