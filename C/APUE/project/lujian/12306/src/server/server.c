#include "P12306.h"
#include "Thread_pool.h"

#define   MAX_THRD_NUM   (10) // 最大线程数


Pqueue  pool;

static void sig_deal(int signo);
static struct ser_deal_pakg* pakg_init(int sockfd, struct cli_ser_pakg lv_cli_ser_pakg, 
				struct sockaddr_in conaddr);
void * myprocess(void* ppakg);
DB db_12306;
int main() 
{
	db_open();
	//udp绑定
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
	}
	int one = 1;
	struct sockaddr_in seraddr, conaddr;
	memset(&seraddr, 0, sizeof(seraddr));
	memset(&conaddr, 0, sizeof(conaddr));

	socklen_t len = sizeof(seraddr);
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port   = htons(6666);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);


	if (bind(sockfd, (struct sockaddr*)&seraddr, len) < 0)
	{
		perror("bind");
		goto Err;
	}
	
	//非正常退出信号处理
	sigset_t newset;
	sigfillset(&newset);
	sigdelset(&newset, SIGINT);
	sigdelset(&newset, SIGABRT);
	sigprocmask(SIG_BLOCK, &newset, NULL);

	signal(SIGINT, sig_deal);
	signal(SIGQUIT, sig_deal);

	//创建线程池
	pool_init(MAX_THRD_NUM);
	
	int re;
	struct cli_ser_pakg lv_cli_ser_pakg;	

	bzero(&lv_cli_ser_pakg, sizeof(struct cli_ser_pakg));

	struct ser_deal_pakg* pdeal =NULL;

	while(1)
	{
		re = recvfrom(sockfd, &lv_cli_ser_pakg, sizeof(struct cli_ser_pakg), 0, (struct sockaddr* )&conaddr, &len);
		if (re < 0)
		{
			perror("recvfrom");
			goto Err;
		}
	printf(	"flag:%d\n", lv_cli_ser_pakg.flag);
	printf("buf:%s \n",     lv_cli_ser_pakg.req.que_buf);
	printf("username:%s\n, passwd%s\n", lv_cli_ser_pakg.user.username,  lv_cli_ser_pakg.user.userpasswd);
	printf("sockfd: %d\n", sockfd);
	printf("ip :%s\n", inet_ntoa(conaddr.sin_addr));

		//封装处理数据包

		pdeal =  pakg_init(sockfd, lv_cli_ser_pakg, conaddr);

		assert(pdeal !=NULL);

		//添加任务到队列
		pool_add_worker(myprocess, (void*)pdeal);

		memset(&conaddr, 0, sizeof(conaddr));
		memset(&lv_cli_ser_pakg, 0, sizeof(struct cli_ser_pakg));
	}

	close(sockfd);
	return TRUE; 
Err:
	close(sockfd);
	return FALSE;  
}

struct ser_deal_pakg* pakg_init(int sockfd, struct cli_ser_pakg lv_cli_ser_pakg, 
				struct sockaddr_in conaddr)
{
		struct ser_deal_pakg* pdeal;
		creat_memory((void**)&pdeal, sizeof(*pdeal));
		pdeal->recv_pakg = lv_cli_ser_pakg;
		pdeal->cli_ip = conaddr;
		pdeal->sockfd = sockfd;
		
		return pdeal; 
}	

void sig_deal(int signo)
{
		switch(signo)
		{
				case SIGINT: printf("[%s = %d line] \n", __FUNCTION__, __LINE__ ); 
				case SIGABRT:printf("[%s = %d line] \n", __FUNCTION__, __LINE__ );  
							 pool_destroy();
							  break;
				default :
							  break;
		}
		exit(-1);

}
