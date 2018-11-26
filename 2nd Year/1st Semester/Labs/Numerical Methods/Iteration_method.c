#include <stdio.h>
#include <math.h>
#define PI 3.145
#define E 0.0001
double func(double x)
{
	return exp(x)-4*x*x;
}
double g1(double x)
{
	return sqrt(exp(x)/4);
}
double g2(double x)
{
	return -1*sqrt(exp(x)/4);
}
double g_1(double x)
{
	return  sqrt(exp(x))/4;
}
double g_2(double x)
{
	return -1*sqrt(exp(x))/4;
}
void fixed_point_iteration_root1(double X)
{
	double X_Next=g1(X);int i=0;double FX=func(X);double abse=fabs(X_Next-X);double order=0.0;
	while(1)
	{
		
		i++;
		FX=func(X);
		//X1=X- func(X)/func_1(X);
		X_Next=g1(X);
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
		printf("%d \t\t\t %lf \t %6lf \t %lf \t %lf \t%lf\n",i,X,FX,g_1(X),abse,order);
		if(fabs(g_1(X_Next)) >=1)
		{
			printf("Root is diverging\n");
			break;
		}
		if(abse<E)
		{
			printf("Root found at %lf\n",X_Next);
			break;
		}
		X=X_Next;
		//getch();
	}
}
void fixed_point_iteration_root2(double X)
{
	double X_Next=g1(X);int i=0;double FX=func(X);double abse=fabs(X_Next-X);double order=0.0;
	while(1)
	{
		
		i++;
		FX=func(X);
		//X1=X- func(X)/func_1(X);
		X_Next=g2(X);
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
		printf("%d \t\t\t %lf \t %6lf \t %lf \t %lf \t%lf\n",i,X,FX,g_2(X),abse,order);
		if(fabs(g_2(X_Next)) >=1)
		{
			printf("Root is diverging\n");
			break;
		}
		if(abse<E)
		{
			printf("Root found at %lf\n",X_Next);
			break;
		}
		X=X_Next;
		//getch();
	}
}
int main()
{
	double X=0.0;
		scanf("%lf",&X);
	
	printf("Iteration Count \t X \t\t FX  \t\t G'(X) \t\t abs error \torder\n");
	fixed_point_iteration_root1(X);
	fixed_point_iteration_root2(X);
}
