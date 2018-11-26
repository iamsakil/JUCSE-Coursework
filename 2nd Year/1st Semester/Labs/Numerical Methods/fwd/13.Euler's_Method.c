//Differential Equation Using Euler's Method
#include<stdio.h>
#include<math.h>

#define f(x,y) (2*x*x+2*y)
#define origi_y(x) (1.5*exp(2*x)-x*x-x-0.5)

int main()
{
	int flag;
	float x=0,y=1,x0,y0,y1_0,y1_1;
	float h=0.1;
	
	printf("\n\t\tx \t y_computed\t\t y \t\t Absolute error\n");
	
	while(x<1)
	{
		x0=x;
		y0=y;
		x=x+h;
		y1_0=y0+h*f(x0,y0);
		flag=0;
		do
		{
			if(flag!=0)
				y1_0=y1_1;
			y1_1=y0+h*(f(x0,y0)+f(x,y1_0))/2;                     
			flag=1;
		}while(fabs(y1_1-y1_0)<0.00005);
		
		printf("\n\t %f \t %f \t %f \t %f",x,y1_1,origi_y(x),fabs(origi_y(x)-y1_1));
		
		y=y1_1;
	}
	return 0;
}
	
	
