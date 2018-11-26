// Integration Using Simpsons's 1/3 Rule
#include<stdio.h>
#include<math.h>

float f(float x){
	return 1/(1+x);
}

float integration(float ul,float ll,int n){
	int i;
	float h=(ul-ll)/n;
	float y0=f(ll);
	float yn=f(ul);
	float s1=0,s2=0;
	for (i=0;i<n/2;i++)
		s1+=f(ll+2*i*h+h);
		
	for (i=0;i<n/2-1;i++)
		s2+=f(ll+2*i*h+2*h);

	return h*(y0+4*s1+2*s2+yn)/3;


}

main(){
	float a,b;
	float h;
	float I1,I2;
	int n=1;
	printf("Enter the lower and upper limits of integral: ");
	scanf("%f %f",&a,&b);
	
	//n=12;
	//I1=integration(b,a,n);
	
	do{
		n*=2;
		I2=I1;
		I1=integration(b,a,n);
	
	}while (fabs(I1-I2)>=0.0005);
	

	printf("The result is %f .\n",I1);
}
