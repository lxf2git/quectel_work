#ifndef _MAIN_H_
#define _MAIN_H_
#define _FILE_OFFSET_BITS 64
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>
#include <pwd.h>
#include <grp.h>
#define N 100 //最多文件数
#define M 40 //文件名最大长度
void judge_output(int argc,char **argv,char *mode);
int open_deal(struct stat *stat,char **file_name,DIR *pdir);
void output(struct stat * stat,char * mode_output,int nb,char **file_name);
void mode_change(char *mode,struct stat stat,int nb);
void change(char *mode,int start_i,int mode_num);
void output_1(char **name,int nb);

#endif

