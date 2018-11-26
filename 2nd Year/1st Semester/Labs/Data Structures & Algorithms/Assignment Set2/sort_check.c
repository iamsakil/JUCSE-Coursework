#include <stdio.h>
#include <stdlib.h>
int main()
{
    int m;
    printf("Enter size of array\n");
    scanf("%d",&m);
    int a[m];
    printf("Enter elements of array\n");  //input
    int i;
    for(i=0;i<m;i++)
        scanf("%d",(a+i));
    if(a[0]<a[1])
    {
        for(i=2;i<m-1;i++)                //checking if it's in ascending order
        {
            if(a[i-1]>a[i] || a[i]>a[i+1])
            {
                printf("unsorted");
                break;
            }
        
        }printf("Sorted in ascending order");
    }
    else
    {
        for(i=2;i<m-1;i++)               //checking if it's in descending order
        {
            if(a[i-1]<a[i] || a[i]<a[i+1])
            {
                printf("unsorted");
                break;
            }
        
        }printf("Sorted in descending order");
    }
}
