/*Secant Method to find the root of a non-linear equation*/
#include<stdio.h>
#include<math.h>
#define e 2.7182818

/*Given Non linear equation*/
#define f(x) 3*x+sin(x)-pow(e,x)

int main()
{
	int i=0;
	float x0,x1,x2,err1,err2;
	
	/*Initial Approximation*/
	
	printf("\n\t Please input the initial approximations: ");
	scanf("%f %f",&x0,&x1);
	
	printf("\t  Iteration no \t  Prev Val \t  New Val \t  Next Val \t  |Error| \t Order of convergance \n");
	
	/*Iteration Part*/
	
	do
	{
		++i;
		x2= (x0*(f(x1))-x1*(f(x0)))/((f(x1))-(f(x0)));
		err1=log(fabs(x2-x1));
		err2=log(fabs(x1-x0));
		printf("\n\t\t %d \t %f \t %f \t %f \t %f  \t %f",i,x0,x1,x2,fabs(x2-x1),err1/err2);
		x0=x1;
		x1=x2;
	}while(fabs(x1-x0)>0.00005);
	
	printf("\n\n\t The answer is: %f\n",x2);
	
	return 0;
}		
