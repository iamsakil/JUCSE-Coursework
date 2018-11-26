//Solution for Non-Linear Simulteneous Equations using Jacobi's Method
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float **A,**C,**L,**U,**D,**DI,*x,*xx,*B,*M,*M1,*M2,max,det,**matrix,ratio,a;
double *err;
int n,i,j,k,p,m=0;
float maximum(double err[],int n)
{
	float max=err[0];
	int i;
	for(i=1;i<n;i++)
	{
		if(max<err[i])
			max=err[i];
	}
	return max;
}
void print_mat1(float **a,int n)// matrix printing function
{
	int i;
	for(i=0;i<n;i++)
		{
			printf("\n\t");
			for(j=0;j<n;j++)
				printf("%f ",a[i][j]);
		}
}
void print_mat(float *a,int n)
{
	int i;
	for(i=0;i<n;i++)
		{
			printf("\n\t");
			printf("%f ",a[i]);
		}
}

void input(int n)//initialization of the matrices needed
{
	A=(float **)malloc(n*sizeof(float *));
	for(i=0;i<n;i++)
		A[i]=(float *)malloc((n+1)*sizeof(float));
		
	matrix=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		matrix[i]=(float *)calloc(2*n,sizeof(float));
		
	printf("\n\t Please entry the coefficient matrix: \n\n");
	for(i=0;i<n;i++)
		for(j=0;j<n+1;j++)
			scanf("%f",&A[i][j]);
			
	L=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		L[i]=(float *)calloc(n,sizeof(float));
		
	U=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		U[i]=(float *)calloc(n,sizeof(float));
		
	D=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		D[i]=(float *)calloc(n,sizeof(float));
	
	DI=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		DI[i]=(float *)calloc(n,sizeof(float));
		
	C=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		C[i]=(float *)calloc(n,sizeof(float));
		
	x=(float *)calloc(n,sizeof(float));
	xx=(float *)calloc(n,sizeof(float));
	B=(float *)calloc(n,sizeof(float));
	err=(double *)calloc(n,sizeof(float));
	M=(float *)calloc(n,sizeof(float));
	M1=(float *)calloc(n,sizeof(float));
	M2=(float *)calloc(n,sizeof(float));
}
int main()
{
	printf("\n\tPlease enter the size of the matrix: ");
	scanf("%d",&n);
	
	input(n);
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i>j)
				L[i][j]=A[i][j];
			else if(i==j)
				D[i][j]=A[i][j];
			else
				U[i][j]=A[i][j];
		}
	for(i=0;i<n;i++)
		B[i]=A[i][n];
		
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)//taking inverse of the diagonal matrix
			if(i==j)
				DI[i][j]=1/D[i][j];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			C[i][j]=L[i][j]+U[i][j];			
	
	//printing all the needed matrices	
	printf("\nU matrix:");
	print_mat1(U,n);
	printf("\n\n");
		
	printf("\nC matrix:");
	print_mat1(C,n);
	printf("\n\n");
		
	printf("\nD matrix:");
	print_mat1(D,n);
	printf("\n\n");
		
	printf("\nDI matrix:");
	print_mat1(DI,n);
	printf("\n\n");
		
	printf("\nB matrix:");
	print_mat(B,n);

    	do
    	{
    		printf("\n\n");
    		printf("Iteration No: %d",m);//the iteration equation
    		for(i=0;i<n;i++)
    			x[i]=xx[i];
    		for(i=0;i<n;i++)
    			M2[i]=M1[i]=M[i]=0.0;
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M2[i]+=DI[i][j]*B[j];
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M[i]+=U[i][j]*x[j];
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M1[i]+=DI[i][j]*M[j];
    		
    		for(i=0;i<n;i++)
    			xx[i]=M2[i]-M1[i];
    		
    		printf("\n\n");	
    	
    		printf("\nX NEW matrix:");
		print_mat(xx,n);
		for(i=0;i<n;i++)
    			err[i]=fabs(xx[i]-x[i]);
    		
    		max=maximum(err,n);//error calculation
    		printf("\n\n");
    		
    		printf("\t Error is %lf",max);
    		m++;
    	}while(max>0.0000005);
    	
    		for(i=0;i<n;i++)
    			x[i]=xx[i];
    		for(i=0;i<n;i++)
    			M2[i]=M1[i]=M[i]=0.0;
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M2[i]+=DI[i][j]*B[j];
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M[i]+=U[i][j]*x[j];
    		for(i=0;i<n;i++)
    			for(j=0;j<n;j++)
    				M1[i]+=DI[i][j]*M[j];
    		
    		for(i=0;i<n;i++)
    			xx[i]=M2[i]-M1[i];
    	
    	printf("\n\n\t The answer vector is: ");
    	print_mat(xx,n);
	
	return 0;
}
