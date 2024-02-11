#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <string.h>

void rec_dir(char * filename)
{
    DIR * dir = opendir(filename);
    if (!dir) {exit(1);}
    struct dirent * extra;
    struct stat st;
    while ((extra = readdir(dir)) != NULL)
    {
    char newfile[sizeof(extra->d_name) + sizeof(filename)];
    sprintf(newfile, "%s/%s", filename, extra->d_name);
    if (lstat(newfile, &st) == 0)
        {
            if (((st.st_mode & S_IFMT) == S_IFDIR) && (strcmp(extra->d_name, ".")!= 0) && (strcmp(extra->d_name, "..")!= 0) )  // if file - directory
                {char  newdir[sizeof(filename) + sizeof(extra->d_name)]= {0} ;
                    sprintf(newdir, "%s/%s",filename, extra->d_name );
                    rec_dir((newdir)); //
                }
            else if ((st.st_mode >> 3 & 1) && (st.st_mode >> 6 & 1)&& (strcmp(extra->d_name, ".")!= 0) && (strcmp(extra->d_name, "..")!= 0))
                printf("%s\n", extra->d_name);
        }
    else {
        perror("No stat");
        exit(-1);
    }
    }
    closedir(dir);
}
int main(int argc, char ** argv)
{
    if (argc < 2) { printf("No directory"); exit(-1);}
    rec_dir(argv[1]);
    return 0;
}