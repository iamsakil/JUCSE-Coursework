/*
1. Develop a C program to implement Gaussian Elimination method. Test your program on the following system of linear 
equations:
x_1+x_2-x_3+ x_4=2
?2x?_1+x_2+x_3- 3x_4=1
3x_1-x_2-x_3+ x_4=2
?5x?_1+x_2+3x_3- 2x_4=7
After elimination of each variable, display the augmented coefficient matrix. Incorporate pivoting technique in the 
program.
1 5 3 10
1 3 2 5
2 4 -6 -4
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
float** maxRowPivot(float** matrix,int range,int n){
	int i,pos=n;
	float max=fabs(matrix[n][n]);
	for(i=n;i<(range-1);i++){
		if(max<fabs(matrix[i][n])){
			max=matrix[i][n];
			pos=i;
		}
	}
	matrix=interchangeRow(matrix,range,n,pos);
	return matrix;
}
void display(float** matrix,int range){
	int i,j;
	for(i=0;i<(range-1);i++){
		for(j=0;j<(range);j++){
			printf("%6.3f\t",matrix[i][j]);
		}
		printf("\n");
	}
	return;
}
float** subtractRows(float** matrix,int range,int n){//reducing the rows
	int i,j;
	float temp;
	//for(i=n+1;i<(range-1);i++) matrix[i][n]=0;
	for(i=n+1;i<(range-1);i++){
		temp=matrix[i][n]/matrix[n][n];
		for(j=n;j<range;j++){
			matrix[i][j]=matrix[i][j]-(matrix[n][j]*temp);
		}
	}
	return matrix;
}
float** multColumn(float** matrix,float val,int col){
	int i;
	for(i=col-1;i>=0;i--){
		matrix[i][col]*=val;
	}
	return matrix;
}
int main(void){
	float **matrix,term,*answers;
	int range,i,j;
	
	printf("Enter the number of variables\t");
	scanf("%d",&range);
	range++;
	matrix=(float**)malloc(sizeof(float*)*(range-1));
	answers=(float*)malloc(sizeof(float)*(range-1));
	for(i=0;i<range;i++){
		matrix[i]=(float*)malloc(sizeof(float)*range);
	}
	printf("Enter the coefficients separated with spaces\n");
	for(i=0;i<(range-1);i++){
		printf("Enter equation number  %d\n",(i+1));
		for(j=0;j<range;j++){
			scanf("%f",&matrix[i][j]);
		}
	}
	for(i=0;i<(range-1);i++){//rows
		matrix=maxRowPivot(matrix,range,i);
		display(matrix,range);
		matrix=subtractRows(matrix,range,i);
		printf("Operation done %d \n",(i+1));
		display(matrix,range);
		printf("\n");
	}
	for(i=(range-2);i>=0;i--){
		term=matrix[i][range-1];
		if(matrix[i][i]==0){
			printf("No solution possible\n");
			exit(0);
		}
		for(j=i+1;j<(range-1);j++) term-=matrix[i][j];
		term/=matrix[i][i];
		answers[i]=term;
		matrix=multColumn(matrix,term,i);
		display(matrix,range);
		printf("val of %d is %f\n",(i+1),term);
	}
	printf("Solutions - \n");
	for(i=0;i<(range-1);i++){
		printf("%f\t",answers[i]);
	}
	return 0;
}
