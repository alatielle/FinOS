#include <stdlib.h>
#include <algorithm>
using namespace std;

const int s=1024;

volatile int a [s][s];
volatile int b [s][s];
int r [s][s];

int main()
{
	int i;
	int j;
	int k;
	memset(r,0,s*s);
	for (i=0; i<s; ++i)
		for (j=0; j<s; ++j)
			for (k=0; k<s; ++k)
				r[i][j]+=a[i][k]*b[k][j];
	return r[rand()%s][rand()%s];
}
