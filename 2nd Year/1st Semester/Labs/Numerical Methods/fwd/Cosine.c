//Progamming to find Cos Series
#include<stdio.h>
#include<stdlib.h>

int main()
{

	int loop,n;
	float val1,sum=0,term;

	printf("The Cos series will be \n");

	for(loop=0;loop<=360;loop=loop+30)
	{

		val1=loop*3.1415/180;//Change into redian
		term=1;
		sum=1;
		n=1;

		while((term>0.00001)||(term<-0.00001))
		{

			term=(-1)*val1*val1*term/((2*n)*(2*n-1));//Relation equation
			n++;
			sum+=term;
			
		}

		printf("\t\tCos(%d)=%f",loop,sum);
		printf("\n");
	}
	return 0;
}
