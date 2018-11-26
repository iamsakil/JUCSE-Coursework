#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long random(long ,long);
int prime_check(int a)//checks if a is prime
{
	int i;
	for(i=2;i<a;i++)
		if(a%i==0)
			return 0;
	return 1;
}
int main()
{
	srand(time(NULL));
	long P=1000;
	while(prime_check(P)==0)
	{
		P++;
	}
	long L[100];
	long R[100];
	int i;
	for(i=0;i<100;i++)
	{
		L[i]=random(10000,100000);//generating a large number
		R[i]=L[i]%P;
		printf("%d \t %ld \t\t %ld \n",i+1,L[i],R[i]);
	}
	return 0;
	
}
long random(long a,long b)
{
	
	return a+ rand()%(b-a);
}
