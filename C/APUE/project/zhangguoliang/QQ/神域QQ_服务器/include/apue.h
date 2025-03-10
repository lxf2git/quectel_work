#ifndef _APUE_H_
#define _APUE_H_
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <assert.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "struct.h"
#include "ser_glo.h"//服务器专用
#define EMPTY 0
#define MAX_SIZE 2048
#define TRUE 1
#define FLASE 0
#define PORT 8888
#define MAX_THREAD 5
#define MAX_MONT 100
#define RET_ERR "2"
#define RET_SUC "1"
#define FIL_PER 0666
#define MIN_QQ 10000
#define DATA_FILE "qqdata"
#define GET_QQ "qqnode"

enum{QUIT_CON,APPLY,LOGIN,CHQQ,FDPWD,
		CHINFO,SHOWF,ADDFD,DELFD,FTALK,SHOWFT,
		SENDFILE,LXSENDF,LXSENDM};//客户端给服务器
enum{Q_TALK,NEWF,S_TALK,SENDF,N_TALK,M_TALK,AEXIT,OKFD,KOFD,NKOFD,
		RFILE,NFILE,YFILE,READF,SCFILE,XZFILE,SCTALK,XZTALK};//服务器给客户端发送的标签
enum{SHUTDOWN,SHOW1,SHOW2,SHOW12,SHUTQQ,SHUTCON,SETVIP};//服务器功能
//S_TALK:让客户选择是否通讯
//N_TALK:客户拒绝通讯
//M_TALK:客户同意通讯
#endif
