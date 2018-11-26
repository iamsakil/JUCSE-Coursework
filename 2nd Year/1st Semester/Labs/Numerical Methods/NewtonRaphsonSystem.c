/*Solution for System of Non-Linear Equations Using Newton-Raphson Method*/
/* The code is for
	f1=x*x+y*y-50;
	f2=x*y-25;
	these two equations*/

#include<stdio.h>
#include<math.h>

float df1x(float x1,float y1)
{
	return (2*x1);
}

float df2x(float x1,float y1)
{
	return (y1);
}

float df1y(float x1,float y1)
{
	return (2*y1);
}

float df2y(float x1,float y1)
{
	return (x1);
}

float det(float x,float y)
{
	float D=df1x(x,y)*df2y(x,y)-df1y(x,y)*df2x(x,y);
	return D;
}

float newx(float x,float y)
{
	float x1,f1,f2;
	f1=x*x+y*y-50;
	f2=x*y-25;
	x1=f2*df1y(x,y)-f1*df2y(x,y);
	float d=det(x,y);
	if(d==0)printf("Jacobin has become zero");
	return (x1/d);
}

float newy(float x,float y)
{
	float y1,f1,f2;
	f1=x*x+y*y-50;
	f2=x*y-25;
	y1=f1*df2x(x,y)-f2*df1x(x,y);
	float d=det(x,y);
	if(d==0)printf("Jacobin has become zero");
	return (y1/d);
}

int main()
{
	int i=0;
	float x1,x2,y1,y2;

	printf("Enter the approximations of x & y respectively: \n");
	scanf("%f %f", &x2, &y2);

	printf("\n\n\t  Iteration no \t  Prev x Val \t  New x Val \t  |X-X0| \t  Prev y Val \t New y Val  \t |Y-Y0| \n");

	do
	{
		++i;
		x1=x2;
		y1=y2;

		x2=x1+newx(x1,y1);
		y2=y1+newy(x1,y1);

		printf("\n\t\t %d \t %f \t %f \t %f \t %f \t %f \t %f",i,x1,x2,fabs(x1-x2),y1,y2,fabs(y1-y2));

	}while(fabs(x1-x2)>0.000001||fabs(y1-y2)>0.000001);

	printf("\n\n\t So the answer will be: %f & %f",x2,y2);

	return 0;
}

