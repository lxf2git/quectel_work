#include"main_strcat.h"

int main()
{
	int i;
	char str1[100]={0};
	char str2[20]={0};
	for(i=0;i<N;i++)
	{
		str1[i]=getchar();
		getchar();	
	}
	for(i=0;i<N;i++)
	{
		str2[i]=getchar();
		getchar();	
	}
	mystrcat(str1,str2);
	printf("str1:%s\n",str1);
	return 0;
}
