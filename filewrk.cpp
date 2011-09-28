#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

bool OK=true;
vector <int> dgts;
FILE ** hndls;

void pre(const char* Cause)
{
	printf("Error: %s\n", Cause);
	return;
}

void closediap(int curstage)
{
	int	k;
	for (k=curstage; k>=0; --k)
		if(fclose(hndls[k])) {
			pre("Can't close the file");
		}
	return;
}

int main(int argc, char *argv[])
{
	int	stage,i,j;
	float f;
	int test;
	if (argc<3)
	{
		pre("Too few arguments");
		return 1;
	}
	if ((hndls = (FILE **) malloc((argc-1)*sizeof(FILE *)))==NULL)
	{
		pre("Not enough memory");
		return 1;
	}
	for (stage=0; stage<argc-2; ++stage)
	{
		if ((hndls[stage]=fopen(argv[stage+1], "r"))==NULL)
		{
			pre("Can't open the file for reading");
			closediap(stage-1);
			return 1;
		}
	}
	if ((hndls[stage]=fopen(argv[stage+1], "w"))==NULL)
	{
		pre("Can't open the file for writing");
		closediap(argc-3);
		return 1;
	}
	try {
		for (i=0; i<stage; ++i)
		{
			while ((test=fscanf(hndls[i],"%d",&j))>0)
			{
				dgts.push_back(j);
			}
			if (test!=EOF)
			{
				throw(exception("Bad file content"));
			}
		}
		sort(dgts.begin(), dgts.end());
	} catch (exception e)
	{
		pre(e.what());
		dgts.clear();
		closediap(stage-1);
		return 1;
	}
	for(i=0; i<dgts.size(); i++)
	{
		if ((test=fprintf(hndls[stage],"%d\n", dgts[i]))<0)
		{
			pre("Can't write to the file");
			break;
		}
	}
	closediap(stage);
	free(hndls);
	dgts.clear();
	return 0;
}