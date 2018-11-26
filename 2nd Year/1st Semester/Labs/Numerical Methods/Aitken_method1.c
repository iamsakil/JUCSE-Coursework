//SECANT METHODS
#include <stdio.h>
#include <math.h>
#define PI 3.145
#define E 0.0001
double f(double x)
{
	return -2*x +cos(x) +3;
}
double g (double x)
{
	return (.5)*(cos(x)+ 3);
}
double aitken_method(double X_Prev)
{
	printf("Iteration Count \t X \t\t FX  \t\t abs error \torder\n");
	int i=0;
	double X;
	double X_Next;
	
	double abse=fabs(X-X_Prev);
	double order=0.0;
	do
	{
		i++;
		X=g(X_Prev);
		X_Next=g(X);
		
		double temp=X_Next - (pow(X_Next-X,2))/ (X_Next + X_Prev - 2*X);
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
		printf("%d \t\t\t %lf \t %6lf \t %lf \t%lf\n",i,X,f(X),abse,order);
		X_Prev=X;
		X=X_Next;
		X_Next=temp;
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
	double X=0.0;
		scanf("%lf",&X);
	
	double root=aitken_method(X);
	printf("Root at %lf by aitken method \n",root);
	return 0;
}
