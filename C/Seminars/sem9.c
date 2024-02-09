#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXLEN 15
//сигналы
/* отец и сын поочередено читают строку из файла. Длина строки ограничена MAXLEN. Работа с помощью систмных функций. Вывод должен продолжаться в течение одной секунды или по завершению чтения из файла.*/

void SigHandler1(int s)
{
    exit(0);
}
void SigHandler2(int s)
{
    ;
}
void SigHandler3(int s)
{
 printf("Прошла 1 секунда\n");
 exit(0);
}
void SigHandler4(int s)
{
   ;
}
int main(int argc, char **argv)
{
    signal(SIGTSTP, SigHandler2);
    signal(SIGALRM, SigHandler3);
    signal(SIGUSR1, SigHandler4);
    signal(SIGCHLD, SigHandler1);
    if (argc != 2) { printf("Not right parametres\n"); return 0;}
    int fd = open(argv[1], O_RDONLY, 0444 );
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        alarm(1);
        while(1)
        {
        char str[MAXLEN] = {0};
            if (read(fd, &str, sizeof(str)*sizeof(char) - 1))
            {
            printf("Son слово:  %s\n", str);
            kill(getppid(), SIGTSTP); //ctrl^z отцу
            pause();
            }
            else 
            {
            exit(0);
            }
            
        }
    }
    else if (pid > 0)
    {
        char str[MAXLEN] = {0};
        while(1)
        {
            pause();
            if (read(fd, &str, sizeof(str)*sizeof(char) - 1))
            {
            printf("Father слово:  %s\n", str);
            kill(pid, SIGUSR1);
            }
            else 
            {
            kill(pid, SIGUSR1);
            close(fd);
            wait(0);
            exit(0);
            }
        }
    }
    
}
