#ifndef _MIAN_H_
#define _MAIN_H_
#include<stdlib.h>
#include<stdio.h>
typedef struct data
{
		int data;
		struct data *prev;
		struct data *next;
}sData,*pData;

typedef struct an
{
		struct data *an[8];
}sAnd,*pAnd;

typedef struct mod
{
		struct an *mod[5];
}sMod,*pMod;
void distribute(pMod hash,int *arr,int nb);
void getmemory(void **p,int size);
void init_data(pData *p,int size);
void chain_back(pData pHead,pData pnew);
void output(pMod hash);
#endif
