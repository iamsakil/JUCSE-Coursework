//Programming to find the value by 1/(1-x) series
#include<stdio.h>
#include<math.h>

int main()
{

	float num,sum=1;
	int i=1;
	float temp;//initialization
	
	printf("Please input a value: ");
	scanf("%f",&num);
	temp=num;

	while((num>0.0000001)||(num<-0.0000001))
	{

		sum=sum+num;
		i++;
		num=pow(temp,i);
		
	}
		
	printf("So the value will be: %f",sum);
	return 0;

}
	
