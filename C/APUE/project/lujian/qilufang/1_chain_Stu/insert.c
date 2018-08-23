#include"./insert.h"
pStu loction(pStu pHead,pStu pnew)
{
	pStu stmp=pHead;
	while(stmp->next != NULL)
	{
			if(stmp->next->id >= pnew->id)
			{
				return stmp;
			}
			stmp=stmp->next;
	}
	return stmp;
}
int id_find(pStu pHead,pStu pnew)
{
	pStu palit=pHead;
	while(palit->next!=NULL)
	{
		if(palit->next->id==pnew->id)
		{
			return 0;
		}
		palit=palit->next;
	}
	return 1;
}
int insert_back(pStu pHead,pStu pnew,int (*pIDfind)(pStu pHead,pStu pnew),
			pStu (*pInsertPosition)(pStu pHead,pStu pnew))
{
		int i =	pIDfind(pHead,pnew);
		if(i)
		{
				pStu palit = pInsertPosition(pHead,pnew);
				pnew->next=palit->next;
				palit->next=pnew;
		}
		else
		{
				printf("输入学生的id已存在！\n");
		}
	return 0;
}
int make_chain(pStu pnew)
{	
	printf("输入学生的Name Age Id:\n");
	scanf("%s%d%d",pnew->name,&pnew->age,&pnew->id);
	return 0;
}
void insert(pStu pHead,sList slist)
{
	pStu pnew=NULL;
	init_Stu(&pnew,sizeof(sStu));
	pnew->stu_input=make_chain;
	pnew->stu_input(pnew);
	slist.pInsert=insert_back;
	slist.pInsert(pHead,pnew,id_find,loction);
}

