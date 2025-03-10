#include "/home/c/class_c/APUE/apue.h"

#define SIZE (1024) 

void op_file(char **argv);

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("%s filename filename\n",argv[0]);
        return -1;
    }

    op_file(argv);

    return 0;
}

void op_file(char **argv)
{
    char buf[SIZE];
    int ret = 0;
    int fdSrc = 0;
    int fdDest = 0;

    fdSrc = open(argv[1], O_RDONLY);
    
    if (fdSrc < 0)
    {
        perror("open");
        return ;
    }

    fdDest = open(argv[2], O_EXCL|O_CREAT|O_WRONLY ,0644);
    if(fdDest < 0)
    {
        if(EEXIST == errno)
        {
            char i;
            printf("file has exist,recover it?(y/n)");
            scanf("%c", &i);
            getchar();

            if('y' == i||'Y' == i)
            {
                
                fdDest = open(argv[2], O_WRONLY);
                memset(buf, 0, SIZE);
                ret = write(fdDest, buf, SIZE);
                if(ret < 0)
                {
                    close(fdSrc);
                    exit(-1);
                }
                lseek(fdDest, 0, SEEK_SET);
            }else
            {
                close(fdSrc);
                exit(-1);
            }
                        
        }
        if (fdDest < 0)
        {
            perror("open");
            close(fdSrc);
            exit(-1);
        }
    }
    while(1)
    {
        memset(buf, 0, SIZE);
        ret = read(fdSrc, buf, SIZE - 1);
        if (ret < 0)
        {
            perror("read");
            goto ERR;
        }
        ret = write(fdDest, buf, ret);

        if(ret < 0)
        {
            perror("write");
            goto ERR;
        }
        printf("ret:%d\n",ret);
        if(ret != SIZE - 1)
        {
            break;
        }
    }

ERR:
    close(fdSrc);
    close(fdDest);
    return ;
}
