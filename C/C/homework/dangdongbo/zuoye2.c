#include<stdio.h>
int main()
{
	int a,b,c,d;
	scanf("%d%d%d",&a,&b,&c);

	if((a%4==0&&a%100!=0)||a%400==0)
	{
			printf("是润年");
			if(b<=7)
	        if(b>2)
			d=30*(b-2)+29+b/2+c;		
			else d=31*(b-1)+c;
			else d=213+30*(b-8)+c+(b-8)/2;
			printf("%d\n",d);
			}
	else
{
			printf("不是润年");
			if(b<=7)
			if(b>2)		
			d=30*(b-1)+b/2+c-2;
			else d=31*(b-1)+c;
			else d=212+30*(b-8)+c+(b-8)/2;
			printf("%d\n",d);
}}
