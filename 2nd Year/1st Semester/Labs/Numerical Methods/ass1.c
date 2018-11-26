#include <stdio.h>
#include <math.h>
#define PI 3.145
#define E 0.0000001
double func(double x)
{
	return ((x* sin(x)) + (cos(x)) );
}
double bisection_method_root(double a,double b)
{
	double fm,fa,fb,m;
	double order=0;
	fa=func(a);
	fb=func(b);
	m=(a+b)/2;
	double prevM;
	int i=0;
	printf("Iteration Count \t a(lb) \t\t b(lb) \t\t m(mid) \t f(m) \t\t abs error \t order\n");
	if(fa==0)
	{
		return a;
	}
	else if(fb==0)
	{
		return b;
	}
	else 
	{
		while(1)
		{
			i++;
			prevM=m;
			double abse=fabs(a-b);
			
			m=(a+b)/2;
			fm=func(m);
			if(i==1)
			{
				order=0.0;
			}
			else
			{
				order=log(m)/log(prevM);
			}
			printf("%d \t\t\t %lf \t %lf \t %lf \t %lf \t %lf \t%lf\n",i,a,b,m,fm,abse,order);
			double gap=a>b?(a-b):(b-a);
			
			if(fm==0 || (  gap<E     ))
			{
				return m;
				break;
			}
			if(fa * fm <0)
				b=m;
			else 
				a=m;
			
		}
	}
	return 0.0;
}
double false_position_method_root(double a,double b)
{
	double fc,fa,fb,c,order;
	order=0.0;
	fa=func(a);
	fb=func(b);
	fc=func(c);
	int k=0;
	double prevC;
	printf("Iteration Count \t a(lb) \t\t b(lb) \t\t c(mid) \t f(c) \t\t abs error \t order\n");
	if(fa==0)
	{
		return a;
	}
	else if(fb==0)
	{
		return b;
	}
	else 
	{
		int i=0;
		while(1)
		{
			k++;
			double abse=fabs(a-b);
			
			prevC=c;
			c=(b*fa - a*fb)/(fa-fb);
			fc=func(c);
			if(k==1)
			{
				order=0.0;
			}
			else
			{
				order=log(c)/log(prevC);
			}
			printf("%d \t\t\t %lf \t %lf \t %lf \t %0.6lf \t %lf \t %lf\n",k,a,b,c,fc,abse,order);
			if(fc==0.0)
				return c;
			if(fa*fc <0)
				b=c;
			else
				a=c;
				
			if(i==1)
			{
				if(fabs(prevC-c) < E )
					return c;
			}
			i=1;
			//order=log(c)/log(prevC);
		}
	}
	return 0.0;
}
int main()
{
	double a,b;
	a=0.0;
	b=PI;
	do
	{
		scanf("%lf %lf",&a,&b);
	}while(func(a)*func(b)>0);
	double root=bisection_method_root(a,b);
	printf("Root at %lf by bisection method \n",root);
	root=false_position_method_root(a,b);
	printf("Root at %lf by false position method\n",root);
	
	return 0;
}

