#include"create.h"


pNode create_single_chain(pDis pHead_D)
{
	pDis pnew = NULL;
	pDis ptmp = pHead_D;
	int i;
	//单链表输入0 1 2 3 4  5 6 7 8 9 10
	for(i=0;i<10;i++)
	{
		init_node(&pnew,sizeof(sDis));
		init_node_node(&pnew->record,sizeof(sDis));
		pnew->record->data = i;
		ptmp->next = pnew;
		pnew->next = pHead_D;
		ptmp = pnew;
	}
	for(ptmp=pHead_D->next;ptmp!=pHead_D;ptmp=ptmp->next)
		printf("%d ",ptmp->record->data);
		printf("\n");
}
pNode create_double_chain(pNode pHead_N,int num)
{
	pNode pnew_N  = NULL;
	pNode ptmp = NULL;
	int i;
	//双链表输入比较的数字
	pnew_N  = NULL;
	printf("输入比较的数据:\n");
	for(i=0;i<num;i++)
	{
		init_node_node(&pnew_N,sizeof(sNode));
		scanf("%d",&pnew_N->data);
		pnew_N->prev = pHead_N->prev;
		pHead_N->prev->next = pnew_N;	
		pHead_N->prev = pnew_N;
		pnew_N->next = pHead_N;
	}	

}
