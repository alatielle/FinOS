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
	float f;
	int test;
	/* Начнем с того, что проверим, достаточно ли у нас аргументов для работы.
	Нам нужны файл для записи отсортированных чисел и как минимум один файл для чтения.
	Значит, аргументов должно быть 3 и больше (первым аргументом является имя программы). */
	if (argc<3)
	{
		// В случае неудачи выведем сообщение об ошибке с помощью процедуры pre() и аварийно завершим работу.
		pre("Too few arguments");
		return 1;
	}
	/* Теперь попытаемся выделить память для дескрипторов файлов, которые мы собираемся открыть.
	В случае успеха будем иметь ссылку на массив дескрипторов. */
	if ((hndls = (FILE **) malloc((argc-1)*sizeof(FILE *)))==NULL)
	{
		pre("Not enough memory");
		return 1;
	}
	/* Попытаемся открыть файлы с числами на чтение.
	Воспользуемся переменной stage, с помощью которой будет легко узнать,
	сколько уже открытых файлов нужно будет закрыть, если произойдет ошибка. */
	for (stage=0; stage<argc-2; ++stage)
	{
		if ((hndls[stage]=fopen(argv[stage+1], "r"))==NULL)
		{
			pre("Can't open the file \""+argv[stage+1]+"\" for reading");
		}
	}
	// Попробуем открыть последий файл на запись.
	if ((hndls[stage]=fopen(argv[stage+1], "w"))==NULL)
	{
		pre("Can't open the file for writing");
		// Если мы добрались до этого места и произошла ошибка, нужно закрыть все файлы, уже открытые на чтение.
		closediap(argc-3);
		return 1;
	}
	// Теперь займемся сортировкой. Для хранения чисел используем вектор dgts.
	// Попытаемся извлечь числа из каждого файла, кроме последнего.
	for (i=0; i<stage; ++i)
	{
		/* Функция fscanf возвращает количество успешно прочитанных записей (в нашем случае соответствующих типу Decimal integer),
		которое в случае неудачи будет нулем. Если достигнут конец файла, будет возвращен EOF. Поместим считанные числа в вектор и отсортируем их. */
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
	// Попробуем вывести результаты в файл.
	for(i=0; i<dgts.size(); i++)
	{
	// При ошибке записи функция fprintf вернет отрицательное число, мы обнаружим это, выведем сообщение об ошибке и аварийно завершим работу.
		if ((test=fprintf(hndls[stage],"%d\n", dgts[i]))<0)
		{
			pre("Can't write to the file");
			break;
		}
	}
	// Если все прошло успешно, закроем все файлы, очистим память, занимаемую дескрипторами, очистим контейнер, завершим работу.
	closediap(stage);
	dgts.clear();
	return 0;
}