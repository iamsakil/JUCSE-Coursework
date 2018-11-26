#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct List{
	int data[MAX_SIZE];
	int len;
}List;
void initList(List *l){
	l->len=0;
	int i;
	for(i=0;i<MAX_SIZE;i++){
		l->data[i]=0;
	}
}
int isEmpty(List l){
	if(l.len==0)
		return 1;
	return 0;
}
int isFull(List l){
	if(l.len==MAX_SIZE-1)
		return 1;
	return 0;
}
int len(List l){
	return l.len;
}
int read(List l,int n){
	return l.data[n-1];
}
void write(List *l,int n,int w){
	l->data[n-1]=w;
}
void insertEnd(List *l,int x){
	if(isFull(*l)==1)
		printf("List is full");
	else{
		l->data[l->len]=x;
		l->len++;
	}
}
void del(List *l,int n){
	if(isEmpty(*l)==1 || n>(l->len))
		printf("List is empty");
	else{
		int i;
		for(i=n-1;i<(l->len-1);i++){
			l->data[i]=l->data[i+1];
		}
		l->len--;
	}	
}
int search(List l,int key){//returns -1 if not found
	int i;
	for(i=0;i<l.len;i++){
		if(l.data[i]==key)
			return key;
	}
	return -1;
}
void print(List l){
	int i;
	for(i=0;i<l.len;i++){
		printf("%d  ",l.data[i]);
	}
	printf("\n");
}
int main(){
	List L;
	initList(&L);
	insertEnd(&L,12);
	insertEnd(&L,32);
	insertEnd(&L,14);
	insertEnd(&L,4);
	del(&L,3);
	print(L);
	return 0;
}
