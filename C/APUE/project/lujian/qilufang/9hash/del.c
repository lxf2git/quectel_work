#include"main.h"
void distribute(pMod hash,int *arr,int nb)
{
	pData pnew;
	int i,j,k;
	for(i=0;i<nb;i++)
			for(j=0;j<5;j++)
					for(k=0;k<8;k++)
					{
						if(arr[i]%5==j&&(((arr[i])>>3)&7)==k)
						{
							init_data(&pnew,sizeof(sData));
							pnew->data=arr[i];
							chain_back(hash->mod[j]->an[k],pnew);
						}
					}
}
void chain_back(pData pHead,pData pnew)
{
	pHead->next->prev=pnew;
	pnew->prev=pHead;
	pnew->next=pHead->next;
	pHead->next=pnew;
}
void output(pMod hash)
{
	int i,j,k;
	pData ptmp;
	for(j=0;j<5;j++)
		for(k=0;k<8;k++)
		{
			if(hash->mod[j]->an[k]->next==hash->mod[j]->an[k])	
					printf("J[%d]K[%d]:没有存数：\n",j,k);	
			else
			{
			for(ptmp=hash->mod[j]->an[k]->next;ptmp!=hash->mod[j]->an[k];ptmp=ptmp->next)
				{
					
						printf("Mod:%d And:%d Data:%d\n",j,k,ptmp->data);
				}			
			}	
		}
}
