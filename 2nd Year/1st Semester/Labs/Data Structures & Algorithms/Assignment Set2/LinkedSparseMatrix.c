#include <stdio.h>
typedef struct Element 
{
	int key;
	int row;
	int col;
	struct Element *right;
	struct Element *down;
	
} Element;
typedef struct Header 
{
	struct Element *next;
} Head;
typedef struct Sparse_Matrix
{
	struct Element *index;
}Sparse_Matrix;
void add_node(Sparse_Matrix *M)
{
	int r,c,d;
	printf("Enter row col data (r,c,d)");
	scanf("%d %d %d",&r,&c,&d);
	Element *new_node;
	new_node->key=d;
	Head *right=M->index->right;
	while(right->next!=NULL)
	{
		
	}
	
}
int main()
{
	return 0;
}
