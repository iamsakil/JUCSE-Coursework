// Iterpolation Using Lagrange
#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,i,j;
	float *x,*y;
	float x1,y1,S;
	printf("Enter the no. of data entry: ");
	scanf("%d",&n);
	x=(float *)malloc(n*sizeof(float));
	y=(float *)malloc(n*sizeof(float)); 
	printf("Enter the values of x's and y's one by one:\n");

	for (i=0;i<n;i++)
		scanf("%f %f",&x[i],&y[i]);
	
	printf("Enter the value of x:");
	scanf("%f",&x1);

	y1=0;

	for (i=0;i<n;i++)
	{
		S=1;
		for (j=0;j<n;j++)
		{
			if (i!=j)
				S*=(x1-x[j])/(x[i]-x[j]);
		}
		y1+=y[i]*S;
	}

	printf("The value of y is %f .",y1);

        return 0;
}
