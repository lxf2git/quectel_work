#include<stdio.h>

int main()
{
	long a, b, c, d;
	printf("请输入一个数");
	scanf("%d",&a);
	scanf("%d",&b);
	a = a % 10 + (a % 1000 / 100) * 100;
	printf("a%d  ",a);
	b = (b % 10000 / 1000 * 1000) + (b %100 / 10) * 10;
	printf("b%d",b);
	c = a + b;
	printf("组合后的数%d",c); 
}
