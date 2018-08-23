#include "/apue.h"
#define NONE "\e[0m"
#define  RED "\e[31m"
#define  GREED "\e[32m"
#define SAN "\e[31m\033[05m"
#define YEL "\e[33m" 
#define WIT "\e[37m" 
#define PRO "\e[35m" 

#define DATA 1024
typedef struct info
{
		char user[DATA];
		char passwd[DATA];
		char addr[DATA];
		char cmd[DATA];
		char data[DATA];
		int mode;
}sData;


int my_strcmp(char *buf);
void my_wait(int sig);
void my_exit(int sig);
void my_jump(int sig);
int wait_connect(int sockfd,int*fdPipe);
int read_data(int sockfd,struct sockaddr_in caddr);
jmp_buf jmpbuffer;
int main()
{
		signal(SIGUSR1,my_exit);
		signal(SIGCHLD,my_wait);

		int sockfd = socket(AF_INET,SOCK_STREAM,0);
		if(sockfd == -1)
		{
				perror("socket");
				exit(0);
		}
		struct sockaddr_in saddr,caddr;
		bzero(&saddr,sizeof(saddr));
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = htonl(INADDR_ANY);
		saddr.sin_port = htons(7563);
		int ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
		if(ret == -1)
		{
				perror("bind");
				exit(-1);
		}
		listen(sockfd , 10);
		int fdPipe[2];
		ret = pipe(fdPipe);
		if(ret == -1)
		{
				perror("pipe");
				exit(-1);
		}
		int pid = fork();
		if(pid!=0)
		{
				//close(fdPipe[0]);
				usleep(1000*100);
				wait_connect(sockfd,fdPipe);

		}


		else
		{
				sData bufData;
				bzero(&bufData,sizeof(bufData));
				struct sockaddr_in raddr;

				close(fdPipe[1]);
				int ret;
				int roc;
				puts("child1");
				ret = read(fdPipe[0],&roc,sizeof(sockfd));

//				ret = read(fdPipe[0],&raddr,sizeof(raddr));
				printf("roc:%d\n",roc);
		//		ret = read(roc,&bufData,sizeof(bufData));
		//		printf("ret:%d\n",ret);
				read_data(roc,raddr);

		}

}
int read_data(int sockfd,struct sockaddr_in caddr)
{
		sData bufData;
		while(1)
		{
				bzero(&bufData,sizeof(bufData));
				int ret ;
				while( ( ret=read(sockfd,&bufData,sizeof(bufData)))  == 0 )
				{
						printf("0\n");
						sleep(1);
				}
				if(ret < 0)
				{
						printf("%d\n",ret);
						perror("read");
						close(sockfd);
						exit(-1);
				}
				printf("\n"RED"ip(%s) id(%d):->"WIT"%s"NONE"\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port),bufData.data);
				printf("user:%s passwd%s\n",bufData.user,bufData.passwd);
				if(my_strcmp(bufData.data) == 1)
				{
						printf(GREED"%s:go away"NONE"\n",inet_ntoa(caddr.sin_addr));
						close(sockfd);
						exit(0);
				}
		}

}
int wait_connect(int sockfd,int*fdPipe)
{
		struct sockaddr_in saddr,caddr;
		while(1)
		{
				bzero(&caddr,sizeof(caddr));
				int len = sizeof(caddr);
				int cocfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
				if(cocfd == -1)
				{
						perror("accept");
						exit(0);
				}
				getpeername(cocfd,(struct sockaddr*)&saddr,&len);
				printf("\n"GREED"ip(%s) 请求ftp"NONE"\n",inet_ntoa(saddr.sin_addr));

				if(fork() == 0)
				{
						close(fdPipe[0]);
						printf("cocfd%d\n",cocfd);
						write(fdPipe[1],&cocfd,sizeof(int));
			//			write(fdPipe[1],&caddr,sizeof(caddr));
			//			read_data(cocfd,caddr);
						sleep(10);
						exit(0);
				}
				
		}


}
int my_strcmp(char *buf)
{
		if(buf[0]=='b'  && buf[1]=='y')
				return 1;
		else
				return 0;

}
void my_wait(int sig)
{
		while(waitpid(-1,NULL,WNOHANG) >0)
				;
}
void my_exit(int sig)
{
		if(getpid() != getpgrp())
		{
				printf("%d\n",getpid());
				exit(0);
		}
}
void my_jump(int sig)
{
		if(sig == SIGPIPE)
		{
				printf("SICPIPE\n");
		}
		else
				printf("time over\n");
//		longjmp(jmpbuffer,1);

}
