#include<stdio.h>
int main()
{
	int i;
	printf("请输入数字：\n");
	scanf("%d",&i);
	if(i>=1&&i<=7)
	{
	if(i==1)
	{
		printf("monday\n");
	}
	if(i==2)
	{
		printf("tuesday\n");
	}
	if(i==3)
	{
		printf("wednesday\n");
	}
	 if(i==4)
        {
                printf("thursday\n");
	}
	 if(i==5)
        {
                printf("friday\n");
	}
	 if(i==6)
        {
                printf("saturday\n");
	}
	 if(i==7)
        {
                printf("sunday\n");
	}
	}
	else 
	{
	printf("输入错误！\n");
	}
}
