#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 4) {printf("Not right parametres\n"); return 0;}
    int n = atoi(argv[1]);
    if ((n < 2 )|| (n > 5)) {printf("N should be in [2;5] and be \n"); return 0;}
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    pid_t pid;
    int c;
    int **fd = malloc(sizeof(int*)*n); //массив каналов (каждой паре каналов один канал , n процессов -> n каналов)
    if (!fd) {perror("malloc "); return 1;}
    for (int i = 0; i < n ; i++)
    {
        fd[i] = malloc(sizeof(int)*2);
        if (!fd[i]) {perror("malloc "); return 1;}
        pipe(fd[i]);
    }
    int *p = malloc(sizeof(int)*n); // массив pidов
    if (!p) {perror("malloc "); return 1;}
    p[0] = getpid(); //получаем pid отца

    for (int i = 0; i < n - 1 ; i++)
    {
       pid = fork();
       p[getpid() - p[0]] = getpid(); // записываем pid каждого процесса в массив pidов
       if (pid == 0) break;
       if (pid < 0) return 1;
    }
    if (pid > 0)//only father
    {
        close(fd[0][0]);
        write(fd[0][1], &a, sizeof(int));
    }
   if (getpid() - p[0] == 0) // отец записывает в последний элемент массива каналов, читает из 0 элемента массива
   {
    close(fd[n - 1][1]);
    while(read(fd[ n - 1 ][0], &c, sizeof(int)))
       {
        if (c <= b) printf("number: %d pid: %d\n" , c++, getpid());
        if (c >= b)
        {
            close(fd[0][0]);
            write(fd[0][1], &c, sizeof(int));//чтобы другие процессы завершились
            break;
        }
        else
        {
            close(fd[0][0]);
            write(fd[0][1], &c, sizeof(int));
        }
       }
    }
    else //другие процессы записывают в канал под номером, соответствующему их номеру, читают  из канала - номер - 1
    {
       close(fd[ getpid() - p[0] - 1 ][1]);
       while(read(fd[ getpid() - p[0] - 1 ][0], &c, sizeof(int)))
       {
       if (c <= b) printf("number: %d pid: %d\n" , c++, getpid());
        if (c >= b)
        { 
            close(fd[ getpid() - p[0] ][0]);
            write(fd[ getpid() - p[0] ][1], &c, sizeof(int));//чтобы другие процессы завершились 
            exit(0);
            
        }
        else
        {
            close(fd[ getpid() - p[0] ][0]);
            write(fd[ getpid() - p[0] ][1], &c, sizeof(int));
        }
       }
    }
    for (int i = 0; i < n; i++) //закрываем открытые дескрипторы в каждом процессе
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }
   if (pid > 0)
    {   
        for (int i = 0; i < n - 1; i++)
            wait(0); 
        free(p); // освобождаем память
        for (int i = 0; i < n; i++)
        free((fd[i]));
        free(fd);
        exit(0);
    }    
}