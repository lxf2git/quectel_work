#include"./apue.h"
int main()
{
		int ret;
		int fd;
		int fd_pid;
		pid_t pid;
		char buf[20];
		memset(buf,0,sizeof(buf));
		fd_pid=open("file1",O_RDWR|O_EXCL|O_CREAT);
		if(fd_pid<0)
		{
				perror("open_pid");
		}	
		fd = open("file",O_RDWR);	
		if(fd<0)
		{
				perror("open");
		}		
		pid = fork();
		if(pid==0) //第一个子进程
		{		
				pid =getpid();
				read(fd,buf,1);
				if(write(fd_pid,&pid,sizeof(pid_t))<0)
				{
					perror("write");
					exit(-1);
				}	
				close(fd_pid);			
				close(fd);
				while(1)
				{
						write(1,buf,1);
						sleep(1);
				}
		}
		else
		{
				pid=fork();
				if(pid==0)//第二个进程
				{		sleep(1);
						pid =getpid();
						read(fd,buf,1);
						if(write(fd_pid,&pid,sizeof(pid_t))<0)
						{
							perror("write");
							exit(-1);
						}	
						close(fd_pid);	
						printf("pid:%d\n",getpid());
						close(fd);
						while(1)
						{
								write(1,buf,1);
								sleep(1);
						}
				}
				else
				{
						pid=fork();
						if(pid==0)//第三个进程
						{
								sleep(2);
								pid =getpid();
								read(fd,buf,1);
								if(write(fd_pid,&pid,sizeof(pid_t))<0)
								{
									perror("write");
									exit(-1);
								}	
								close(fd_pid);	
								printf("pid:%d\n",getpid());
								close(fd);
								while(1)
								{
										write(1,buf,1);
										sleep(1);
								}
						}
				}

		}		
				close(fd_pid);
				close(fd);
				system("gcc ./homework_1.c");
				return 0;

#if 0
		/*****父进程收尸****/
		while(1)
		{
				pid = wait(&sta);
				if (pid == -1)
				{
						break;
				}
				printf("child->pid:%d, status:%d %d %d %d \n",
								pid, WIFEXITED(sta),
								WEXITSTATUS(sta), WIFSIGNALED(sta),WTERMSIG(sta));
		}
#endif 		
}
