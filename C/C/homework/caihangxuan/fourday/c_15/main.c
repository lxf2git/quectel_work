#include<stdio.h>
#include"yue_shu.h"
/*#include"add.h"*/
int main()
{
        int nu;
	printf("请输入100-500间的任意数。");
	scanf("%d",&nu);
	
	nu=yue_shu(nu);
	/*	add(yue_shu(nu));*/
}
