#ifndef _MAIN_H_
#define _MAIN_H_

#include<stdio.h>
#include<stdlib.h>
enum name
{
	inputA = 1,
	inputB,
	print,
	del,
	quit
};

typedef struct node
{
	int data;	
	struct node *next;
	struct node *prev;
}sNode,*pNode;


void insertA(pNode pHeadA);
void insertB(pNode pHeadB);
void init_node(pNode *p,int size);
void delete_node(pNode pHeadA,pNode pHeadB);
void pPrint(pNode pHeadA,pNode pHeadB);

#endif
