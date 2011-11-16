#include <stdio.h>
#include <stdlib.h>

voif f(double arg)
{
	printf("%f",arg);
	return;
}

extern __inline__ double g(int arg0, double arg1);

int main()
{
	f(g(10,0.5));
	return 0;
}