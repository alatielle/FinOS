#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

bool OK=true;
vector <int> dgts;
FILE ** hndls;

void pre(char* Cause)
{
	printf("Error: %s\n", Cause);
	return;
}

void closediap(int curstage)
{
	int	k;
	for (k=curstage; k>=0; --k)
		if (hndls[k]!=NULL)
			if (fclose(hndls[k])) {
				pre("Can't close the file");
			}
	free(hndls);	
	return;
}

int main(int argc, char *argv[])
{
	int	stage,i,j;
	int test;
	/* ������ � ����, ��� ��������, ���������� �� � ��� ���������� ��� ������.
	��� ����� ���� ��� ������ ��������������� ����� � ��� ������� ���� ���� ��� ������.
	������, ���������� ������ ���� 3 � ������ (������ ���������� �������� ��� ���������). */
	if (argc<3)
	{
		// � ������ ������� ������� ��������� �� ������ � ������� ��������� pre() � �������� �������� ������.
		pre("Too few arguments");
		return 1;
	}
	/* ������ ���������� �������� ������ ��� ������������ ������, ������� �� ���������� �������.
	� ������ ������ ����� ����� ������ �� ������ ������������. */
	if ((hndls = (FILE **) malloc((argc-1)*sizeof(FILE *)))==NULL)
	{
		pre("Not enough memory");
		return 1;
	}
	/* ���������� ������� ����� � ������� �� ������.
	������������� ���������� stage, � ������� ������� ����� ����� ������,
	������� ��� �������� ������ ����� ����� �������, ���� ���������� ������. */
	for (stage=0; stage<argc-2; ++stage)
	{
		if ((hndls[stage]=fopen(argv[stage+1], "r"))==NULL)
		{
			//char * errdescr;
			//sprintf(errdescr,"Can't open the file \"%s\" for reading",argv[stage+1]);
			pre("Can't open the file for reading");
		}
	}
	// ��������� ������� �������� ���� �� ������.
	if ((hndls[stage]=fopen(argv[stage+1], "w"))==NULL)
	{
		pre("Can't open the file for writing");
		// ���� �� ��������� �� ����� ����� � ��������� ������, ����� ������� ��� �����, ��� �������� �� ������.
		closediap(argc-3);
		return 1;
	}
	// ������ �������� �����������. ��� �������� ����� ���������� ������ dgts.
	// ���������� ������� ����� �� ������� �����, ����� ����������.
	//try {
		for (i=0; i<stage; ++i)
		{
			/* ������� fscanf ���������� ���������� ������� ����������� ������� (� ����� ������ ��������������� ���� Decimal integer),
			������� � ������ ������� ����� �����. ���� ��������� ����� �����, ����� ��������� EOF. �������� ��������� ����� � ������ � ����������� ��. */
			if (hndls[i]==NULL)
			{
				continue;
			}
			while ((test=fscanf(hndls[i],"%d",&j))>0)
			{
				dgts.push_back(j);
			}
			if (test!=EOF)
			{
				pre("Bad file content");
			}
		}
		sort(dgts.begin(), dgts.end());
	//} catch (exception e)
	//{
	//	dgts.clear();
	//	pre("Fatal error");
	//	closediap(stage);
	//	return 1;
	//}
	// ��������� ������� ���������� � ����.
	for(i=0; i<dgts.size(); i++)
	{
	// ��� ������ ������ ������� fprintf ������ ������������� �����, �� ��������� ���, ������� ��������� �� ������ � �������� �������� ������.
		if ((test=fprintf(hndls[stage],"%d\n", dgts[i]))<0)
		{
			pre("Can't write to the file");
			break;
		}
	}
	// ���� ��� ������ �������, ������� ��� �����, ������� ������, ���������� �������������, ������� ���������, �������� ������.
	closediap(stage);
	dgts.clear();
	return 0;
}
