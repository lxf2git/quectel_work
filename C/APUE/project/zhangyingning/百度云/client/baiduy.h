#ifndef _BAIDUY_H_
#define _BAIDUY_H_
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<shadow.h>
#include<unistd.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<signal.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<assert.h>
#include<errno.h>
typedef struct
{
		int file_type;
		char file_name[100];	
}sM_F,*pM_F;

enum flag
{
		REGISTER,
		LOGIN,
		PUT,
		GET,
		MKDIR,
		FIND
};
typedef struct
{
		enum flag cmd;
		char usrname[30];
		char passwd[30];
		char buf[512];
		int num;
		sM_F file_op;
	
}sBdy,*pBdy;

typedef struct record
{
		char file[30];
		int flag_up_down;
		struct record *next;
}sRe,*pRe;

int op_deal(int tmp);
void creat_record_chain(pRe pHead,pRe pnode);
void init(pRe *ptmp);
void dele(pRe pHead);

#endif
