#include<stdio.h>
#include<stdlib.h>

int main()
{
	float **A,*x,max,var,m,s;
	int n,i,j,l,k=0,temp=0;
	
	printf("\n\t Please enter the degree of the equation: ");
	scanf("%d",&n);
	
	A=(float **)malloc(n*sizeof(float*));
	for(i=0;i<n;i++)
		A[i]=(float*)malloc((n+1)*sizeof(float));
		
	x=(float *)malloc(n*sizeof(float));
		
	printf("\n\t Please enter the coefficient matrix: ");
	
	for(i=0;i<n;i++)
		for(j=0;j<=n;j++)
			scanf("%f",&A[i][j]);
	
	n=n-1;
	
	while(k<=n)
	{
		l=k;
		max=A[k][k];
		while(k+1<=n)
		{
			if(max<A[k+1][k])
			{
				max=A[k+1][k];
				temp=k+1;
			}
			k++;
		}
		k=l;
		if(temp!=0)
		{
			for(i=0;i<=n+1;i++)
			{
				var=A[k][i];
				A[k][i]=A[temp][i];
				A[temp][i]=var;
			}
			printf("\n\t So the argumented matrix will be: \n");
			for(i=0;i<=n;i++)
			{
				printf("\t");
				for(j=0;j<=n+1;j++)
					printf("%f ",A[i][j]);
				printf("\n");
			}
			printf("\n\n");
		}
		i=k+1;
		while(i<=n)
		{
			m=A[i][k]/A[k][k];
			j=k;
			while(j<=n+1)
			{
				A[i][j]=A[i][j]-m*A[k][j];
				j++;
			}
			i++;
		}
		k++;
		
		printf("\n\t So the argumented matrix will be: \n");
		for(i=0;i<=n;i++)
		{
			printf("\t");
			for(j=0;j<=n+1;j++)
				printf("%f ",A[i][j]);
			printf("\n");
		}
		printf("\n\n");
	}
	
	printf("\n\t So the argumented matrix will be: \n");
	for(i=0;i<=n;i++)
	{
		printf("\t");
		for(j=0;j<=n+1;j++)
			printf("%f ",A[i][j]);
		printf("\n");
	}
	printf("\n\n");
	x[n]=A[n][n+1]/A[n][n];
	i=n-1;
	while(i>=0)
	{
		j=i+1;
		s=A[i][n+1];
		while(j<=n)
		{
			s=s-A[i][j]*x[j];
			j++;
		}
		s/=A[i][i];
		x[i]=s;
		i--;
	}
	printf("\n\n\t So the output of the solution of the given simulteneous will be: \n");
	for(i=0;i<=n;i++)
		printf("\t X%d->%f\n",i+1,x[i]);
	return 0;
}
