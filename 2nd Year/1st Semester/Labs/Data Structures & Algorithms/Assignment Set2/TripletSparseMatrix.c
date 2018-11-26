#include <stdio.h>
#include <stdlib.h>
typedef struct Node  //Each element stored int the sparse matric has row col and key
{
	int row;
	int col;
	int key;
}Node;
void init_Node(Node *N,int r,int c,int k)
{
	N->row=r;
	N->col=c;
	N->key=k;
}



typedef struct Sparse_Matrix
{
	int n;
	int max_size;
	int rows;
	int cols;
	Node Array[100];
}Sparse_Matrix;
void init_Sparse_Matrix(Sparse_Matrix *M,int size)
{
	
	//M=malloc(sizeof(M) +size*sizeof(M->Array));
	M->max_size=size;//size is max size of SM
	M->n       =0;   //no of element in SM
	M->rows=0;
	M->cols=0;
	int i;
	for(i=0;i<size;i++)
	{
		init_Node(&M->Array[i],0,0,0);
	}
}



void swap(int *a,int *b)
{
	int *temp=a;
	a=b;
	b=temp;
}
void transpose(Sparse_Matrix *M)
{
	int i;
	for(i=0;i<M->n;i++)
	{
		init_Node(&(M->Array[i]),M->Array[i].col,M->Array[i].row,M->Array[i].key);
	}
	swap(&(M->rows),&(M->cols));
}

void add_node(Sparse_Matrix *M,int r,int c,int k)
{
	if(M->n< M->max_size)
	{
		
		int n=M->n;
		init_Node(&(M->Array[n]),r,c,k);
		if(r>M->rows)
			M->rows=r;
		if(r>M->cols)
			M->cols=c;
		M->n++;
	}
	
}

void display_sparse_matrix(Sparse_Matrix *M)
{
	int rows=M->rows;
	int cols=M->cols;
	int arr[rows][cols];
	int i,j;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			arr[i][j]=0;
		}
	}
	for(i=0;i<M->n;i++)
	{
		arr[M->Array[i].row][M->Array[i].col]=M->Array[i].key;
	}
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%d ",arr[i][j]);
		}printf("\n");
	}
	free(&arr);
}
void multiply_constant(Sparse_Matrix *M,int c)
{
	int i;
	for(i=0;i<M->n;i++)
	{
		init_Node(&(M->Array[i]),M->Array[i].row,M->Array[i].col,c*M->Array[i].key)	;	
	}
}
void print_sparse_matrix(Sparse_Matrix *M)
{
	int i=0;
	int n=M->n;
	printf("ROW\tCOL\tKEY\n");
	while(i<n)
	{
		printf("%d\t%d\t%d\n",M->Array[i].row,M->Array[i].col,M->Array[i].key);
		i++;
	}
}
int main()
{
	Sparse_Matrix M1;
	Sparse_Matrix M2;
	int choice;
	while(1)
	{
		printf("1.Enter 1st Sparse Matrix\n");
		printf("2.Enter 2nd Sparse Matrix\n");
		printf("3.Multiply SM1 with a constant\n");
		printf("4.Add the 2 SM's\n");
		printf("5.Multiply 2 SM's\n");
		printf("6.Tranpose SM 1\n");
		printf("7.Print SM 1\n");
		printf("8.Display SM 1\n");
		printf("9.Exit\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			int n;
			printf("Enter no of elements to enter:");
			scanf("%d",&n);
			init_Sparse_Matrix(&M1,n);
			while(n-->0)
			{
				printf("Enter elements(r,c,k): ");
				int r,c,k;
				scanf("%d  %d  %d",&r,&c,&k);
				add_node(&M1,r,c,k);
			}
			print_sparse_matrix(&M1); 
		}
		else if(choice==2)
		{
			int n;
			printf("Enter no of elements to enter:");
			scanf("%d",&n);
			init_Sparse_Matrix(&M2,n);
			while(n-->0)
			{
				
				printf("Enter elements(r,c,k): ");
				int r,c,k;
				scanf("%d  %d  %d",&r,&c,&k);
				add_node(&M2,r,c,k);
			}
			print_sparse_matrix(&M2);
		}
		else if(choice==3)
		{
			int c;
			printf("Enter the constant:");
			scanf("%d",&c);
			multiply_constant(&M1,c);
			print_sparse_matrix(&M1);
		}
		else if(choice==4)
		{
			
		}
		else if(choice==5)
		{
			
		}
		else if(choice==6)
		{
			
			transpose(&M1);
			//display_sparse_matrix(&M1);
		}
		else if(choice==7)
		{
			print_sparse_matrix(&M1);
		}
		else if(choice==8)
		{
			display_sparse_matrix(&M1);
		}
		else if(choice==9)
		{
			break;
		}
	}
	return 0;
}
