#include"huffman.h"

int uncompress_file(char *fname)
{
	FILE *phm = NULL;	//压缩后的文件
	FILE *pc = NULL;	//还原文件
	char new_file[256];
	pNode proot = NULL;
	pNode pHead = NULL;

	phm = fopen(fname,"r");
	if(phm == NULL)
	{
		printf("hm: cannot compress`%s' : No such file\n",fname);//判断被解压缩文件是否存在
		return FAIL;
	}
	
	read_huffman_tree(&proot,phm);	//将huffman树还原	
//	show_tree(proot);
	
	sprintf(new_file,"%s.c",fname);
	pc = fopen(new_file,"w");
	if(pc == NULL)
	{
		printf("uncompress fail\n");
		return FAIL;
	}
//	printf("out\n");
	do_uncompress(phm,pc,proot);

	fclose(phm);
	fclose(pc);
	return SUC;
}
void do_uncompress(FILE *phm,FILE *pc,pNode proot)
{
	int i = 0;
	char ch;

//	printf("out\n");
	pNode ptmp = proot;	
	ch = fgetc(phm);
	while(!feof(phm))
	{
//	printf("in char\n");
		while(i<8)
		{
//	printf("in bit\n");
			if((ch & 0x80) == 0x00)
			{
//	printf("out0\n");
				ptmp = ptmp->rc;
//				printf("0");
			}
			if((ch & 0x80) == 0x80)
			{
//	printf("out1\n");
				ptmp = ptmp->lc;
//				printf("1");
			}
			ch <<= 1;
			if(ptmp->data != 0)
			{
//	printf("outch\n");
//	printf("ch========%c\n",ptmp->data);
				fwrite(&ptmp->data,1,1,pc);
				ptmp = proot;
			}
			i++;
		}
//		printf(" ");
		i = 0;
		ch = fgetc(phm);
	}
}
