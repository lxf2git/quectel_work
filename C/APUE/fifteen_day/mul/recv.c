#include"../apue.h"
int main()
{
	struct ip_mreq mreq;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	char buf[50];	
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		show_err("socket");
	}	


	mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.8");
	mreq.imr_interface.s_addr = inet_addr("192.168.1.200");
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(struct ip_mreq));

	bzero(&addr,sizeof(addr));
	addr.sin_family =  AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = htons(INADDR_ANY);//0 
	bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

	bzero(buf,sizeof(buf));
	recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&addr,&len);
	printf("len:%d\n",strlen(buf));	
	printf("%s recv %s\n",inet_ntoa(addr.sin_addr),buf);
	return 0;

}
