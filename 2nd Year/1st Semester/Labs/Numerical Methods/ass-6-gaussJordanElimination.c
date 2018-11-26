/*
. Develop a C program to find the inverse of a non-singular matrix by Gauss-Jordan elimination method. Arrange for 
verification of the product of the matrix and its inverse. Test your program on the following:
?(1&5&3@1&3&2@2&4&-6)
*/
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
void display(float** matrix,int range){
	int i,j;
	for(i=0;i<(range);i++){
		for(j=0;j<(range);j++){
			printf("%6.3f\t",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
float** interchangeRow(float** matrix,int range,int n,int m){
	int i;
	float temp;
	if(n==m) return matrix;
	for(i=0;i<range;i++){
		temp=matrix[n][i];
		matrix[n][i]=matrix[m][i];
		matrix[m][i]=temp;
	}
	return matrix;
}
void maxRowPivot(float** matrix,float** inverse,int range,int n){
	int i,pos=n;
	float max=fabs(matrix[n][n]);
	for(i=n;i<(range);i++){
		if(max<fabs(matrix[i][n])){
			max=matrix[i][n];
			pos=i;
		}
	}
	matrix=interchangeRow(matrix,range,n,pos);
	inverse=interchangeRow(inverse,range,n,pos);
	return ;
}
float** allocate(float** matrix,int range){//allocates matrix of n*n size
	int i;
	matrix=(float **)malloc(range*sizeof(float *));
	for(i=0;i<range;i++){
		matrix[i]=(float *)malloc(range*sizeof(float));
	}
	return matrix;
}
float** matrixMult(float** a,float** b,float** newm,int range){
	int i,j,k;
	for(i=0;i<range;i++){
		for(j=0;j<range;j++){
			newm[i][j]=0;
			for(k=0;k<range;k++){
				newm[i][j]+=(a[i][k]*b[k][j]);
			}
		}
	}
	return newm;
}
int main(){
	float **matrix,**inverse,**original,**newm,temp;
	int i,j,k,range;

	printf("Enter the size of the matrix(i.e. value of 'n' as size isnXn):\t");
	scanf("%d",&range);

	matrix=(float **)allocate(matrix,range);
	inverse=(float **)allocate(inverse,range);
	original=(float **)allocate(original,range);
	newm=(float **)allocate(newm,range);
	printf("Enter the matrix:\n");
	for(i=0;i<range;i++){
		printf("Row number %d\n",(i+1));
		for(j=0;j<range;j++){
			scanf("%f",&matrix[i][j]);
			original[i][j]=matrix[i][j];
		}
	}
	for(i=0;i<range;i++){
		for(j=0;j<range;j++){
			if(i==j) inverse[i][j]=1;
			else inverse[i][j]=0;
		}
	}
	for(k=0;k<range;k++){
		maxRowPivot(matrix,inverse,range,k);
		temp=matrix[k][k];
		for(j=0;j<range;j++){
			matrix[k][j]/=temp;
			inverse[k][j]/=temp;
		}
		for(i=0;i<range;i++){
			temp=matrix[i][k];
			for(j=0;j<range;j++){
				if(i==k) break;
				matrix[i][j]-=matrix[k][j]*temp;
				inverse[i][j]-=inverse[k][j]*temp;
			}
		}
		display(inverse,range);
	}
	printf("The inverse of the matrix is:\n");
	display(inverse,range);
	newm=matrixMult(original,inverse,newm,range);
	display(newm,range);
	return 0;
}

