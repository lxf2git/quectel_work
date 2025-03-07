#include"save.h"
void print(pStu pHead,sList slist)
{
	slist.pPrint=put_chain;
	slist.pPrint(pHead);
}
void save_pStu(pStu pHead,sList slist)
{
	slist.pStu_Save=save;
	FILE *fp;
	if((fp=fopen("file","a"))==NULL)
	{
		printf("file_open_error!\n");
		exit(-1);
	}
	slist.pStu_Save(pHead,fp);
}
int save(pStu pHead,FILE *fp)
{
	pStu stmp;
	
	for(stmp=pHead;stmp->next != NULL;stmp=stmp->next)
	{
		fwrite(stmp->next->name,20*sizeof(char),1,fp);
		fwrite(&stmp->next->age,sizeof(int),1,fp);
		fwrite(&stmp->next->id,sizeof(int),1,fp);
	}
	fclose(fp);
	return;
}
void output(pStu stmp)
{
	printf("Name:%s Age:%d Id:%d\n",stmp->next->name,stmp->next->age,
						stmp->next->id);	
}
void put_chain(pStu pHead)
{
	pStu stmp;
	stmp=pHead;
	while(stmp->next != NULL)
	{
		stmp->stu_print=output;
		stmp->stu_print(stmp);	
		stmp=stmp->next;
	}	
}
