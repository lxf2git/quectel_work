#include"../apue.h"
for(;;)
{
	confd = accept()
}
if(fork()==0)
{
	
	deal;
}
//
int main()
{
	int fd[2];	
	pid_t pid;
	struct sockaddr_in saddr,caddr;
	char buf[1024]={'\0'};
	int sfd;
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
		if(sockfd == -1)
		{
				perror("socket");
				exit(0);
		}
		
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

		bzero(&caddr,sizeof(caddr));
		
				int len = sizeof(caddr);
				int cocfd = accept(sockfd,(struct sockaddr*)&caddr,&len);
				if(cocfd == -1)
				{
						perror("accept");
						exit(0);
				}
			

	pipe(fd);
	
	pid = fork();
	if(pid<0)
	{
		show_err("fork");
	}	
	if(pid==0)//读 关闭写端
	{
		sleep(5);	
		close(fd[1]);
		int n;
		int ret = read(fd[0],&sfd,4);
		
		
		ret = read(sfd,buf,sizeof(buf));
		if(ret<=0)
		{
			perror("read");
		}
		printf("read-sfd:%d\n",sfd);
		printf("read-data:%s\n",buf);		

			
	}
	else//par
	{
			
				
		if(fork()==0)
		{
			close(fd[0]);//写 关闭读端
			write(fd[1],&cocfd,sizeof(int));
		}
		else
		{	
		wait(NULL);
		}
	}
	return 0;

}
