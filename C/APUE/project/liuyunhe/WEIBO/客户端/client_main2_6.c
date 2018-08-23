#include"apue.h"	
int sockfd;

int personal_information()//个人信息查询_ok_s
{
	char buf[1024];
	int button,num;
PERSON:
	bzero(buf,sizeof(buf));
	printf("/***查看个人信息：1***/\n/***返回上一级：2***/\n");
	scanf("%d",&button);
	switch(button)
	{
			case 1:
				num = 11;
				write(sockfd,&num,sizeof(num));
				read(sockfd,buf,sizeof(buf));
				printf("personal_information:\n%s\n",buf);
				goto PERSON;
				break;
			case 2:
				//write(sockfd,&button,sizeof(button));
				break;
			default:
				printf("请选择1/2\n");
				goto PERSON;
				break;
	}
	return 0;
}

int add_message()//发送微博-添加文本信息_ok_s
{
	char buf[1024];
	printf("请添加文本信息:\n");
	scanf("%s",buf);
	write(sockfd,buf,strlen(buf)+3);
	bzero(buf,sizeof(buf));
	read(sockfd,buf,sizeof(buf));
	printf("add_message:%s\n",buf);
	return 0;
}

int send_message()//发送微博_ok_S
{
	int button,num;
SEND:
	printf("/***发微博：1***/\n/***返回：2***/\n");
	scanf("%d",&button);
	switch(button)
	{
		case 1:
			num = 10;
			write(sockfd,&num,sizeof(num));
			add_message();
			break;
		case 2:
			//write(sockfd,&button,sizeof(button));
			break;
		default:
			printf("请正确选择\n");
			goto SEND;
	}
	return 0;	
}

void cancel_attenrion()/*此处由云鹤大师书写*/
{
		char buf[40];
		bzero(buf,sizeof(buf));
		read(sockfd,buf,sizeof(buf));
		printf("%s\n",buf);
		bzero(buf,sizeof(buf));
		scanf("%s",buf);
		write(sockfd,buf,strlen(buf)+1);
		printf("正在处理请稍等\n");
		sleep(1);
}

int list_show(int button)//名单显示_ok_s
{
	int choose,ret=1,num;
	char buf[1024];
	read(sockfd,buf,sizeof(buf));
	printf("list_show:%s\n",buf);
	if(3==button)
	{
		while(ret==1)
		{
			printf("/***取消关注：1***/\n/***返回上一级：2***/\n");
			scanf("%d",&choose);
			switch(choose)
			{
				case 1:/*云鹤*/
					num = 12;
					write(sockfd,&num,sizeof(num));
					bzero(buf,sizeof(buf));
					cancel_attenrion();
					//read(sockfd,buf,strlen(buf));
					printf("已取消\n");
					break;
				case 2:
					//write(sockfd,&choose,sizeof(choose));
					ret=0;
					break;
				default:
					printf("选择错误\n");
					break;
			}
			
		}
		
	}else
	{
		;	
	}
	return 0;
}

int list_show_fans()//粉丝名单显示
{
	int choose,ret=1;
	char buf[40];
	while(1)
	{
		bzero(buf,sizeof(buf));
		read(sockfd,buf,sizeof(buf));
		if(strcmp(buf,"*#*")==0)
		{
				break;
		}
		printf("%s\n",buf);
	}
	return 0;
}

int show_message_guanzhu()//关注显示微博     /*此处由云鹤大师书写*/
{
	int button;
	char ch[2]={'\0'};
	char buf[1024];
REPEAT:
	bzero(buf,sizeof(buf));
	read(sockfd,buf,sizeof(buf));
	if(strcmp(buf,"*#*")==0)
	{
			return 0;
	}
	printf("show_message:%s\n",buf);
SHOW:
	printf("/***评论：1***/\n/***不评论：2**/\n/***返回上一级：0***/\n");
	scanf("%d",&button);
	
	switch(button)
	{
		case 1:
				strcpy(ch,"1");
			write(sockfd,ch,sizeof(ch));
			comment();
			goto REPEAT;
			break;
		case 2:
				strcpy(ch,"2");
			write(sockfd,ch,sizeof(ch));
			goto REPEAT;
			break;
		case 0:
				strcpy(ch,"0");
			write(sockfd,ch,sizeof(ch));
				break;
		default:
			printf("请正确选择：1/2\n");
			goto SHOW;
			break;
	}
	return 0;	
}

int look()//查看_ok_s
{
	int button,num;
LOOK:
	printf("/***查看粉丝：1***/\n/***查看关注的微博：2***/\n/***查看关注列表：3***/\n/***返回上一级：40***/\n");
	scanf("%d",&button);
	switch(button)
	{
		case 1:
			num = 7;
			write(sockfd,&num,sizeof(num));
			list_show_fans();/*云鹤*/
			goto LOOK;	
			break;
		case 2:
			num = 9;
			write(sockfd,&num,sizeof(num));
			show_message_guanzhu();
			goto LOOK;	
			break;
		case 3:
			num = 8;
			write(sockfd,&num,sizeof(num));
			list_show(button);
			goto LOOK;	
			break;
		case 4:
		//	write(sockfd,&button,sizeof(button));
			break;
		default:
			printf("请选择，1/2/3/4 \n");
			goto LOOK;
			break;
	}
	return 0;	
}

int comment()//评论微博_ok_s
{
	int button;
	char buf[1024];
COMMENT:
	bzero(buf,sizeof(buf));
	printf("请输入评论，16个字以内，回车结束\n");
	scanf("%s",buf);
	printf("请确认是否修改：1、重新输入 2、保存并发送\n");
	scanf("%d",&button);
	if(1==button)
	{
		goto COMMENT;
	}else
		if(2==button)
		{
			write(sockfd,buf,strlen(buf)+3);
		}else
		{
			printf("请输入 1/2\n");
			goto COMMENT;
		}
	return 0;
}

#if 1
int show_message()//显示微博
{
	int button;
	char buf[1024];
SHOW:
	bzero(buf,sizeof(buf));
	read(sockfd,buf,sizeof(buf));
	printf("show_message:%s\n",buf);
ERROR:
	printf("/***评论：1***/\n/***下一条：2***/\n/***返回上一级：0***/\n");
	scanf("%d",&button);
	
	switch(button)
	{
		case 1:
		//	write(sockfd,&button,sizeof(button));
			comment();
			break;
		case 2:
		//	write(sockfd,&button,sizeof(button));
			goto SHOW;
			break;
		case 0:
			break;
		default:
			printf("请正确选择：1/2/0\n");
			goto ERROR;
			break;
	}
	return 0;	
}
#endif
int indication()//搜索信息显示
{
	int button,num;
	/*云鹤*/
	char buf[40];
	bzero(buf,sizeof(buf));
	read(sockfd,buf,sizeof(buf));
	printf("%s\n",buf);
	
	bzero(buf,sizeof(buf));
		scanf("%s",buf);
		write(sockfd,buf,strlen(buf)+1);
		while(1)
		{
				bzero(buf,sizeof(buf));
				read(sockfd,buf,sizeof(buf));
			//	printf("测试传入：%s\n",buf);
				if(strcmp(buf,"*#*")==0)
				{
						break;
				}
				printf("%s\n",buf);
			//	printf("_______\n");
		}

	//scanf("%s",buf);
	//getchar();
	//write(sockfd,buf,strlen(buf)+3);
	//memset(buf,0,sizeof(buf));
	//read(sockfd,buf,strlen(buf));
	//printf("indication:%s\n",buf);
	
INDICATION:	
	printf("/***关注：1***/\n/***查看：2***/\n/***返回上一级：0***/\n");
	scanf("%d",&button);
	switch(button)
	{
		case 1:
			num = 5;
			write(sockfd,&num,sizeof(num));
			//read(sockfd,&button,sizeof(button));
			printf("请关注的ID\n");
			bzero(buf,sizeof(buf));
			scanf("%s",buf);
			write(sockfd,buf,strlen(buf)+3);
			bzero(buf,sizeof(buf));
			read(sockfd,buf,sizeof(buf));
			printf("%s\n",buf);
			break;
		case 2:
			num = 6;
			write(sockfd,&num,sizeof(num));
			show_message();
			break;
		case 0:
			//write(sockfd,&button,sizeof(button));
			break;
		default:
			printf("请正确选择：1/2/3\n");
			goto INDICATION;
			break;
	}
	return 0;	
}

int search()//搜索接口
{
	int button,ret,num;
SEARCH:
	printf("/***1、ID搜索***/\n/***2、用户名搜索***/\n/***3、返回上一级***/\n");
	scanf("%d",&button);
	switch(button)
	{
		case 1:
			num = 3;
			write(sockfd,&num,sizeof(num));
			printf("请输入搜索ID\n");
			indication();
			goto SEARCH;
			break;
		case 2:
			num = 4;
			write(sockfd,&num,sizeof(num));
			printf("请输入搜索NAME\n");
			indication();
			goto SEARCH;
			break;
		case 3:
			//write(sockfd,&button,sizeof(button));
			ret = 1;
			break;
		default:
			printf("请输入选择‘1’‘2’‘3’\n");
			goto SEARCH;
			break;
	}
	return 0;	
}

int menu()//一级主菜单列表
{
	int button,ret;
MENU:
	printf("/***搜索：1***/\n/***查看：2***/\n/***发微博：3***/\n/***个人信息：4***/\n/***退出：0***/\n");
	scanf("%d",&button);
	switch(button)
	{
			case 1:
							search();//搜索接口
							goto MENU;
							break;
			case 2:
							look();//查看接口
							goto MENU;
							break;
			case 3:
							send_message();//发微博接口
							goto MENU;
							break;
			case 4:
							personal_information();//个人信息接口
							goto MENU;
							break;
			case 0:
							ret = logout();//退出选择接口
							if(ret==1)
							{
											goto MENU;	
							}else
							{
											//write(sockfd,&button,sizeof(button));
											return;
							}
							break;
			default:
							printf("选择失败，请重新选择：\n");
							goto MENU;
							break;
	}

	//write(sockfd,&button,sizeof(button));
	return 0;	
}

int login()//登录函数接口
{
		/*此处由嵌入式大师云鹤书写*/
	printf("登录\n");
	char ch[30];	
		while(1)
		{
				bzero(ch,sizeof(ch));
				read(sockfd,ch,sizeof(ch));
				if(strcmp(ch,"*p*")==0)
				{
						break;
				}
				printf("%s\n",ch);
				printf("（8位）\n");
				while(1)
				{
						bzero(ch,sizeof(ch));
						scanf("%s",ch);
						if(strcmp(ch,"*p*")==0)
						{
								printf("请重新输入\n");
								//break;
						}
						else
						{
								break;
						}
				}
				write(sockfd,ch,sizeof(ch));
		}
	printf("登录成功\n");

	menu();
	return 0;
}

int logon()//注册函数接口
{
		char ch[30];
		printf("注册\n");

		printf("欢迎你注册微博\n");
		while(1)
		{
				bzero(ch,sizeof(ch));
				read(sockfd,ch,sizeof(ch));
				if(strcmp(ch,"*#*")==0)
				{
						break;
				}
				printf("%s\n",ch);
				printf("（8位）\n");
				while(1)
				{
						bzero(ch,sizeof(ch));
						scanf("%s",ch);
						if(strcmp(ch,"*#*")!=0)
						{
								printf("*****\n");
								break;
						}
						else
						{
								printf("请重新输入\n");
						}
				}
				write(sockfd,ch,sizeof(ch));
		}
		printf("注册成功\n");

	return 0;
}

int logout()//退出选择确认
{
	int ret;
	char ch;
	printf("真的要离开了么？y/n\n");
LOGOUT:
	//getchar();
	scanf("%s",&ch);
	switch(ch)
	{
		case 'y':
						ret = 0;
						break;
		case 'n':
						ret = 1;
						break;
		default:
						printf("please input y or n!\n");
						goto LOGOUT;
						break;
	}
	return ret;
}

int login_state()//登录
{
	int choose;

	while(1)
	{
	printf("/***注册：1***/\n/***登录：2***/\n/***退出：0***/\n选择：");
	scanf("%d",&choose);
	getchar();
	if(choose==2)//登录
	{
		printf("choose:%d\n",choose);
		write(sockfd,&choose,sizeof(choose));
		login();
	}else
			if(choose==1)//注册
			{
				write(sockfd,&choose,sizeof(choose));
				logon();
			}else
					if(choose==0)//退出？
					{
						int ret = logout();
						if(ret==1)
						{
							;	
						}else
						{
							write(sockfd,&choose,sizeof(choose));
							return;
						}
					}else
					{
						printf("please input '0'/'1'/'2'\n");
					}
	}
	return 0;
}

int main(int argc,char *argv[])	
{
	if(argc!=2)
	{
		printf("please input ip_service:\n");
		return 0;
	}

	char buf[1024];
	memset(buf,0,sizeof(buf));
	struct sockaddr_in seraddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		show_err("socket");
	}
	
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(6666);
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
#if 1
	if(connect(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0)
	{
		close(sockfd);
		show_err("connect");
	}
//	strcpy(buf,"加载成功！\n");
//	write(sockfd,buf,strlen(buf)+3);
//	read(sockfd,buf,strlen(buf));
//	printf("%s\n",buf);
#endif
	login_state();

	return 0;	
}




