#include"../../apue.h"
int main()
{
	printf("%d\n",getpid());	
	int n;	
	struct sockaddr_in conaddr;
	socklen_t len = sizeof(struct sockaddr_in);
	char buf[30];
	bzero(buf,sizeof(buf));	
	struct sockaddr_in selfaddr;
	char buf1[30];
	
	int ret;
	bzero(buf1,sizeof(buf));	
	
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		show_err("socket");
	}
bzero(&selfaddr,sizeof(selfaddr));
	selfaddr.sin_family = AF_INET;
	selfaddr.sin_port = htons(5678);
	selfaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sockfd,(struct sockaddr*)&selfaddr,sizeof(selfaddr));
	if(ret<0)
	{
		close(sockfd);
		show_err("bind");
	}
	

	n = recvfrom(sockfd,buf1,sizeof(buf1),0,(struct sockaddr*)&conaddr,&len);
    printf("ip:%s connet! data:%s \n",inet_ntoa(conaddr.sin_addr),buf1);
	
bzero(&conaddr,sizeof(conaddr));
	conaddr.sin_family = AF_INET;
	conaddr.sin_port = htons(5678);
	conaddr.sin_addr.s_addr  = inet_addr("192.168.1.200");

	sprintf(buf,"%d say hi friend!\n",getpid());
	n = sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&conaddr,len);
	if(n<0)
	{
		close(sockfd);
		show_err("sendto");
	}
	
	sleep(10);

	
	return 0;

}
