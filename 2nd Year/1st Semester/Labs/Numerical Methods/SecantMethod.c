//SECANT METHODS
#include <stdio.h>
#include <math.h>
#define PI 3.145
#define E 0.00000001
double func(double x)
{
	return exp(x) -2*x -1;
}
double secant_method(double X,double X_Prev)
{
	printf("Iteration Count \t X \t\t FX  \t\t abs error \torder\n");
	
	double X_Next;int i=0;
	double FX_Prev=func(X_Prev);
	double FX=func(X);
	double abse=fabs(X-X_Prev);
	double order=0.0;
	do
	{
		i++;
		FX=func(X);
		FX_Prev=func(X_Prev);
		X_Next=(X_Prev*FX - X*FX_Prev)/(FX-FX_Prev);
		
		double absePrev=abse;
		abse=fabs(X_Next-X);
		if(i==1)
		{
			order=0.0;
		}
		else
		{
			order=log(abse)/log(absePrev);
		}
		printf("%d \t\t\t %lf \t %6lf \t %lf \t%lf\n",i,X,FX,abse,order);
		X_Prev=X;
		X=X_Next;
		/*double cValue=func(X)*func__1(X)/(func_1(X)*func_1(X));
		if(cValue>=1)
		{
			printf("Not Converging");
		}*/
	}while( abse>E );
	return X;
}
int main()
{
	double X=0.0,Y=0.0;
		scanf("%lf %lf",&X,&Y);
	
	double root=secant_method(X,Y);
	printf("Root at %lf by secant method \n",root);
	return 0;
}
