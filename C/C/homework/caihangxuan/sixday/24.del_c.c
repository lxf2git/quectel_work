#include<stdio.h> 
int main()
{
	char a[100];
	int i,n;
	printf("请输入字符");
	for(i=0;;i++)
	{
		scanf("%c",&a[i]);
		if(a[i]=='\n')
			break;
		else if(a[i]=='c')
			i--;
	}
	i=i-1;
	for(n=0;n<=i;n++)
	{
		printf("%c",a[n]);
	}
	printf("\n");
}
