#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *multiply(double **Matrix,double *eigenVec,int n)
{
	int i,j;
	double *newEigenVec=malloc(sizeof(double)*n);
	for(i=0;i<n;i++)
	{
		double rowSum=0.0;
		for(j=0;j<N;j++)
		{
			rowSum+=Matrix[i][j];
		}
		newEigenVec[i]=eigenVec[i]*rowSum;
	}
	return newEigenVec;
}
void display(double eigenVal,double* eigenVec,int n)
{
	int i;
	printf("Eigen value - %lf\n",eigenVal);
	for(i=0;i<n;i++){
		printf("%.3f \t",eigenVec[i]);
	}
	printf("\n");
	return;
}
int main()
{
	int N;
	printf("Enter N:");
	scanf("%d",&N);
	
	double A[N][N];
	
}
