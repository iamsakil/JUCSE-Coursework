#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int i,j,k=0,l,n,temp=0;
	float **A,*x,var,m,max,temp2;
	
	printf("\n\t Please input the order of the matrix: ");
	scanf("%d",&n);
	
	A=(float **)malloc(n*sizeof(float *));
	for(i=0;i<=n;i++)
		A[i]=(float *)malloc(2*n*sizeof(float));
		
	x=(float *)malloc(n*sizeof(float));
		
	printf("\n\t Please input the matrix elements: \n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%f",&A[i][j]);
	
	for(i=0;i<n;i++)
		for(j=n;j<2*n;j++)
		{
			if(i==j%n)
				A[i][j]=1.0;
			else
				A[i][j]=0.0;
		}
		
	printf("\n\t So the argumented matrix will be: \n");
	for(i=0;i<n;i++)
		{
			for(j=0;j<2*n;j++)
				printf("%f ",A[i][j]);
			printf("\n");
		}
	n=n-1;				
	while(k<=n)
	{
		l=k;
		max=A[k][k];
		temp=0;
		while(k+1<=n)
		{
			if(max<fabs(A[k+1][k]))
			{
				max=A[k+1][k];
				temp=k+1;
			}
			k++;
		}
		k=l;
		
		if(temp!=0)
		{
			for(i=0;i<=2*n+1;i++)
			{
				var=A[temp][i];
				A[temp][i]=A[k][i];
				A[k][i]=var;
			}
			printf("\n\t So the argumented matrix will become: \n");
			for(i=0;i<=n;i++)
			{
				printf("\t");
				for(j=0;j<=2*n+1;j++)
					printf("%f ",A[i][j]);
				printf("\n");
			}
			printf("\n\n");	
		}
		
	temp=A[k][k];
	
	for(j=0;j<=2*n+1;j++)
		A[k][j]/=temp;
		
		i=0;
		while(i<=n)
		{
			if(i!=k)
			{
				m=A[i][k]/A[k][k];
				j=0;
				while(j<=2*n+1)
				{
					A[i][j]=A[i][j]-m*A[k][j];
					j++;
				}
			}
			i++;
		}
		printf("\n\t So the argumented matrix will become: \n");
		for(i=0;i<=n;i++)
		{
			printf("\t");
			for(j=0;j<=2*n+1;j++)
				printf("%f ",A[i][j]);
			printf("\n");
		}
		printf("\n\n");
		k++;
	}
	return 0;
}
