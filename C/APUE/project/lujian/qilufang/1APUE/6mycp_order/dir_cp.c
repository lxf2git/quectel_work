#include"main.h"
int dir_cp(char *path_start,char *path_end)
{	//printf("Start_dir:%s\n",path_start);
	//printf("Start_dir:%s\n",path_end);
	char add_end[M];
	memset(add_end,0,sizeof(add_end));
	DIR * op_dir=NULL;
	struct stat s;
	struct dirent * re_dir=NULL;
	int ret=0; 
	char dir_add[M];
	memset(dir_add,0,sizeof(dir_add));
	char file_add[M];
	memset(file_add,0,sizeof(file_add));
	if(mkdir(path_end,0777)<0)
	{
		perror("mkdir1");
		exit(-1);
	}
	op_dir=opendir(path_start);
	if(NULL==op_dir)
	{
		perror("opendir");
		exit(-1);
	}
	if(chdir(path_start)<0)
	{
		perror("chdir");
		exit(-1);
	}
	while(1)
	{
		re_dir=readdir(op_dir);
		if(re_dir==NULL)
		{
			break;
		}
		if(re_dir->d_name[0]=='.')
		{
			continue;
		}
		ret=lstat(re_dir->d_name,&s);
		if(ret<0)
		{
			perror("lstat");
			return FAIL;
		}
		if(S_ISDIR(s.st_mode))
		{
			chdir(re_dir->d_name);

			memset(dir_add,0,sizeof(dir_add));
			getcwd(dir_add,sizeof(dir_add));
			
			memset(add_end,0,sizeof(add_end));
			strcpy(add_end,path_end);
			add_end[strlen(add_end)]='/';
			strcat(add_end,re_dir->d_name);

			dir_cp(dir_add,add_end);
		}
		if(S_ISREG(s.st_mode))
		{
			memset(file_add,0,sizeof(file_add));
			strcat(file_add,re_dir->d_name);

			memset(add_end,0,sizeof(add_end));
			strcpy(add_end,path_end);
			add_end[strlen(add_end)]='/';
			strcat(add_end,re_dir->d_name);

			file_cp(file_add,add_end);
		}
	}
	get_prevDir_Addr(path_start);
	get_prevDir_Addr(path_end);
	chdir("..");
	return SUC;
}

