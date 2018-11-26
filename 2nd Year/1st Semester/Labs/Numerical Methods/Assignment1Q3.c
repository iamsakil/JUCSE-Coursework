
//NEWTON RAPSON METHODS
#include <stdio.h>
#include <math.h>
#define PI 3.145
#define E 0.000001
double func(double x)
{
	return x*x*x + 0.03*x*x + 2.4*pow(10,-6);
}
double func_1(double x)
{
	return 3*x*x + 0.03*2*x ;
}
double func__1(double x)
{
	return 3*2*x + 0.03*2 ;
}
double newton_rapson(double X)
{
	printf("Iteration Count \t X \t\t FX  \t\t abs error \torder\n");
	
	double X1;int i=0;double FX=func(X);double abse=fabs(X1-X);double order=0.0;
	do
	{
		i++;
		FX=func(X);
		X1=X- func(X)/func_1(X);
		
		double absePrev=abse;
		abse=fabs(X1-X);
		if(i==1)
		{
			order=0.0;
		}
		else
		{
			order=log(abse)/log(absePrev);
		}
		printf("%d \t\t\t %lf \t %6lf \t %lf \t%lf\n",i,X,FX,abse,order);
		X=X1;
		double cValue=func(X)*func__1(X)/(func_1(X)*func_1(X));
		if(cValue>=1)
		{
		//	printf("Not Converging\n");
		}
	}while( abse>E );
	return X1;
}
int main()
{
	double X=0.0;
		scanf("%lf",&X);
	
	double root=newton_rapson(X);
	printf("Root at %lf by newton rapson method \n",root);
	return 0;
}
