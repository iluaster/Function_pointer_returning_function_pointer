#include<stdio.h>

typedef int (*f1)(int,int);
typedef f1 (*f2)(char,int,int);

int add(int i,int j)
{
	return i+j;
}

int sub(int i,int j)
{
	return i-j;
}

f1 arithmetic(char a,int b,int c)
{
	int (*fptr)(int,int);

	if(a=='+')
	{
		printf("%d+%d=",b,c);
		fptr=add;
	}
	if(a=='-')
	{
		printf("%d-%d=",b,c);
		fptr=sub;
	}
	return fptr;
}


int main(int argc, char *argv[])
{
//	int (*(ffptr)(int,int))(char,int,int);
	int result;
	char operator;
	f1 fptr;
	f2 ffptr;
	ffptr=arithmetic;

	operator='+';
	fptr=ffptr(operator,5,2);
	result=fptr(5,2);
	printf("%d\n",result);

	operator='-';
	fptr=ffptr(operator,5,2);
	result=fptr(5,2);
	printf("%d\n",result);
	return 0;
}
