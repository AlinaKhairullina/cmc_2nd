#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2, pid3;
    int fd[2];
    pipe(fd);
    if ((pid1 = fork()) < 0 )
    {
        perror("Fork : ");
        return 0;
    }
    if (pid1 == 0)//son
    {
        if ((pid2 = fork()) < 0)
        {
            perror("Fork : ");
            return 0;
        }
        if (pid2 == 0)//grandson
        {
            if ((pid3 = fork()) < 0)
            {
                perror("Fork : ");
                return 0;
            }
            if (pid3 == 0)//greate-grand son
            {
                time_t currentTime;
                time(&currentTime);
                close(fd[0]);
                write(fd[1], &currentTime, sizeof(int));
                write(fd[1], &currentTime, sizeof(int));
                write(fd[1], &currentTime, sizeof(int));
                close(fd[1]);
                exit(0);
                
            }
            else if (pid3 > 0) //grandson
            {
                time_t currentTime;
                read(fd[0], &currentTime, sizeof(int));
                close(fd[0]);
                close(fd[1]);
                struct tm *ltime = localtime(&currentTime);
                if (ltime->tm_mday > 9) printf("D:%d\n", ltime->tm_mday );
                else printf("D:0%d\n", ltime->tm_mday );
                exit(0);

            }
        }
        else if (pid2 > 0) //son
        {
            time_t currentTime;
            read(fd[0], &currentTime, sizeof(int));
            close(fd[0]);
            close(fd[1]);
            struct tm *ltime = localtime(&currentTime);
            if ((ltime->tm_mon + 1) > 9) printf("M:%d\n", ltime->tm_mon + 1);
                else printf("M:0%d\n", ltime->tm_mon + 1 );
                exit(0);
        }
    }
    else if (pid1 > 0) //father
    {
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        waitpid(pid3, NULL, 0);
        time_t currentTime;
        read(fd[0], &currentTime, sizeof(int));
        close(fd[0]);
        close(fd[1]);
        struct tm *ltime = localtime(&currentTime);
        printf("Y:%d\n", ltime->tm_year + 1900 );
        return 0;
    }
}