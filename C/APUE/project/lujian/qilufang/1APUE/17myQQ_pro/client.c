#include"apue.h"
//exe 192.168.1.200
void my_exit(pid_t pid,int sockfd)
{
	char com[50];
	bzero(com,sizeof(com));
	sprintf(com,"kill -9 %d",pid-1);
	system(com);

	write(sockfd,"goodbye",8);
	close(sockfd);	

	puts("欢迎下次使用！");
	exit(0);

}
int main(int argc,char **argv)
{
	if(argc!=2)
	{
		puts("Input_err!");
		exit(-1);
	}
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		show_err("socket_err");
	}

	struct sockaddr_in seraddr;
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(8888);
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
	if(connect(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr))<0)
	{
		show_err("connect_err!");
	}

	char buf[50];
	if(fork()==0)
	{
		while(1)
		{
			bzero(buf,sizeof(buf));
			printf("Input a str:\n");
			scanf("%[^\n]",buf);
			getchar();
			write(sockfd,buf,strlen(buf)+1);
		}
		exit(0);
		close(sockfd);	
	}
	else
	{
		for(;;)
		{
			bzero(buf,sizeof(buf));
			if(read(sockfd,buf,sizeof(buf))<0)
			{
				break;
			}
			if(strcmp(buf,"goodbye")==0)
			{
				my_exit(getpid(),sockfd);
			}
			strcat(buf,"  --server");
			puts(buf);
		}
	}
	return 0;

}
