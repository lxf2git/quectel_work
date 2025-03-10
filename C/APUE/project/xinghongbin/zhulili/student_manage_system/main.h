#ifndef _MAIN_H_
#define _MAIN_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct student
{
	int num;
	int age;
	struct student *next;
	void (*stu_print)(struct student *);//单个学生的输出函数
	int (*stu_input)(struct student *);//单个学生的输入函数
}sStu,*pStu;

typedef struct list
{
	pStu head;  	
	int (*pInsert)( pStu pHead,  pStu pInsert,
		        int (*pIDFind)(pStu pHead,pStu pInsert),
		        pStu (*pInsertPosition)(pStu pHead,pStu pInsert) );
	int (*pDel)( pStu pHead,
		     pStu (*pDelPosition)(pStu pNode,int age));
	void (*pPrint)(pStu pHead);
	int (*pSearch)( pStu pHead, 
		        int (*pFun_Search[2])(pStu pHead,int num));
	int (*pStu_Save)(pStu pHead,FILE*fd);
}sList,*pList;

int pinsert(pStu pHead, pStu pnew,
		int (*pIDFind)(pStu pHead, pStu pInsert), 
		pStu (*pInsertPosition)(pStu pHead,pStu pInsert) );
pStu pInsertposition(pStu pHead,pStu pnew);
void   insert_back(pStu pmax_front,pStu pnew);
int pidFind(pStu pHead,pStu pnew);
int stu_input(struct student *pHead);

void stu_print(struct student *pHead);
void pPrint(pStu pHead);
int pStu_Save(pStu pHead,FILE*fd);
void save_list(pStu pHead);

int pSearch(pStu pHead, int (*pFun_Search[2])(pStu pHead, int num));
int (*pFun_Search[2])(pStu pHead,int num);
void find(pStu pHead);
int search_num(pStu pHead,int num);
int search_age(pStu pHead,int num);

void delete_node_age(pStu pHead,int Age);
pStu pDelposition(pStu pHead, int age) ;
int pdel(pStu pHead, pStu (*pDelPosition)(pStu pHead, int age) );
void delete_node(pStu pHead);











#endif
