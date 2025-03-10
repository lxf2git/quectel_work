#include"apue.h"
#define SIGEXIT SIGUSR1
void myexit(int sig)
{
	exit(0);
}
int main()
{
  	printf("pid_send:%d\n",getpid());
	char file_name[1024];
	char buf_data[1024];

	signal(SIGEXIT,myexit);//收到信号SIGUSR1时退出
	while(1)
	{
		printf("Input file name:\n");
	   	memset(file_name,0,sizeof(file_name));
	   	scanf("%s",file_name);
		//传送文件名
		int fd_openPipe=open("pipe",O_WRONLY);
		if(fd_openPipe<0)
		{
			show_err("open_pipe_send!");
		}
	    	if(write(fd_openPipe,file_name,sizeof(file_name))<0)
	     	{
			show_err("write_pipe");
	      	}
		close(fd_openPipe);

		usleep(1000);
		int fd_filePipe=open("pipe_data",O_RDONLY);
		if(fd_filePipe<0)
		{
			show_err("open_filePipe");
		}

		while(1)
		{
			//读取文件内容
			memset(buf_data,0,sizeof(buf_data));
			if(read(fd_filePipe,buf_data,sizeof(buf_data))==0)
			{
				break;
			}
			puts(buf_data);
		}
		close(fd_filePipe);
		unlink("pipe_data");
	}
	return 0;

}
