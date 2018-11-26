#include <stdio.h>
typedef struct Poly 
{
	int arr[100];
	int length;
} Poly;
void init_poly(Poly *P)
{
	int l, i, c;
	printf("Input length: ");
	scanf("%d",&l);
	P->length=l;
	for(i=P->length-1;i>=0;i--)
	{
		P->arr[i]=0;
	}
	printf("No of Coff to be inputed:");
	scanf("%d",&l);
	while(l--)
	{
		printf("Enter Coff (c,i) ");
		scanf("%d %d",&c,&i);
		P->arr[i]=c;
	}
}
Poly add(Poly P1,Poly P2)
{
	Poly P3;
	int i;
	P3.length=P1.length>P2.length? P1.length : P2.length;
	for(i=P3.length-1;i>=0;i--)
	{
		P3.arr[i]=0;
		if(i<P1.length)
			P3.arr[i]+=P1.arr[i];
		if(i<P2.length)
			P3.arr[i]+=P2.arr[i];
	}
	return P3;
}
Poly sub(Poly P1,Poly P2)
{
	Poly P3;
	int i;
	P3.length=P1.length>P2.length? P1.length : P2.length;
	for(i=P3.length-1;i>=0;i--)
	{
		P3.arr[i]=0;
		if(i<P1.length)
			P3.arr[i]+=P1.arr[i];
		if(i<P2.length)
			P3.arr[i]-=P2.arr[i];
	}
	return P3;
}
int degree (Poly P1)
{
	int i;
	for(i =P1.length;i>=0;i--)
	{
		if(P1.arr[i]!=0)
			return i;
	}
	return 0;
}
void multiply_constant (Poly *P1,int c)
{
	int i;
	for(i =P1->length;i>=0;i--)
	{
		P1->arr[i]*=c;
	}
}
void display(Poly P)
{
	int i;
	for(i=P.length-1;i>0;i--)
	{
		if(P.arr[i]!=0)
			printf("%dx^%d +",P.arr[i],i);
	}
	if(P.arr[0]!=0)
		printf("%d",P.arr[i]);
	else
		printf("\b\b\b");
}
int main()
{
	Poly P1;
	init_poly(&P1);
	//Poly P2;
	//init_poly(&P2);
	//Poly P3=add(P1,P2);
	multiply_constant(&P1,5);
	display(P1);
}
