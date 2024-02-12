/* Реализовать игру пинг-понг между N процессами, синхронизировать с помощью сигналов (использовать только один канал)*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
void user12(int s)
{
      ;
}
int main(int argc, char **argv)
{
    if (argc != 4) {printf("Not right parametres\n"); return 0;}
    int n = atoi(argv[1]);
    if ((n < 2 )|| (n > 5)) {printf("N should be in [2;5] and be \n"); return 0;}
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int c;
    pid_t pid;
    int fd[2];
    pipe(fd);
    signal(SIGUSR1, user12);
    int *p = malloc(sizeof(int)*n); // массив pidов
    if (!p) {perror("malloc "); return 1;}
    p[0] = getpid();
    for (int i = 0; i < n - 1; i++)
    {
        pid = fork();
        p[getpid() - (p[0])] = getpid();
        if (pid == 0) break;
        if (pid < 0) return 1;
    }
    if (pid > 0)
    {
        write(fd[1], &a, sizeof(int));
        kill(getpid() + 1, SIGUSR1);
    }
   while(1)
    {
        pause();
        if (read(fd[0], &c, sizeof(int)))
        {
        if (c <= b) printf("number: %d pid: %d\n", c++, getpid());
        if (c >= b)
            {
                close(fd[0]);
                write(fd[1], &c, sizeof(int));
                close(fd[1]);
                if ((getpid() - (p[0])) != (n - 1)) kill(getpid() + 1, SIGUSR1);
                else  kill((p[0]), SIGUSR1);
                break;
            }
        else
            {
                write(fd[1], &c, sizeof(int));
                if ((getpid() - (p[0])) != (n - 1)) kill(getpid() + 1, SIGUSR1);
                else kill((p[0]), SIGUSR1); 
            }
        }
        
    }
    close(fd[0]);
    close(fd[1]);
    if (pid > 0)
    for (int i = 0; i < n - 1; i++)
    {
        wait(0);
    }
    exit(0);
}
