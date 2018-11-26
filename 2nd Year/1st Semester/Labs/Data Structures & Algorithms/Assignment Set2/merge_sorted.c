int main()
{
    int m,n,i;
    printf("Enter size of arrays\n");         //input
    scanf("%d %d",&m, &n);
    int a[m], int b[n];
    printf("Enter elements of 1st array\n");
    for(i=0;i<m;i++)
        scanf("%d",(a+i));
    printf("Enter elements of 2nd array\n");
    for(i=0;i<n;i++)
        scanf("%d",(b+i));

    merge(a, b, m, n);
 
    printf("After Merging\n");
    for (i=0; i<m; i++)
        printf("%d ",a[i]);
    for (i=0; i<n; i++)
        printf("%d ",b[i]);
    return 0;
}
void merge(int a[], int b[], int m, int n)
{
    for (int i=n-1; i>=0; i--)
    { 
        int j, end = a[m-1];      /* We find the smallest element>b[i]& shift all
                                    elements one position ahead till smallest greater
                                    element is not found*/
        for (j=m-2; j >= 0 && a[j] > b[i]; j--)
            a[j+1] = a[j]; 
                                    // For greater element
        if (j != m-2 || end > b[i])
        {
            a[j+1] = b[i];
            b[i] = end;
        }
    }
}
