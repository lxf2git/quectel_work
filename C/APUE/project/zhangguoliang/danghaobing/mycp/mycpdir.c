#include "apue.h"
//不显示路径的文件扫描器

void dir_fun(DIR*,char *);
void judge_copy_file(char **,char **,char **);

int main(int argc,char **argv)
{
	if( (argc!=4) && (argc!=3) )
	{
			printf("%s option file_name file_name\n",argv[0]);
			return -1;
	}
	char *copy_from;
	char *copy_to;
	char now[100];


	judge_copy_file(&copy_from,&copy_to,argv);//判断如果是目录复制则继续，否则执行文件复制
	mkdir(copy_to,0777);//没加容错
	
	
	DIR *pdir = opendir(copy_from);
	if(pdir==NULL)
	{
			perror("opendir");
			return -1;
	}

	//求出目标目录的路径
	strcpy(now,getcwd(now,sizeof(now)));
	chdir(copy_to);
	strcpy(copy_to,getcwd(copy_to,255));
	chdir(now);


	chdir(copy_from);
	dir_fun(pdir,copy_to);
	return 0;
}

void judge_copy_file(char **copy_from,char **copy_to,char **argv)
{
		struct stat Stat;
	if(strcmp(argv[1],"-r")==0)
	{
		*copy_from=argv[2];
		*copy_to=argv[3];
	}
	else
	{
		*copy_from=argv[1];
		*copy_to=argv[2];
		lstat(*copy_from,&Stat);
		if(S_ISDIR(Stat.st_mode))
				return ;
		copy_file(*copy_from,*copy_to);
		exit (0);
	}
	
}

void dir_fun(DIR *pdir,char *copy_to)
{
	struct dirent *pdirent;
	struct stat Stat;
	char there[256];
	strcpy(there,copy_to);
//	printf("lj:%s\n",there);
	while((pdirent=readdir(pdir))!=NULL)
	{
			if(pdirent->d_name[0]!='.')
			{
					lstat(pdirent->d_name,&Stat);
					strcpy(copy_to,there);
					strcat(copy_to,"/");
					strcat(copy_to,pdirent->d_name);
					if(S_ISDIR(Stat.st_mode))
					{
							mkdir(copy_to,0777);
							DIR *tdir = opendir(pdirent->d_name);
							chdir(pdirent->d_name);
							dir_fun(tdir,copy_to);
							chdir("../");
							strcpy(copy_to,there);
					}
					else
					{
							copy_file(pdirent->d_name,copy_to);
							printf("%s copy sucess!\n",pdirent->d_name);
					}
			}
	}
}
