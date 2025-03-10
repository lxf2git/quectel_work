#ifndef APUE_H_
#define APUE_H_
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

typedef struct ftp
{
	char ftp_usrname[30];
	char ftp_passwd[30];
	struct ftp *prev;
	struct ftp *next;
}sF,*pF;

static show_err(char *str)
{
	perror(str);
	exit(-1);
}
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

void *thread1(void *p);
int  getfile(char *filename,char *file ,int confd);
void putfile(char *filename,char *file);
void putdocument(char *filename,char *file,int confd);
int  getdocument(char *filename,char *file,int confd);
void find(char *filename,char *file ,int a,int confd);
void make(char *filename,int a);
int getandput(char *filename ,char *file,int a,int b,int confd,int num);
void create_memory(pF *pnode);
void init_node(pF *pnode);
void creat_tail_chain(pF pHead,char *name,char *passwd);
int login_infor(pF pHead,char *name,char *passwd,int a);
void delete(pF pHead,char *name);
void show_chain(pF pHead);

#endif

