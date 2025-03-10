#include"init.h"

void create_memory(pList *p,int size)
{
	*p = (pList)malloc(size);
	if(*p == NULL)
	{
		printf("malloc error");
		exit(-1);
	}
}

void init_node(pList *p,int size)
{	
	create_memory(p,size);		
}

void create_memory_pstu(pStu *p,int size)
{
	*p = (pStu)malloc(size);
	if(*p == NULL)
	{
		printf("malloc error");
		exit(-1);
	}
}

void init_node_pstu(pStu *p,int size)
{
	create_memory_pstu(p,size);
	(*p)->next = NULL;
}
