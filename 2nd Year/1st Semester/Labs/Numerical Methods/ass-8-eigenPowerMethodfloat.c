/*Write a C program to develop the Power method for finding the largest eigenvalue and corresponding eigen vector. 
3
10 5 6
5 20 4
6 4 30
2
4
2 -1 0 0
-1 4 -1 0
0 -1 4 -1
0 0 -1 2
2
1 0 0 0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PRE 0.001
float max(float* array,int n){
	int i;
	float max=0;
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
float* multiply(float** matrix,float* eigenVec,int n){
	int i,j;
	float sum;
	float* newVec=(float*)malloc(sizeof(float)*n);
	for(i=0;i<n;i++){
		sum=0;
		for(j=0;j<n;j++){
			sum+=(matrix[i][j]*eigenVec[j]);
		}
		newVec[i]=sum;
	}
	return newVec;
}
void display(float eigenVal,float* eigenVec,int n){
	int i;
	printf("eigen value - %f\n",eigenVal);
	for(i=0;i<n;i++){
		printf("%f\t",eigenVec[i]);
	}
	printf("\n");
	return;
}
int main(void){
	int n,i,j,ch;
	float **matrix,*eigenVec,eigenVal,prevEigenVal;
	printf("enter the value of n:\t");
	scanf("%d",&n);
	matrix=(float**)malloc(sizeof(float*)*n);
	eigenVec=(float*)malloc(sizeof(float)*n);
	printf("enter the matrix\n");
	for(i=0;i<n;i++){
		matrix[i]=(float*)malloc(sizeof(float)*n);
		for(j=0;j<n;j++){
			scanf("%f",&matrix[i][j]);
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
	printf("eigen value - %f\n",eigenVal);
	printf("Vector - \n");
	for(i=0;i<n;i++){
		printf("%f\n",eigenVec[i]);
	}
	
	float *finalEigenVec=(float*)malloc(sizeof(float)*n);
	finalEigenVec=multiply(matrix,eigenVec,n);
	
	for(i=0;i<n;i++){
		printf("%f\t",finalEigenVec[i]);
		eigenVec[i]*=eigenVal;
	}
	printf("\n");
	
	for(i=0;i<n;i++){
		printf("%f\t",eigenVec[i]);
	}
	printf("\n");
}
