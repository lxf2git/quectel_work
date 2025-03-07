#include"apue.h"
#define SIZE 100
int main()
{
	int index=0;

	key_t key_shm = ftok("/root",'a');
	int shmid = shmget(key_shm,SIZE,O_RDWR);
	char *p=shmat(shmid,NULL,0);

	while(1)
	{
		if(p[index]=='\0')
		{
			break;
		}
		if(p[index]>97&&p[index]<122)
		{
			p[index]-=32;
		}
		index++;
	}

	key_t key_sem=ftok("/root",'b');
	int semid=semget(key_sem,1,O_RDWR);
	if(semid<0)
	{
		show_err("semget_err!");
	}
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(semid,&buf,1);

	return 0;
}
