#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdint.h>

/* функция должна принимать права доступа к файлу (например, rwxrw-rwx) и возвращать целое значение прав доступа к файлу. */
int f1( const char * str)
{
    if (str == NULL) exit(-1);
    if (strlen(str) != 9) exit(-1);
    unsigned int res = 0;
    char s[]= "rwxrwxrwx";
    int k = sizeof(s);
    for (int i = 0; i < k - 1; i++)
    {
        res <<= 1;
        if (s[i] == str[i])
        
            res |= 1;
    }
        return (int) res;

}

/*функция принимает целое значение в восьмеричном виде и возвращает указатель на строку в формате прав доступа rwx(9 знаков) */
char * f2(int x)
{
    char *s = malloc(sizeof(char) * 10);
    char *tmp = "rwxrwxrwx";
    for (int i = 0; i < 9; i++)
    {
        if (x & (1 << (8 - i)))
        s[i] = tmp[i];
        else s[i] = '-';
    }
    s[9] = '\0';
    return s;
}
int main(int argc, char ** argv)
{
    if (argc < 2) {printf("No directory"); return -1;}
    DIR * dir = opendir(argv[1]);
    if (!dir)
    {
        perror("dir open");
        return -1;
    }
    struct dirent *entry;
    struct stat st;
    char *s = malloc(sizeof(char) * 255);
    
    /*для всех файлов из текущего каталога вывести на экран имя файла, номер его индексного дескриптора, тип файла в виле строки и права доступа в формате rwx */
    while ((entry = readdir(dir)) != NULL)
    {
        if (lstat(entry->d_name, &st) == 0)
        {
       
         switch (st.st_mode & S_IFMT) {
           case S_IFBLK:   s = "block device";            break;
           case S_IFCHR:   s = "character device";        break;
           case S_IFDIR:   s = "directory";               break;
           case S_IFIFO:   s = "FIFO/pipe";               break;
           case S_IFLNK:   s = "symlink";                break;
           case S_IFREG:   s = "regular file";            break;
           case S_IFSOCK:  s = "socket";                  break;
           default:        s = "unknown?";               break;
           }

        {
        fprintf(stdout, "%s %ld %s %s\n", entry->d_name, st.st_ino, f2(st.st_mode), s );
        free(f2(st.st_mode));
        }
        
     }
        
        else return -1;

    }
    closedir(dir);
    printf("%s\n", f2(0660));
    return 0;
}
