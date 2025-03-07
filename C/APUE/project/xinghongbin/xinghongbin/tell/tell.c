#include "apue.h"
#define NONE "\e[0m"
#define  RED "\e[31m"
#define  GREED "\e[32m"
#define SAN "\e[31m\033[05m"
#define YEL "\e[33m" 
#define WIT "\e[37m" 
#define PRO "\e[35m" 


int my_strcmp(char *buf);
void my_wait(int sig);
void my_exit(int sig);
void my_jump(int sig);
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
		saddr.sin_port = htons(8889);
		int ret = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
		listen(sockfd , 10);

		if(ret == -1)
		{
				perror("bind");
				exit(-1);
		}
		if(fork() !=0)
		{
						read_data(sockfd);
						usleep(1000*100);

		}
		else
				while(1)
				{
						{
								signal(SIGUSR1,SIG_IGN);
								setjmp(jmpbuffer);
								int id;
								int cockfd = socket(AF_INET,SOCK_STREAM,0);
								char buf_ip[1024];
								bzero(buf_ip,sizeof(buf_ip));
								usleep(1000*100);
								printf("\n"RED"intput buf_ip id"NONE"\n");
								scanf("%s%d",buf_ip,&id);
								if(buf_ip[0] != '1')
								{
										kill(0,SIGUSR1);
										sleep(1);
										kill(getppid(),SIGKILL);
										exit(0);
										
								}
								send_data(cockfd,buf_ip,id);
						}
				}

}

int read_data(int sockfd)
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
				printf("\n"GREED"ip(%s) 进入对话"NONE"\n",inet_ntoa(saddr.sin_addr));
				if(fork() == 0)
				{
						char buf_wel[1024];
						char buf[1024];
						bzero(buf_wel,sizeof(buf_wel));
						char buf_data[1024];
						while(1)
						{
								bzero(buf_data,sizeof(buf_data));
								int ret ;
								while( ( ret=read(cocfd,buf_data,sizeof(buf_data)))  == 0 );
								if(ret < 0)
								{
										printf("%d\n",ret);
										perror("read");
										close(cocfd);
										exit(-1);
								}
								printf("\n"RED"ip(%s) id(%d):->"WIT"%s"NONE"\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port),buf_data);
								if(my_strcmp(buf_data) == 1)
								{
										printf(GREED"%s:go away"NONE"\n",inet_ntoa(caddr.sin_addr));
										close(cocfd);
										exit(0);
								}
						}
				}
		}


}
int send_data(int sockfd,char* buf_ip,int id)
{
		signal(SIGALRM,my_jump);
		struct sockaddr_in caddr;
		bzero(&caddr,sizeof(caddr));
		caddr.sin_family = AF_INET;
		caddr.sin_port = htons(id);
		caddr.sin_addr.s_addr = inet_addr(buf_ip);
		if(connect(sockfd,(struct sockaddr*)&caddr,sizeof(caddr)) < 0)
		{
				perror("conect");
				return -1;
		}
		char buf_data[1024];
		char buf_dataR[1024];
		char buf[1024];
		while(1)
		{
				usleep(1000*100);
				bzero(buf_data,sizeof(buf_data));
				printf(WIT"data:"NONE);
				fflush(NULL);
				read(0,buf_data,sizeof(buf_data));
				alarm(60);

				int ret = write(sockfd,buf_data,sizeof(buf_data));
				if(ret == -1)
				{
						perror("write");
						break;
				}
				if(my_strcmp(buf_data) == 1)
				{
						printf("close...\n");
						close(sockfd);
						return 0;	
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
		longjmp(jmpbuffer,1);

}
