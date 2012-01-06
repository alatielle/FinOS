extern void clrscr()
{
	int i;
	for (i=0xb8000; i<0xb8fa0; i+=2)
		*(short int *) i = 0x0;
	return;
}

extern void printint(int curpos,short int symb)
{
	*(short int *) curpos = 0x700 + symb;
	curpos+=2;
	return;
}

extern void printhex(int curpos,int val)
{
	int t;
	t=val;
	int	d;
	d=28;
	char c;
	while (d>=0)
	{
		c=(t>>d)&0xf;
		if (c<10)
			c+='0';
		else
			c+='A'-10;
		*(short int *) curpos = 0x700 + c;
		d-=4;
		curpos+=2;
	}
	return;
}

extern void printstring(int curpos,int strstart)
{
	int	i=strstart;
	while (*(char *) i != 0 && curpos<0xb8fa0)
	{
		*(short int *) curpos = 0x700 + *(char *) i;
		++i;
		curpos+=2;
	}
	return;
}
