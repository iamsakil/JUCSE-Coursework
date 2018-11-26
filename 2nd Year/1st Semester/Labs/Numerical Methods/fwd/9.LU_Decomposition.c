//Solution for Linear Simulteneous equations using LU Decomposition
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	float **A,**L,**U,*B,*Y,*X,sum=0;
	int n,i,j,k,p;
	printf("\n\tPlease enter the size of the matrix: ");
	scanf("%d",&n);
	A=(float **)malloc(n*sizeof(float *));
	for(i=0;i<n;i++)
		A[i]=(float *)malloc(n*sizeof(float));
		
	printf("\n\t Please entry the coefficient matrix: \n\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%f",&A[i][j]);
			
	L=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		L[i]=(float *)calloc(n,sizeof(float));
		
	U=(float **)calloc(n,sizeof(float *));
	for(i=0;i<n;i++)
		U[i]=(float *)calloc(n,sizeof(float));
	B=(float *)calloc(n,sizeof(float));
	Y=(float *)calloc(n,sizeof(float));
	X=(float *)calloc(n,sizeof(float));
		
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
		{
		    if(i>=j)
		    {
		        L[i][j]=A[i][j];
		        for(k=0;k<=j-1;k++)
		            L[i][j]-=L[i][k]*U[k][j];
		        if(i==j)
		            U[i][j]=1;
		    }
		    else
		    {
		       
		        U[i][j]=A[i][j];
		        for(k=0;k<=i-1;k++)
		            U[i][j]-=L[i][k]*U[k][j];
		        U[i][j]/=L[i][i]; 
		    }
		}
	 }
	printf("\nL matrix:");
	for(i=0;i<n;i++)
		{
			printf("\n\t");
			for(j=0;j<n;j++)
				printf("%f ",L[i][j]);
		}
		
		printf("\n\n");
		
	printf("\nU matrix:");
	for(i=0;i<n;i++)
		{
			printf("\n\t");
			for(j=0;j<n;j++)
				printf("%f ",U[i][j]);
		}
		
	printf("\n\n\tPlease entry the constant terms\n");
	for(i=0;i<n;i++)
		scanf("%f",&B[i]);
		
	for(i=0;i<n;i++)
    	{
        	Y[i]=B[i];
        	for(j=0;j<i;j++)//Forword substitution
        	{
            		Y[i]-=L[i][j]*Y[j];
        	}
        	Y[i]/=L[i][i];
    	}
    	printf("\n[Y]:");
    	
    	for(i=0;i<n;i++)
    		printf("\t%f ",Y[i]);
    	
    	for(i=n-1;i>=0;i--)//Back Substitution
    	{
        	X[i]=Y[i];
        	for(j=i+1;j<n;j++)
        		X[i]-=U[i][j]*X[j];
        }
    	printf("\n\t So the result will be: \n");
    	
    	for(i=0;i<n;i++)
    		printf("\t%0.5f ",X[i]);
    		
    	printf("\n\n");
    			
	return 0;
}
