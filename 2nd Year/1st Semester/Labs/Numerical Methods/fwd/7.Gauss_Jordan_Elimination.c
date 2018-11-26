#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int n,i,j,k=0,l,temp=0;
	float **A,*x,max,var,m;
	
	printf("\n\t Please input the order of the simulteneous equations: ");
	scanf("%d",&n);
	
	A=(float **)malloc(n*sizeof(float*));
	for(i=0;i<n;i++)
		A[i]=(float *)malloc((n+1)*sizeof(float));
		
	x=(float *)malloc(n*sizeof(float));
		
	printf("\n\t Please enter the argumented matrix: ");
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
				var=A[temp][i];
				A[temp][i]=A[k][i];
				A[k][i]=var;
			}
			printf("\n\t So the argumented matrix will become: \n");
			for(i=0;i<=n;i++)
			{
				printf("\t");
				for(j=0;j<=n+1;j++)
					printf("%f ",A[i][j]);
				printf("\n");
			}
			printf("\n\n");
		}
		
		i=0;
		while(i<=n)
		{
			if(i!=k)
			{
				m=A[i][k]/A[k][k];
				j=0;
				while(j<=n+1)
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
			for(j=0;j<=n+1;j++)
				printf("%f ",A[i][j]);
			printf("\n");
		}
		printf("\n\n");
		k++;
	}
	k=0;
	while(k<=n)
	{
		x[k]=A[k][n+1]/A[k][k];
		k++;
	}
	printf("\n\t So the solution of the simulteneous equations will be: \n");
	for(i=0;i<=n;i++)
		printf("\t %f\n",x[i]);
		
	return 0;
}		
