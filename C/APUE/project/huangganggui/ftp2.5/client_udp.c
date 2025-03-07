
#include "../apue.h"
#include <errno.h>
#define SERPORT 7563
#define CLIENT 8888
#define DATA 200
#define SUCCEED 1
#define FAIL 0


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

int send_data(int sockfd,struct sockaddr_in saddr,int mode,char*buf_ip);
int read_data(int sockfd,struct sockaddr_in saddr,int mode);
int read_passwd(int sockfd);
int put_init(int sockfd,struct sockaddr_in saddr,char*buf_ip);
int my_strcmp(char *cmd);
int deal_client(int sockfd);


int main(int argc, char **argv)
{
		sData buf_data;
		printf("size:%d\n",sizeof(buf_data));

		int sockfd = socket(AF_INET,SOCK_DGRAM,0);
		if(sockfd == -1)
		{
				perror("socket");
				exit(-1);
		}
		int rsockfd = socket(AF_INET,SOCK_STREAM,0);
		if(rsockfd == -1)
		{
				perror("rsocket c");
				exit(-1);
		}
		
		struct sockaddr_in saddr,raddr,caddr;
		bzero(&saddr,sizeof(saddr));
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(SERPORT);
		saddr.sin_addr.s_addr = inet_addr(argv[1]);

		bzero(&raddr,sizeof(raddr));
		raddr.sin_family = AF_INET;
		raddr.sin_port = htons(CLIENT);
		raddr.sin_addr.s_addr = htonl(INADDR_ANY);
		int ret;
		int len = sizeof(raddr);

		int i,readfd;
		for(i=0;i<3;i++)
		{

				send_data(sockfd,saddr,0,argv[1]);
				if(i==0)
				{
						int on = 1;
						setsockopt(rsockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int));
						if(ret == -1)
						{
								perror("setsockopt");
								return -1;
						}

						ret = bind(rsockfd,(struct sockaddr *)&raddr,len);
						if(ret == -1)
						{
								perror("bind");
								exit(-1);
						}
						listen(rsockfd,10);
				}
				readfd = accept(rsockfd,(struct sockaddr *)&caddr,&len);
				if(readfd == -1)
				{
						perror("accept");
						exit(-1);
				}



				ret = read_data(readfd,raddr,0);
				if(ret == SUCCEED)
				{
						break;
				}
		}
		if(i != 3)
		{
				while(1)
				{
						send_data(sockfd,saddr,1,argv[1]);
						deal_client(readfd);
				}
		}
		else
		{
				printf("close\n");
		}




}

int send_data(int sockfd,struct sockaddr_in saddr,int mode,char *buf_ip)
{
		struct sockaddr_in raddr;
		int len = sizeof(saddr);

		sData buf_data;
		if(mode == 0)
		{

				put_init(sockfd,saddr,buf_ip);	
				bzero(&buf_data,sizeof(buf_data));
				buf_data.mode = 0;
				read(0,buf_data.uoc.user,DATA);
				buf_data.uoc.user[strlen(buf_data.uoc.user)-1] = '\0';
				sprintf(buf_data.pod.passwd,"%s",getpass("passwd:"));
				sendto(sockfd,&buf_data,sizeof(buf_data),0,(struct sockaddr*)&saddr,len);
		}
		else
		{
				bzero(&buf_data,sizeof(buf_data));
				buf_data.mode = 1;
				printf("\nftp>");
				fflush(NULL);
				read(0,&buf_data.uoc.cmd,DATA);
				buf_data.uoc.user[strlen(buf_data.uoc.cmd)-1] = '\0';
				sendto(sockfd,&buf_data,sizeof(buf_data),0,(struct sockaddr*)&saddr,len);

		}




}
int read_data(int sockfd,struct sockaddr_in saddr,int mode)
{
		sData buf_data;
		if(mode == 0)
		{
				struct sockaddr_in raddr;
				int ret = read_passwd(sockfd);
				if(ret == 1)
						return SUCCEED;
				else
						return FAIL;
		}
		else
		{
				bzero(&buf_data,sizeof(buf_data));
				int ret =read(sockfd,&buf_data,sizeof(buf_data));
				if(ret == -1)
				{
						perror("read_data");
						exit(-1);
				}
				printf("%s\n",buf_data.pod.data);

		}




}
int read_passwd(int sockfd)
{
		int ret;
		sData buf_data;
		bzero(&buf_data,sizeof(buf_data));
		usleep(1000*500);

		ret = read(sockfd,&buf_data,sizeof(buf_data));
		if(ret == -1)
		{
				perror("read read_cmd");
				exit(-1);
		}
		if(my_strcmp(buf_data.uoc.cmd) == 1)
		{
				printf("go in succeed\n");
				return SUCCEED;
		}
		if(buf_data.uoc.cmd[0] == 'f')
		{
				
				printf("passw error\n");
				close(sockfd);
				return FAIL;
		}
		if(buf_data.uoc.cmd[0] == 'd')
		{
				printf("user 已经登录\n");
				close(sockfd);
				return FAIL;
		}



}
int put_init(int sockfd,struct sockaddr_in saddr,char*buf_ip)
{
		struct sockaddr_in raddr;
		int len = sizeof(raddr);
		char hostName[DATA];
		char serviceName[DATA];
		bzero(&raddr,sizeof(raddr));
		getpeername(sockfd,(struct sockaddr *)&raddr,&len);
		printf("Connected to %s (%s).\n",buf_ip,buf_ip );//服务器名字（地址）
		printf("happy everyday\n");
		printf("Name  (%s:%s):",buf_ip,getpwuid(getuid())->pw_name);//主机名 当强用户
		fflush(NULL);

}
int my_strcmp(char *cmd)
{
		if(cmd[0]=='s')
				return 1;
		else
				return 0;
}
int deal_client(int sockfd)
{
		char buf[DATA];
		char buff[DATA];
		int i = 0;
		int m;
		int fd;
		char ch;
		int ret;
		bzero(buf,sizeof(buf));
		read(sockfd,buf,1);
		if(buf[0] == '$')
				exit(0);
		if(buf[0] == 'p'){
				bzero(buf,sizeof(buf));
				read(sockfd,buf,sizeof(buf));
				fd = open(buf,O_RDWR);
				if(fd < 0){
						perror("open");
						return -1;
				}
				while(1){
						bzero(buf,sizeof(buf));
						ret = read(fd,buf,1);
						if(ret <= 0){
								write(sockfd,"^",1);
								break;
						}
						else
								write(sockfd,buf,1);
				}
				return 0;
		}

		if(buf[0] == '~'){
				//puts("get");
				read(sockfd,buf,sizeof(buf));
				printf("buf:%d,%s\n",strlen(buf),buf);
				strcpy(buff,buf);
				printf("buff:%s\n",buff);
				fd = open(buff,O_RDWR|O_CREAT|O_EXCL,0600);
				if(fd < 0){
						if(errno == EEXIST){
								printf("文件以存在,是否覆盖？(y/n)\n");
								scanf("%c",&ch);
								if(ch == 'y'){
										fd = open(buff,O_RDWR);
										if(fd < 0){
												perror("open");
												exit(-1);
										}
								}
								if(ch == 'n'){
										printf("取消下载\n");
										return -1;
								}
						}else{
								perror("open");
								exit(-1);
						}
				}
				while(1){
						bzero(buf,sizeof(buf));
						int ret = read(sockfd,buf,1);
						if(buf[strlen(buf)-1] == '^'){
								break;
						}
						else
								write(fd,buf,ret);
				}
		}
		else 
				if(buf[0] == 'c' || buf[0] == 'm')
				{
						//puts("cd or mkdir");
						//read(sockfd,buf,sizeof(buf));
				}

				else{
								//puts("ls");
						while(1){
								printf("%s",buf);
								bzero(buf,sizeof(buf));
								ret = read(sockfd,buf,1);
								if(buf[0] == '^')
										break;
						}
		}
}		
