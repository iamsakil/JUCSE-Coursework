#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void sort(int* array, int length) {
	int t, k, i;
    for (i=1; i < length; i++) { // sort the array using insertion sort
        t = array[i];
		k = i-1;
        while (t < array[k] && k>=0) {
            array[k+1] = array[k];
			k--;
        }
        array[k+1] = t;
    }
}

int int_search(int arr[],int k)
{
	int i;
	for(i=0;arr[i]!='\0';i++)
	{
		if(arr[i]==k)
		return i;
	}
	return -1;
}
int int_bin_search(int min,int max,int arr[],int k)
{
	if(max>min)
		return -1;
	int mid=(min+max)/2;
	if(arr[mid]==k)
	{
		return mid;
	}
	else if (k<arr[mid])
	{
		return int_bin_search(min,mid,arr,k);
	}
	else
	{
		return int_bin_search(mid,max,arr,k);
	}
}


int float_search(float arr[],float k)
{
	int i;
	for(i=0;arr[i]!='\0';i++)
	{
		if(arr[i]==k)
		return i;
	}
	return -1;
}
int float_bin_search(int min,int max,float arr[],float k)
{
	if(max>min)
		return -1;
	int mid=(min+max)/2;
	if(arr[mid]==k)
	{
		return mid;
	}
	else if (k<arr[mid])
	{
		return float_bin_search(min,mid,arr,k);
	}
	else
	{
		return float_bin_search(mid,max,arr,k);
	}
}


int compare(char* str1, char* str2) 
{ 
	int length, i;
	length=(strlen(str1)<strlen(str2)) ? strlen(str1):strlen(str2); // ternanry operator to find lower of string lengths
	for (i=0; i<length; i++) 
	{
		if (str1[i]<str2[i]) 
			return -1;
		else if (str1[i]>str2[i]) 
			return 1;
	}
	if (strlen(str1)>strlen(str2)) 
		return 1; 
	else if (strlen(str1)<strlen(str2))
		return -1;
	return 0;
}

void char_sort(char** array, int length) 
{
	int k, i;
	char *t=(char*)malloc(20*sizeof(char));
    for (i=1; i < length; i++) 
	{ // sort array using inserion sort
        t=array[i];
        //printf ("%s",t);
        k = i-1;
        while (k>=0 && compare(t,array[k])==-1) 
		{
            array[k+1]=array[k];
			k--;
        }
        array[k+1]=t;
    }
}
int char_search(char* key, char** array, int length) {
	int i;
	for (i=0; i<length; i++) {
		if (!compare(array[i],key)) return i;
	}
	return -1; // return -1 if key is not found
}
int char_bin_search(char* key, char** array, int length) {
	int up, low, mid;
	up=length-1; low=0;
	while (low<=up) {
		mid=(up+low)/2;
		if (compare(key,array[mid])==-1) up=mid-1;
		else if (compare(key,array[mid])==1) low=mid+1;
		else return mid;
	}	
	return -1; // return -1 if key is not found
}

 
int main()
{
	return 0;
}
