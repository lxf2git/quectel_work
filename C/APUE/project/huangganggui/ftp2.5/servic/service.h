#ifndef SERVICE_H
#define SERVICE_H
#define DATA 200
#include "../../apue.h"
#define NONE "\e[0m"
#define  RED "\e[40;31m"
#define  GREED "\e[40;32m"
#define SAN "\e[31m\033[05m"
#define YEL "\e[40;33m" 
#define WIT "\e[40;37m" 
#define PRO "\e[40;35m" 
union userOrCmd
{
		char user[DATA];
		char cmd[DATA];

};
union passwdOrData
{
		char passwd[DATA];
		char data[DATA];

};
typedef struct info
{
		union userOrCmd uoc;
		union passwdOrData pod;
		char addr[DATA];
		char mode; /* 0 请求认证  1 执行命令*/


}sData;
typedef struct Goin  //登录结构体
{
		char addr[DATA];
		char user[DATA];
		struct Goin *next;
		struct Goin *prev;
}*pGoin;

int my_strcmp(char *buf);
void my_wait(int sig);
void my_exit(int sig);
void my_jump(int sig);
int wait_connect(int sockfd,int*fdPipe);
int read_data(int sockfd,struct sockaddr_in caddr,int *fdPipe);
int send_data(int sockfd,int mode);
int deal_pess(int *fdPipe);
int init_chain(pGoin *p);
int show_chain(pGoin pHead);
int search(pGoin pHead,pGoin pSear);
int insert(pGoin pHead,pGoin pInsert);
int delete(pGoin pHead ,char *user);
int cmd_deal(sData,int cockfd);
int client_pess(char *name,int semid,struct sembuf buf);
int  deal_child_process(struct info judge,int sockfd);
int deal_apply(char *cmd,int fd,int sockfd);
#endif
