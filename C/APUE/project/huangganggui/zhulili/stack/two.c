#include"two.h"

void two_jinzhi(pStack ps,int data,int mod,int *pop_data)
{
	while(data!=0)
	{
		mod = data%2;  //余数
		push(mod,ps);
		data = data/2;
		
	}
	while( pop(ps,pop_data) != EMPTY)
	{
		printf("%d ",*pop_data);
	}
	printf("\n");
}
