#include<stdio.h> 
#include<stdlib.h>
#define N 100

typedef struct Student
{
	char name[10];
	int math;
	int chinese;
	int english;
}S_s;
void ranking(S_s *point,int num)
{
	int arr[N],id[N],nu=0,tmp,i,finaly;
	for(;nu<num;nu++)
	{
		arr[nu]=(((point+nu)->math)+((point+nu)->chinese)+((point+nu)->english));
		id[nu]=nu;
	}
	for(i=0;i<N;i++)
	{
		nu=0;
		for(nu=0;nu<num-1;nu++)
		{
			if(arr[nu]>arr[nu+1])
			{
				tmp=arr[nu];
				arr[nu]=arr[nu+1];
				arr[nu+1]=tmp;
				tmp=id[nu];
				id[nu]=id[nu+1];
				id[nu+1]=tmp;
			}	
		}
	}
	finaly=num*0.3;
	printf("最高%d 最低%d\n",arr[num-1],arr[0]);
	if(arr[num-1]-arr[0]<=30&&arr[num-1]>270)
		printf("老师据我推断你们班好像没有学渣了。\n");
	else if(arr[1]==arr[2]&&arr[2]==arr[3]&&arr[3]==arr[4]&&arr[4]==arr[5]&&arr[5]==arr[6])
		printf("老师据我推断你们班好像没有学渣了但是......................。\n");
	else if(arr[num-1]<=150)
		printf("-_-||!\n");
	else
	{
		printf("老师你们班还有%d个学渣，加油。\n",finaly);
		for(nu=0;nu<finaly;nu++)
		{
			printf("姓名：%s 数学：%d 语文：%d 英语：%d\n",(point+id[nu])->name,(point+id[nu])->math,(point+id[nu])->chinese,(point+id[nu])->english);
		}
	}		
}
void average(S_s *point,int num)
{
	int math_av=0,ch_av=0,en_av=0,nu=0,sum_av=0;
	for(;nu<num;nu++)
	{
		math_av=((point+nu)->math)+math_av;
		ch_av=((point+nu)->chinese)+ch_av;
		en_av=((point+nu)->english)+en_av;
		sum_av=math_av+ch_av+en_av;
	}
	math_av=math_av/num;
	ch_av=ch_av/num;
	en_av=en_av/num;
	sum_av=sum_av/num;
	printf("数学平均分:%d语文平均分：%d英语平均分：%d总平均分：%d\n",math_av,ch_av,en_av,sum_av);
	ranking(point,nu);
}
int main()
{
	int number,nu=0;
	printf("请输入学生总人数。\n");
	scanf("%d",&number);
	S_s *stu=(S_s*)malloc(number*sizeof(S_s));
	if(stu==NULL)
		printf("malloc error.\n");
	for(;nu<number;nu++)
	{
		printf("这是第%d个学生，请依次输入姓名 数学成绩，语文成绩，英语成绩。\n",nu+1);
		scanf("%s%d%d%d",&(stu+nu)->name,&(stu+nu)->math,&(stu+nu)->chinese,&(stu+nu)->english);
	//	printf("%s%d%d%d",(stu+nu)->name,(stu+nu)->math,(stu+nu)->chinese,(stu+nu)->english);
	}	
	average(stu,number);
} 
