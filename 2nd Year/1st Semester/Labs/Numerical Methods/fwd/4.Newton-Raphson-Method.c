/*Newton Raphson Method to find the root of a non-linear equation*/
#include<stdio.h>
#include<math.h>

/*Given Non linear equation*/
#define f(x) pow(x,3)-18
#define fn(x) 3*pow(x,2)
#define fnn(x) 6*pow(x,1)

int main()
{
	int i=0;
	float x,newx;
	
	/*Initial Approximation*/
	
	printf("\n\t Please input the initial approximation: ");
	scanf("%f",&newx);
	
	printf("\t  Iteration no \t  Prev Val \t  New Val \tConvergence Val    |Error|\n");
	
	/*Iteration Part*/
	
	do
	{
		++i;
		x=newx;
		newx=x-((f(x))/(fn(x)));
		printf("\n\t\t %d \t %f \t %f \t %f \t %f",i,x,newx,fabs((f(newx))*(fnn(newx))/pow((fn(x)),2)),fabs(x-newx));
		
	}while(fabs(x-newx)>0.000005);
	
	
	printf("\n\n\t The answer is: %f\n",newx);
	
	return 0;
}	
