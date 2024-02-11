#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lens(FILE * f)
{
    char c;
    int n = 0;
    fseek(f, 0, SEEK_SET);
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n') n++;
    }
    return n;
}

void more (char fl, int  num, int linenum, FILE * f ) // more([-s][-num][+linenum] filename)
{
    int n = lens(f), len = 0;
    long int * p = malloc(sizeof(long int) * (n + 1)); // 
    char c = 0, cur = 0, pred = 0;
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < n ; i++)
    {
        p[i] = ftell(f);
        while ((cur = fgetc(f))!= '\n');
    }
    fseek(f, p[linenum - 1], SEEK_SET);
    while (1)
    {
        if (!fl){ //если опция -s отсутствует
        for (int i = 0; i < num; i++)
                {
                   while (((cur = fgetc(f) )!= '\n') && (cur != EOF)) fprintf(stdout, "%c", cur);
                   if ((cur != EOF) && (i != num - 1)) fprintf(stdout, "%c", cur); 
                }
        if  (cur == EOF) break;
        else {if (((c = getchar()) != 'q')) 
        continue;
            else break; }
        }
        else // если присутствует опция -s 
        {
        for (int i = 0; i < num; i++)
                {
                   len = 0;
                   while (((cur = fgetc(f)) != '\n') && (cur != EOF)) {fprintf(stdout, "%c", cur); len++; }
                   if ((cur != EOF) && (i != num - 1)&& (len)) fprintf(stdout, "%c", cur); 
                    pred = cur;
                    if (cur != EOF) {
                        cur = fgetc(f);
                        if (cur == '\n')
                        {
                            while (cur == pred)
                            {
                                pred = cur;
                                if (cur != EOF) {cur = fgetc(f);}
                            }
                        fprintf(stdout,"%c", pred);
                        }
                        else if (!len) {printf("\n"); i++;} // если одна пустая строка
                        else if (cur == EOF) printf("\n"); // прочитали последнюю строчку файла
                    if (cur != EOF) fseek(f, SEEK_CUR - 2, SEEK_CUR);}
                }
        if  (cur == EOF) break;
        else {if (((c = getchar()) != 'q')) 
        continue;
            else break; }
        }
    }
}
    
int main(int argc, char ** argv)
{
    
    int num = 10, linenum = 1;
    char fl = 0; //флаг -s
    if (argc < 2) {printf("Not enough parametres\n"); return 0; }
    FILE *f = fopen (argv[argc - 1], "r");
    if (!f) {
        perror("No file"); 
        return -1;
        }
    for (int i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-s") == 0 ) fl = 1;
        if ((argv[i][0] == '-') && (strcmp(argv[i], "-s") != 0 )) 
            num = -(atoi(argv[i])); 
        if (argv[i][0] == '+') 
            linenum = atoi(argv[i]); 
    }
    more(fl, num, linenum, f);
    fclose(f);
    return 0;
}