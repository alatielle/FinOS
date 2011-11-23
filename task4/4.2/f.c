#include <stdio.h>

double g(double,int);

void f(double arg)
{
	printf("%f\n",arg);
	return;
}

int main()
{
	f(g(5.99,7));
	return 0;
}
