#include"main.h"
void output_1(char **name,int nb)
{
	int i;
	for(i=0;i<nb;i++)
	{
		if(name[i][0]=='.')
		{
			continue;
		}
		printf(" %10s  ",name[i]);
	}
	printf("\n");
}	
void output(struct stat * stat,char * mode_output,int nb,char **file_name)
{
	char mode[nb][11];
	char ino[20]={'\0'};
	char nlink[20]={'\0'};
	int i,j,k;
	char *time;
	char size[20]={'\0'};
	struct passwd *root_1=NULL;
	struct group *root_2=NULL;
	for(i=0;i<nb;i++)
	{
		if(mode_output[1]!='a')
		{
			if(file_name[i][0]=='.')
			{
				continue;
			}
		}
		memset(mode[i],0,sizeof(mode[i]));
		mode_change(mode[i],stat[i],nb);
		if(mode_output[0]=='i')
		{
			sprintf(ino,"%d",stat[i].st_ino);
			printf("%7s ",ino);
		}
		printf("%-11s",mode[i]);
		sprintf(nlink,"%d",stat[i].st_nlink);
		printf("%2s ",nlink);
		root_1=getpwuid(stat[i].st_uid);
		printf("%4s ",root_1->pw_name);
		root_2=getgrgid(stat[i].st_gid);
		printf("%4s ",root_2->gr_name);
		sprintf(size,"%d",stat[i].st_size);
		printf("%4s ",size);
		time=ctime(&stat[i].st_mtime);
		for(k=0;k<strlen(time)-1;k++)
		{
			printf("%c",time[k]);
		}
		printf(" %-11s\n",file_name[i]);
	}
}
void mode_change(char *mode,struct stat stat,int nb)
{
	int mode_num=0;
	if(S_ISREG(stat.st_mode))
	{
		mode[0]='-';
	}
	else 
		if(S_ISDIR(stat.st_mode))
		{
			mode[0]='d';
		}
		else
			if(S_ISCHR(stat.st_mode))
			{
					mode[0]='c';
			}
			else
				if(S_ISBLK(stat.st_mode))
				{
						mode[0]='b';
				}
				else
					if(S_ISFIFO(stat.st_mode))
					{
							mode[0]='p';
					}
					else
						if(S_ISLNK(stat.st_mode))
						{
								mode[0]='l';
						}
						else
							if(S_ISSOCK(stat.st_mode))
							{
									mode[0]='s';
							}

	mode_num=(stat.st_mode>>6)&0x7;
	change(mode,1,mode_num);

	mode_num=(stat.st_mode>>3)&0x7;
	change(mode,4,mode_num);

	mode_num=stat.st_mode&0x7;
	change(mode,7,mode_num);
}
void change(char *mode,int start_i,int mode_num)
{
	int num;
	if((num=(mode_num&0x01))==0)
	{
		mode[start_i+2]='-';
	}
	else
		mode[start_i+2]='x';
	if((num=(mode_num>>1)&0x01)==0)
	{
		mode[start_i+1]='-';
	}
	else
		mode[start_i+1]='w';
	if((num=(mode_num>>2)&0x01)==0)
	{
		mode[start_i]='-';
	}
	else
		mode[start_i]='r';
}
