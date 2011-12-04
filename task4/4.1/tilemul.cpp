#include <stdlib.h>
#include <algorithm>
using namespace std;

const int S=1024;
const int TILES=32;
const int TILENUM=S/TILES;
const int TILEV=TILES*TILES;

volatile int a [S*S];
volatile int b [S*S];
int r [S*S];

int main()
{
	int i;
	int j;
	int k;
	memset(r,0,S*S);
	for (i=0; i<S; ++i)
	{
		int tilei=(i/TILES)*TILEV*TILENUM+(i%TILES)*TILES;	//tile row
		for (j=0; j<S; ++j)
		{
			int tilej=(j/TILES)*TILEV+j%TILES;		//tile col
			for (k=0; k<S; ++k)
				r[tilei+tilej]+=a[tilei+(k/TILES)*TILEV+k%TILES]*b[(k/TILES)*TILEV*TILENUM+(k%TILES)*TILES+tilej];
		}
	}
	return r[rand()%S*S];
}
