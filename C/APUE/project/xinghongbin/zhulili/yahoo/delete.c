#include"delete.h"

void delete_node(pNode pHeadA,pNode pHeadB)
{
	pNode ptmpA = NULL;
	pNode ptmpB = NULL;
	pNode pdelA = NULL;
	pNode pdelB = NULL;
	pNode pTravA = NULL;  //要删除节点的前一个节点
	pNode pTravB = NULL;
	int i = 0;
	for(ptmpA=pHeadA->next;ptmpA!=pHeadA;ptmpA=ptmpA->next)
	{
		for(ptmpB=pHeadB->next;ptmpB!=pHeadB;ptmpB=ptmpB->next)
		{	
			if(ptmpA->data == ptmpB->data)
			{  	
				pdelB = ptmpB;
				pTravB = pdelB->prev;
				pTravB->next = pdelB->next;
				pdelB->next->prev = pTravB;
				pNode ptmp;
				//pdelB->next = NULL;
				//pdelB->prev = NULL;
				i = 1;
			}
		}		
		if(i == 1)	
		{			
				pdelA = ptmpA;
				pTravA = pdelA->prev;
				pTravA->next = pdelA->next;
				pdelA->next->prev = pTravA;
				//pdelA->next = NULL;
				//pdelA->prev = NULL;			
		}
		i = 0;
	}
	printf("删除后的链表A和链表B的数据为：\n");
	if(pHeadA->next == pHeadA && pHeadB->next == pHeadB)
	{
		printf("A和B的链表相同，都被删除！\n");
	}
	pPrint(pHeadA,pHeadB);
}



