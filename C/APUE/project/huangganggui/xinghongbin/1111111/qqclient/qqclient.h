#ifndef CLIENT_H
#define CLIENT_H
#include "apue.h"
#include <errno.h>
#define NONE "\e[0m"   //无色
#define RED "\e[40;31m"//黑第红
#define GRE "\e[40;32m"//黑第绿
#define YEL "\e[40;33m"//黄
#define WIT "\e[40;37m"//白
#define PRO "\e[40;35m"//紫
#define SERVIC_PORT 7563
#define CLIENT_PORT 8888
#define RECV_CHECK 6563
#define SEND_CHECK 7777
#define SERVICE_IP "192.168.1.54"
#define USER_NUMBER 10
#define PASS_NUMBER 10
struct UserInformation
{
		char userId[USER_NUMBER];           //用户
		char passwd[PASS_NUMBER];			//密码
		char vip;							//vip
		long balance;						//余额
};
union dataOrinformation
{
		char data[200];
		struct UserInformation loginInformation;
};



typedef struct Data
{
		int  mode;		//数据类型
		char destAddr[20]; 						//目的地址
		char sourceAddr[20];					//源地址
		char fileName[20];
		char time[30];
		struct timeval vtime;					//微妙毫秒
		union dataOrinformation dorinform;		//数据或者信息

		struct data *next;
		struct data *prev;


}sData_package,*pData_package;

enum
{
		LOGIN,          //登入
		REGISTER,       //注册
		ADDFRIEND,      //添加好友
		FILE_REQUES,    //文件请求
		TELL_REQUES,    //谈话请求
		REQUES_EXIT,    //请求结束
		LOGINERROR,     //登录失败
		LOGINSUCCEED,   //登录成功
		REGISTERERROR,  //注册失败
		REGISTERSUCCEED,//注册成功
		LEAVE,			//下线通知
		CHECK,			//检测
		FRIENDRE,		//好友回应
		FRIENDLIST,		//好友链表
		END			    //最后一个
};
typedef struct 
{
		int sockfd_send;                  //发送套接子
		int sockfd_recv;					//接受
		int send_check;						//发送检验
		int recv_check;						//接受校验
		struct sockaddr_in addr_send;		//发送地址
		struct sockaddr_in addr_recv;		//接送地址
		struct sockaddr_in addr_Schec;		//发送检验地址
		struct sockaddr_in addr_Rchec;		//接受检验地址
}Socks,*psock;
/*发送队列结构体*/
typedef struct data_chain
{
		sData_package data;				//等待处理数据
		pthread_t id;                    //线程id
		struct data_chain *next;		
		struct data_chain *prev;

} Thread_Data;

int login_menu();
int Send_fun(pData_package package,struct sockaddr_in *paddr,int sockfd);
sData_package Recv_fun(struct sockaddr_in *paddr,int rockfd);
/*初始化函数*/
int initSockfd_Serive(struct sockaddr_in *psaddr);
int initSockfd_Client(struct sockaddr_in *praddr);
int inintSend_Check(struct sockaddr_in *pcaddr);
int inintRecv_Check(struct sockaddr_in *pcaddr);
sData_package init_login(char*name,char *);
sData_package init_register(char*name,char*);
sData_package init_addfriend(char*name,char*);
sData_package init_file(char *buf_file,char*);
sData_package init_tell(char *buf_tell,char*);
//////////////////////////////////////////////

//void * create_send(void* pHead);
void * Send_choose(void *pHead);
Thread_Data * read_Data(Thread_Data *pHead);       //从链表中读取数据。
int Send_main(Socks Socks);
int SendToService(Socks Socks,sData_package data);			//发送到服务端
int Recv_main(Socks Socks);
void * Recv_choose(void* pHead);
int Recv_addfriend(sData_package package,Socks Socks);
int Recv_file(sData_package package,Socks Socks);
int Recv_tell(sData_package package,Socks Socks);
int Recv_list(sData_package package);
sData_package login_fun(int sockfd,struct sockaddr_in *psaddr,int rockfd);
sData_package register_fun(int sockfd,struct sockaddr_in *psaddr,int rockfd);
void myalarm(int sig);
Thread_Data * tell_addfriend(int mode,char* destAddr);
Thread_Data * tell_file(int mode,char* destAddr);
Thread_Data * tell_tell(int mode,char* destAddr);
int chain_insert(Thread_Data *pHead,Thread_Data *pInsert);
int chain_init(Thread_Data **p);
void create_list(Thread_Data *pTemp);
void list_show();


static sData_package (*Sendinit[5])(char *,char*) = {init_login,
												init_register,
												init_addfriend,
												init_file,
												init_tell};
																				
static jmp_buf jmpbuffer;
#endif
