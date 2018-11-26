
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PRE 0.001
double max(double* array,int n){
	int i;
	double max=0;
	for(i=0;i<n;i++){
		if(fabs(array[i])>fabs(max)){
			max=array[i];
		}
	}
	for(i=0;i<n;i++){
		array[i]/=max;
	}
	return max;
}
double* multiply(double** matrix,double* eigenVec,int n){
	int i,j;
	double sum;
	double* newVec=(double*)malloc(sizeof(double)*n);
	for(i=0;i<n;i++){
		sum=0;
		for(j=0;j<n;j++){
			sum+=(matrix[i][j]*eigenVec[j]);
		}
		newVec[i]=sum;
	}
	return newVec;
}
void display(double eigenVal,double* eigenVec,int n){
	int i;
	printf("Eigen Value: %lf\n",eigenVal);
	for(i=0;i<n;i++){
		printf("%lf\t",eigenVec[i]);
	}
	printf("\n\n");
	return;
}
int main(void){
	int n,i,j,ch;
	double **matrix,*eigenVec,eigenVal,prevEigenVal;
	printf("enter the value of n:\t");
	scanf("%d",&n);
	matrix=(double**)malloc(sizeof(double*)*n);
	eigenVec=(double*)malloc(sizeof(double)*n);
	printf("enter the matrix\n");
	for(i=0;i<n;i++){
		matrix[i]=(double*)malloc(sizeof(double)*n);
		for(j=0;j<n;j++){
			scanf("%lf",&matrix[i][j]);
		}
	}
	printf("1. enter the initial approx, 2. use all 1s\n");
	scanf("%d",&ch);
	if(ch==1){
		printf("enter the values\n");
		for(i=0;i<n;i++){
			scanf("%d",&eigenVec[i]);
		}
	}
	else{
		for(i=0;i<n;i++){
			eigenVec[i]=1;
		}
	}
	prevEigenVal=5.0;eigenVal=0;
	while(fabs(prevEigenVal-eigenVal)>PRE){
		prevEigenVal=eigenVal;
		eigenVec=multiply(matrix,eigenVec,n);
		eigenVal=max(eigenVec,n);
		display(eigenVal,eigenVec,n);
	}
	printf("Eigen Value : %lf\n",eigenVal);
	printf("Eigen Vector: \n");
	for(i=0;i<n;i++){
		printf("%lf\n",eigenVec[i]);
	}
}
