//Program for bisection method for x*x-x-6
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define f(x) (x*x-x-6)
int main(void){
    float x0=0,x1=0,x2=0,y0=0,y1=0,y2=0;int iter =0;
    printf("Solution for Equation using bisection method x*x-x-6\n ");
    do{ 
        printf("Enter Range :");
        scanf("%f %f",&x0,&x1);
        y0=f(x0),y1=f(x1);
        if(y0==0){
            printf("The solution is %f",x0);
            exit(0);
        }
        else if(y1==0){
            printf("The solution is %f",x1);
            exit(0);
            }
        }while((y0*y1)>0);
        printf("Iteration  \tx0  \t x1  \t Mid  \t   f(x0) \t f(x1) \t  f(Mid)"); 
        do{
        x2=(x0+x1)/2.0;
        y2=f(x2);
        printf("\n%d\t  %f   %f  %f  %f  %f   %f\n",(++iter),x0,x1,x2,y0,y1,y2); 
        if(y0*y2>0)
            x0=x2;
        else
            x1=x2;
        y0=f(x0),y1=f(x1);
        }while(x1-x0>=0.000001||x1-x0<=-0.000001);
        x2=(x1+x0)/2.0;
        printf("\nThe solution is %f\n ",x2);
        return 0;
}

