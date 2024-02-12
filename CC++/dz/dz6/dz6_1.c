#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

int main(int argc, char ** argv)
{
    if (argc < 2) { printf("No directory\n"); return -1;}
    DIR * dir= opendir(argv[1]);
    if (!dir)
    {
        perror("No dirent");
        return -1;
    }
    struct dirent * extra;
    struct stat st;
    while ((extra = readdir(dir)) != NULL)
    {
        if (lstat(extra->d_name, &st) == 0)
        {
            if ((st.st_mode & S_IFMT) == S_IFLNK) // if file - symlink
            {
                char buf[255] = {0};
                buf[254] = '\0';
                if((readlink(extra->d_name, buf, sizeof(buf))) > 0)
                {
                    printf("%s\n", buf);
                }
            }
        }
        else 
        {
            perror("Stat error");
            exit(1);
        }
    }
    closedir(dir);
     return 0;
}