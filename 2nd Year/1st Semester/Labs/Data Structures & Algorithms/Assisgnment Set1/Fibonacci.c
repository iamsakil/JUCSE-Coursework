#include <stdio.h>
double fibo(double n)
{
	if(n==1)
		return 0;
	else if(n==2)
		return 1;
	else 
		return fibo(n-1)+fibo(n-2);//the recursive call statement
}
double fibo_iterative(double n)
{
	if(n==1)
		return 0;
	else if(n==2)
		return 1;
	double a=0;
	double b=1;
	n-=2;
	while(n-->0)//iterative way to find the nth fibo no
	{
		double c=a+b;
		a=b;
		b=c;
	}
	return b;
}
int main()
{
	double n=31;
	n=fibo(n);
	printf("%lf",n);
}
