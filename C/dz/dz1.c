#include <stdio.h>
#include <stdlib.h>

#define N 4

char* read ( void ) //функция 
{
    char* stroka, *x; // x - нужен для проверки исчерпания памяти
    char c;
    int len = 0, i = 0; // len : текущая длина выделенной памяти , i : текущая длина строки - 1 .
    stroka = malloc(N);
    if (!stroka) {fprintf(stderr, "malloc returned NULL" ); free(stroka); exit(1);}
    while (((c = getchar()) != '\n') && ((c) != EOF) )
    {
        if (!len )
        {
            stroka[i] = c;
            i++;
            len += N;
        }
        else 
        { 
            if (!(i % N))
            {
                x = malloc(N);
                if (!x) {fprintf(stderr, "malloc returned NULL" ); free(x); free(stroka); return NULL;} //проверка на исчерпание памяти
                free(x);
                {
                stroka = realloc(stroka, len  + N);
                stroka[i] = c;
                i++; 
                len += N;
                }
            }
            else {stroka[i] = c; i++;}
        }
    }
    stroka[i] = '\0';
    stroka = realloc(stroka, i + 1);
    return stroka;
}
int main()
{
    char* res = read();
    printf("%s\n", res);
    if (res) free(res);
    return 0;
}

