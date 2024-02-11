#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
    if (argc != 4) 
    {
        printf("To run programm please write: ./a.out <file1> <file2> <file3>\n");
        return 0;
    }
    int f1 = open(argv[1], O_RDONLY);
    if (f1 < 0) 
    {
        perror("Error open file 1 : ");
        return 1;
    }
    int f2 = open(argv[2], O_RDONLY);
     if (f2 < 0) 
    {
        perror("Error open file 2 : ");
        return 1;
    }
    int f3 = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (f3 < 0) 
    {
        perror("Error open file 3 : ");
        return 1;
    }
    int fd1[2], fd2[2], fd3[2];
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pid_t pid1, pid2;
    if ((pid1 = fork()) < 0)
    {
        perror("Fork: ");
        exit(1);
    }
    if (pid1 == 0) //первый сын
    {
        char c1 = 0, tmp = '\n';
        close(fd1[0]);
        close(fd3[0]);
        if (read(f2, &c1, sizeof(char)))
        {write(fd2[1], &tmp, sizeof(char)); lseek(f2, 0, SEEK_SET);} //записываем что-то в канал брата 2 чтобы начать чтение файла
        else 
        {
            tmp = -1;
            write(fd2[1], &tmp, sizeof(char));
        }
        close(fd2[1]);
        c1 = 0;
        while (read(fd2[0], &tmp , sizeof(char)) > 0)  //читаем из канала брата 2
        {
            if (tmp == '\n')
            {
                while((read(f1, &c1, sizeof(char))) && (c1 != '\n'))
                {
                write(f3, &c1, sizeof(char)); //to file
                c1 = '\0'; 
                }
            if (c1 == '\n') {write(f3, &c1, sizeof(char));  write(fd1[1], &c1, sizeof(char)); c1 = 0;} //передали брату \n
            else if (c1 == '\0') 
            {
                char fend = -1;
                close(f1);
                close(fd3[1]);
                close(fd2[0]);
                write(fd1[1], &fend, sizeof(char)); // передали брату конец файла
                close(fd1[1]);
                exit(0);
            }
            }
            if (tmp == -1)//если файл 2 закончился
            {
                int k = 0;
                while (read(f1, &c1, sizeof(char)))
                {
                        if (c1 == '\n') k++;
                }
                close(f1);
                close(fd1[1]);
                close(fd2[0]);
                write(fd3[1], &k, sizeof(int));
                close(fd3[1]);
                exit(0);
            }
        }
    }
    else  {// pid1 > 0 (отец)

     if ((pid2 = fork()) < 0) //создает второго сына
    {
        perror("Fork: ");
        exit(1);
    }
    if (pid2 == 0) //второй сын
    {
        char c2 = 0, tmp = 0;
        close(fd2[0]);
        close (fd1[1]);
        close (fd3[0]);
        while (read(fd1[0], &tmp , sizeof(char))>0)  //читаем из канала брата 1
        {
            if (tmp == '\n')
            {
                while((read(f2, &c2, sizeof(char))) && (c2 != '\n'))
                {
                write(f3, &c2, sizeof(char)); //to file
                c2 = '\0';
                }
            if (c2 == '\n') {write(f3, &c2, sizeof(char));  write(fd2[1], &c2, sizeof(char)); c2 = 0;} //передали брату \n
            else if (c2 == '\0') 
            {
                int fend = -1;
                write(fd2[1], &fend, sizeof(char)); // передали брату конец файла
                close(f2);
                close(fd3[1]);
                close(fd1[0]);
                close(fd2[1]);
                exit(0);
            } 
            }
            if (tmp == -1)//если файл 1 закончился
            {
                int k = 0;
                while (read(f2, &c2, sizeof(char)))
                {
                        if (c2 == '\n') k++;
                } 
                close(f2);
                close(fd1[0]);
                close(fd2[1]);
                write(fd3[1], &k, sizeof(int));
                close(fd3[1]);
                exit(0);
            }
        }
       
    }
    else if (pid2 > 0 ) // отец
    {
        close (fd3[1]);
        int res = 0;
        read(fd3[0], &res, sizeof(int));
        printf("%d\n", res);
        close(f3);
        close(fd3[0]);
        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]);
    wait(0); 
    wait(0);
        return 0;
    }
    }
    
}