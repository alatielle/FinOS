#include <stdlib.h>
#include <algorithm>
using namespace std;


const int s=1536;
const int bs=32;

int a [s][s];
int b [s][s];
int r [s][s];

int main()
{
	int n1;
	int n2;
	int n3;
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
	for (n1=0; n1<s; n1+=32)
		for (n2=0; n2<s; n2+=32)
			for (n3=0; n3<s; n3+=32)
				for (i=n1; i<min(n1+32,s); ++i)
					for (j=n2; j<min(n2+32,s); ++j)
						for (k=n3; k<min(n3+32,s); ++k)
							r[i][j]+=a[i][k]*b[k][j];
	//32*32
	return 0;
}
