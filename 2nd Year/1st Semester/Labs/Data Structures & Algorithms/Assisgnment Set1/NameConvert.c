#include <stdio.h>
#include <stdlib.h>
int main()
{
	char name[100];
	scanf ("%100[^\n]%*c", name);
	int i;
	long long sum=0;
	for(i=0;name[i]!='\0';i++)
	{
		int n=(int)name[i];
		if(n<100)
		{
			sum=sum*100 + n;
		}
		else
		{
			sum=sum*1000 + n;
		}
	}
	printf("%lld",sum);
}
