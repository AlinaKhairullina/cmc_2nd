#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
/*Одна из задач в МЗ. В командной строке передается имя бинарного файла. Переставить в файле числа так, чтобы в начале располагались отрицательные исла, а в конце - неотрицательные. Файл целиком читать нельзя.Временный файл создавать нельзя. */
int main(int argc, char ** argv)
{
    if (argc < 2) {printf("Not right parametres"); return -1;}
    int fd = open(argv[1], O_RDWR );
    if (fd == -1) {perror(""); return -1;}
    int k = 0, m = 0, n1, n2;
    while (read (fd, &n1, sizeof(int)))
    {
        k++;
        if (n1 > 0) 
        {
            m = k;
            while (read (fd, &n2, sizeof(int)))
            {
                m++;
                if (n2 < 0)
                {
                lseek(fd, (k-1)*sizeof(int), SEEK_SET);
                write(fd, &n2, sizeof(int));
                lseek(fd, (m-1)*sizeof(int), SEEK_SET);
                write(fd, &n1, sizeof(int));
                break;
                }
                else continue;
            }
            lseek(fd, k*sizeof(int), SEEK_SET);
        }
        else continue;
    }

    return 0;
}
