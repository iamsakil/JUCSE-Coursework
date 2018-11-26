#include<stdio.h>
#include<math.h>
int main()
{
	int it;
	float num1,num2,x=1.0;
	float fn1,fn2,fn3,dfn1,dfn2,dfn3;//Initialization
	
	fn1=sqrt(x+6);
	fn2=1+6.00/x;
	fn3=pow(x,2)-6;
	dfn1=1.0/(2*sqrt(x+6));
	dfn2=(-1.0)*6.0/pow(x,2);
	dfn3=2*x;
	
	it=1;
	num1=x;
	
	printf("\t\tLET US SOLVE THE EQUATION:\n\n\t\t\tx^2-x-6=0 \n\n\t\tusing g(x)=sqrt(x+6)\n");
	if(dfn1>(-1)&&dfn1<(1))//for 1 st function
	{
		printf("\n\t\tFinding the positive solution\n");
		num2=sqrt(num1+6);
		printf("\n Iteration No\t\t Xo\t\t X1\t\t Ei=|Xo-X1|\n");
		while((num2-num1)>0.000001||(num2-num1)<-0.000001)
		{
			if(1.0/(2*sqrt(num1+6)) < -1 || 1.0/(2*sqrt(num1+6)) >1)
			{
				printf("\tIT IS DIVERGING\n");
				break;
			}
			printf("\t%d\t %f\t %f %f",it,num1,num2,(num2-num1));
			num1=num2;
			num2=sqrt(num1+6);
			it++;
			printf("\n");
		} //equation for positive root
		printf("\n\tthe positive solution of the given equation is %.5f",num2);
		printf("\n\n");
	
		printf("\t\tFinding the negative solution\n");
		it=1;
		num1=x;
		num2=(-1)*sqrt(num1+6);
	
		printf("\n Iteration No\t\t Xo\t\t X1\t\t Ei=|Xo-X1|\n");
		while((num2-num1)>0.000005||(num2-num1)<-0.000005)
		{
			if(-1.0/(2*sqrt(num1+6)) < -1 || -1.0/(2*sqrt(num1+6)) >1)
			{
				printf("\tIT IS DIVERGING\n");
				break;
			}
			printf("\t%d\t %f\t %f %f",it,num1,num2,(num2-num1));
			num1=num2;
			num2=(-1)*sqrt(num1+6);
			it++;
			printf("\n");
		} //equation for negative root
		printf("\n\tthe negative solution of the given equation is %f",num2);
		printf("\n\n\n");
	}
	else
		printf("\n\tIT IS DIVERGING\\n\n\n");
	
	it=1;
	num1=x;
	
	printf("\t\tLET US SOLVE THE EQUATION:\n\n\t\t\tx^2-x-6=0 \n\n\t\tusing g(x)=1+6/x\n");
	if(dfn2>-1&&dfn2<1)//for 2 nd function
	{
		num2=1+6.0/num1;
		printf("\n Iteration No\t\t Xo\t\t X1\t\t Ei=|Xo-X1|\n");
		while((num2-num1)>0.000001||(num2-num1)<-0.000001)
		{
			if((-6.00/num2*num2) < -1 || (-6.0/num2*num2) >1)
			{
				printf("\tIT IS DIVERGING\n");
				break;
			}
			printf("\t%d\t %f\t %f %f",it,num1,num2,(num2-num1));
			num1=num2;
			num2=1+6.0/num1;
			it++;
			printf("\n");
		}
	}
	else
		printf("\n\n\t\tIT IS DIVERGING\n\n\n");
	it=1;
	num1=x;
	
	printf("\t\tLET US SOLVE THE EQUATION:\n\n\t\t\tx^2-x-6=0 \n\n\t\tusing g(x)=x^2-6\n");
	if(dfn2>-1&&dfn2<1)
	{
		num2=num1*num1-6;
		printf("\n Iteration No\t\t Xo\t\t X1\t\t Ei=|Xo-X1|\n");
		while((num2-num1)>0.000001||(num2-num1)<-0.000001)
		{
			if(2*num2< -1 || 2*num2 >1)
			{
				printf("\tIT IS DIVERGING\n");
				break;
			}
			printf("\t%d\t %f\t %f %f",it,num1,num2,(num2-num1));
			num1=num2;
			num2=num1*num1-6;
			it++;
			printf("\n");
		}
	}
	else
		printf("\n\n\t\tIT IS DIVERGING\n\n\n");
	return 0;
}
