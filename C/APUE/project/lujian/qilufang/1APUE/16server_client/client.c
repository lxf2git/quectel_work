#include"apue.h"
//a.out 192.168.1.200
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

	bzero(buf,sizeof(buf));
	printf("Input a str:\n");
	scanf("%s",buf);
	write(sockfd,buf,strlen(buf)+1);


	bzero(buf,sizeof(buf));
	if(read(sockfd,buf,sizeof(buf))<0)
	{
			show_err("read_client");
	}
	puts(buf);
	close(sockfd);
	return 0;

}
