#include <stdlib.h>
#include <algorithm>
using namespace std;


const int s=1536;

int a [s][s];
int b [s][s];
int r [s][s];

int main()
{
	int i;
	int j;
	int k;
	for (i=0; i<s; ++i)
		for (j=0; j<s; ++j)
		{
			r[i][j]=0;
			a[i][j]=rand()%32000;
			b[i][j]=rand()%32000;
		}
	for (i=0; i<s; ++i)
		for (j=0; j<s; ++j)
			for (k=0; k<s; ++k)
				r[i][j]+=a[i][k]*b[k][j];
	return 0;
}
