#include"save.h"

void save()
{
	pStu stmp;
	FILE *fp;
	if((fp=fopen("file","a"))==NULL)
	{
		printf("file_open_error!\n");
		exit(-1);
	}
	for(stmp=pHead;stmp->next != NULL;stmp=stmp->next)
	{
		fwrite(stmp->next->name,20*sizeof(char),1,fp);
		fwrite(&stmp->next->age,sizeof(int),1,fp);
		fwrite(&stmp->next->id,sizeof(int),1,fp);
	}
	fclose(fp);
}
void output(pStu stmp)
{
	printf("Name:%s Age:%d Id:%d\n",stmp->next->name,stmp->next->age,
						stmp->next->id);	
}
void put_chain()
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
