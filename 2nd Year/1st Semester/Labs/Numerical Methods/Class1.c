#include <stdio.h>
#include <math.h>
#define PI 3.141592
#define E 0.000001
float my_sin(float x,int n)
{
	float s=x;int c=0;
	while(c++<n)
	{
		s+= s *  ((float)pow(-1,c))   *   ( (x*x) / ((2.0*c+1)*(2.0*c))  );
	}
	return s;
}
float my_cos(float x,int n)
{
	float s=1.0;int c=0;
	while(c++<n)
	{
		s+= s *  ((float)pow(-1,c))   *   ( (x*x) / ((2.0*c-1)*(2.0*c))  );
	}return s;
}
int main()
{
	float a;int n;
	
		printf("Angle:");
		scanf("%f",&a);
		printf("N:");
		scanf("%d",&n);
	float angle = a * 3.141592 /180.0;
	float SIN=my_sin(angle,n)	;
	float COS=my_cos(angle,n)	;
	printf("Sin is  %f \n",SIN);
	printf("Cos is  %f \n",COS);
	
}

