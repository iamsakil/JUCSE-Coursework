#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand(time(NULL));//seeding the srand func with current time to generate totally random numbers
	int random[30001];
	int i=0;
	for(i=1;i<=30000;i++)//fill up an array each with own index value
	{
		random[i]=i;
	}
	for(i=1;i<=30000;i++)//linearly iterate and randomly swap value, thus random numbers are generated without repitition
	{
		int ra=rand()%30001;
		if(ra==0)
		{
			i--;continue;
		}
		int t=random[i];
		random[i]=random[ra];
		random[ra]=t;
	}
	int n=30000;
	while(n-->0)
	{
		printf("%d\n",random[n]);
	}
	return 0;
}
