#include "../include/apue.h"
void tcp_connect()
{
		int n=1;
	set_err(sockfd=socket(AF_INET,SOCK_STREAM,0),"socket");
	len=sizeof(struct sockaddr_in);
	selfaddr.sin_family=AF_INET;
	selfaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	selfaddr.sin_port=htons(PORT);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(n));
	set_err(bind(sockfd,(struct sockaddr*)&selfaddr,len),"bind");
	listen(sockfd,10);
	printf("tcp绑定完成\n");
}

void *con_in()
{
		pchain pnew;
		init_chain(&pnew);
		if(((pnew->confd)=accept(sockfd,(struct sockaddr*)&(pnew->conaddr),&len))==-1)
			{
					close(sockfd);
					show_err("accept");
			}
			pnew->conaddr.sin_family=AF_INET;//这俩局觉逼不能省，否则不能直接用
			pnew->conaddr.sin_port=htons(PORT);
			add_to_chain(pnew);
			event.data.fd=pnew->confd;
			epoll_ctl(epfd,EPOLL_CTL_ADD,pnew->confd,&event);//将该文件描述符放入监视程序

			//show_chain();
			printf("%s is connected\n",inet_ntoa(pnew->conaddr.sin_addr));
}
