#include"stack.h"
void getmemory(int **p)
{
	*p=malloc(sizeof(int)*SIZE);
	if(NULL==*p)
	{
		printf("getmemory_error!\n");
		exit(-1);
	}
}
void init_stack(pStack ps)
{
	getmemory(&ps->bottom);
	ps->top=0;
}
int push(pStack ps,int mod)
{
	if(ps->top==SIZE)
	{
		printf("stack pull!\n");
		return FULL;
	}	
	ps->bottom[ps->top]=mod;
	ps->top++;
	return SUC;
}
int pop(pStack ps,int *pop_data)
{
	if(ps->top==0)
	{
	//	printf("stack empty!\n");
		return EMPTY;
	}
	ps->top--;
	*pop_data=ps->bottom[ps->top];
	return SUC;
}
void myfree(pStack ps)
{
	if(ps->bottom != NULL)
	{
		free(ps->bottom);
	}
}
