#include"reorder.h"
#define N 4

void reorder(char arr[])
{
	int i;
	for(i=0;i<N;i++)
	{
		scanf("%c",&arr[i]);
		getchar();
	}
	int j;				 
	char t,m,k=0;
	char brr[N]={0};
	for(i=0;i<N;i++)
	{
		for(j=0;j<N-1;j++)
		if(arr[j]>arr[j+1])
		{
			m=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=m;
		}
	}
	for(i=0;i<N;i++)
	printf("%c ",arr[i]);	
}
