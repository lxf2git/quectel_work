#include"apue.h"

typedef struct Data
{
	long type;
	char buf[200];
	char name[200];
}Data;
int main()
{	
	Data info;
	int fd; 
	key_t key=ftok("/root",'a');
	int id=msgget(key,O_RDONLY);
	long type;
	if(-1==msgrcv(id,&info,sizeof(info)-sizeof(info.type),2,0))
	{
		puts("No find!");
	}
	else
	{
		fd=open(info.name,O_RDWR);
		if(fd<0)
		{
			show_err("open_read");
		}	
		while(1)
		{
			memset(info.buf,0,sizeof(info.buf));
			if(read(fd,info.buf,sizeof(info.buf))==0)
			{
				break;
			}
			info.type=1;		
			msgsnd(id,&info,sizeof(info)-sizeof(info.type),0);
			usleep(1000);	
		}	
	}
	close(fd);
	msgctl(id,IPC_RMID,NULL);
}

