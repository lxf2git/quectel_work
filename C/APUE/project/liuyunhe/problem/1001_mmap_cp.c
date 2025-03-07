#include"../apue.h"	

int main(int argc,char *argv[])	
{
	if(argc!=2)
	{
		printf("%s filename to copy!\n",argv[0]);
		exit(-1);
	}
	char *p = NULL;
	int fd = open(argv[1],O_RDWR);
	if(fd<0)
	{
		perror("open");
		exit(-1);
	}

	ftruncate(fd,1024);

	p = (char *)mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	if(p==MAP_FAILED)
	{
		perror("mmap");
	}

	int n;
	for(;;)
	{
		n = read(fd,p,1024);
		if(n<=0)
		{
			break;
		}
	}
	
	munmap(p,1024);

	close(fd);
	return 0;	
}
