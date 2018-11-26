#include <stdio.h>
int fact(int n)
{
	if(n==1)
		return 1;
	return n*fact(n-1);
}
int fact_iterative(int n)
{
	int f=1;
	int i;
	for(i=2;i<=n;i++)
	{
		f*=i;
	}
	return f;
}
int main()
{
	int n=5;
	n=fact(n);
	printf("%d",n);
	getch();
}
