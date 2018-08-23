#include"apue.h"

int rdwr_op(int rdwr)
{
	int n,num,i;
	int j=0;
	int fd;
	char buf[1024];
	char file_name[1024];
	char name[1024];
	char dir[1024];
	bzero(buf,sizeof(buf));
	bzero(file_name,sizeof(file_name));
	bzero(name,sizeof(name));
	bzero(dir,sizeof(dir));

//	n=read(0,buf,sizeof(buf));
	scanf("%[^\n]",buf);
	getchar();
	write(rdwr,buf,strlen(buf)+1);
//	printf("buf:%s\n",buf);
	if(strncmp(buf,"get",3)==0)
	{
		printf("****************\n");
		strcpy(file_name,buf);
		num = strlen(file_name);

		for(i=num;i>=0;i--)
		{
			if(file_name[i-1]==' ')
			{
				break;
			}
		}
		strcpy(name,file_name+i);
		fd = open(name,O_CREAT|O_RDWR,0666);

		
		read(rdwr,buf,sizeof(buf));
		printf("get:%s\n",buf);
		if(buf[0]=='0')
		{
			printf("文件不存在\n");
			return 0;
		}
		if(buf[0]=='1')
		{
			while(1)
			{	
				read(rdwr,buf,sizeof(buf));
				printf("get:%s\n",buf);
				if(strcmp(buf,"#*#")==0)
				{
						break;
				}
				write(fd,buf,sizeof(buf));
			}
			close(fd);
			printf("文件传送成功\n");
			return 0;

		}
	}
	if(strncmp(buf,"put",3)==0)
	{
		printf("****************\n");
		strcpy(file_name,buf);
		num = strlen(file_name);
		printf("num:%d\n",num);
		for(i=0;i!=num;i++)
		{
			if(file_name[i]==' ')
			{
				i++;
				break;
			}
		}
		while(file_name[i]!=' ')
		{
			name[j]=file_name[i];
			i++;j++;
		}
		printf("name:%s",name);
		fd = open(name,O_RDWR);
		int ret;
				bzero(buf,sizeof(buf));
				ret = read(fd,buf,1020);
				printf("buf:%s\n",buf);
						write(rdwr,buf,strlen(buf)+1);
		close(fd);

	}
	if(strcmp(buf,"quit")==0)
	{
			return -1;
	}
	read(rdwr,buf,sizeof(buf));
	printf("my=%s\n",buf);
	return 0;
	
}


int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("没有输入ip\n");
		exit(-1);
	}

	struct sockaddr_in seraddr;
	int m,ret;

	
	socklen_t len = sizeof(seraddr);
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		show_err("socket");
	}
	
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(8888);
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);
	m = connect(sockfd,(struct sockaddr*)&seraddr,len);
	if(m<0)
	{
		close(sockfd);
		show_err("connect");
	}
	printf("请输入用户名\n");
	while(1)
	{
		ret = rdwr_op(sockfd);
		if(ret<0)
		{
			break;
		}
	}


	
	return 0;
}
