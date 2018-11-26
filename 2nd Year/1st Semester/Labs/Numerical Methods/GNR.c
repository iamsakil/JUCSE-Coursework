#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define pre 0.000001
double f(double x)
{
	return pow(x,3) - pow(x,2) - x +1;
}
double df(double x)
{
	return 3*pow(x,2) - 2*pow(x,1) -1;
}
double d2f(double x)
{
	return 6*x - 2;
}

int main(void)
{
	int c=0;
	double X,X_Next,abse,absePrev,oc;
	printf("Enter initial approximation for root: ");
	scanf("%lf",&X);
	//FILE *fp;
	//fp=fopen("genNR.dat", "w+");	
  	printf("i \t x \t\t f(x) \t\t abserror \t oc");  	
	do{	
			X_Next=X-2*f(X)/df(X);
			c++;
			absePrev=abse;
			abse=fabs(X-X_Next);
			if(c==1)
			{
				oc=fabs(log(abse)/log(absePrev));
			}	
			printf("\n%d  	 %lf  	 %lf   	%lf	 %lf", c, X,f(X),abse,oc);
			if(fabs((f(X_Next)*d2f(X_Next))/ (df(X_Next)*df(X_Next)) )>=1)
			{
				printf("\nWon't converge.\n");
				exit(0);
			}	
		    if(f(X)==0)
		    break;
	        X=X_Next;
	        	
	}while(abse>pre);	
	printf("\nThe root is %lf\n", X);
	//fclose(fp);
	return 0;
}
