//Programme to find the Sine Series
#include<stdio.h>
#include<stdlib.h>

int main()
{

	int loop,n;
	float val1,sum=0,term;

	printf("The sine series will be \n");

	for(loop=0;loop<=360;loop=loop+30)
	{

		val1=loop*3.1415/180;//Changing into redian
		term=val1;
		sum=val1;
		n=1;

		while((term>0.00001)||(term<-0.00001))
		{

			term=(-1)*val1*val1*term/((2*n)*(2*n+1));//Relation Equation
			n++;
			sum+=term;
		
		}

		printf("\t\tSine(%d)=%f",loop,sum);
		printf("\n");
	}
	return 0;
}

