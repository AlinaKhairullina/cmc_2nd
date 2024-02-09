//cmd 1 | cmd2 > f(в программу 2 записывается результат программы 1 . если программа 2 завершилась раньше 1, то результат 1 перенаправить в стандартный поток вывода)

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
    pid_t pid1, pid2;
    int fd[2];
    pipe(fd);
    if (pid1 =  (fork()) == 0)//son
    {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        execlp(argv[1], argv[1], NULL);
    }
    else 
    {
         if (pid2 =  (fork()) == 0)
         {
            dup2(fd[0], 0);
            close(fd[1]);
            close(fd[0]);
            execlp(argv[2], argv[2], NULL);
            exit(1);
         }
         else if (pid2 > 0)
         {
            int stat;
            waitpid(pid2, &stat, 0);
            char buf;
            close(fd[1]);
            while(read(fd[0], &buf, 1) > 0)
            {
                printf("%c", buf);
            }
            close(fd[0]);
         }
    }
    wait(0);
    return 0;
}
