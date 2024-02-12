#include <stdio.h>
#include <stdlib.h>

//определить количество строк в файле

/*создать массив для хранения информации о строках файла
а)в интерактивном режиме по номеру строки в файле на экран выдавать ее содердимое. Обеспечить "быстрый доступ к файлу" без прохода по файлу.
б)создать новый файл, вывести в него строки исходного файла, упорядочив их по возрастанию длины.*/

 int main(int argc, char ** argv)
 {

    if (argc < 1) 
    {
        printf("Not enought parametres");
        return 0;
    }
    FILE *f1 = fopen(argv[1], "r+");
    if (!f1)
    {
        printf("Not file\n");
        return 0;
    }
    char c, pred;
    int n = 0, k = 0;
    
    while ((c = fgetc(f1)) != EOF)
    {
        pred = c;
        if (c == '\n') n++;
    }
    if (pred != '\n')
    {
        fprintf(f1, "\n"); n++;
    }
    printf("Количество строк в файле: %d\n", n);
    long int * p = malloc(sizeof(long int) * (n + 1));
    fseek(f1, 0, SEEK_SET);
    for (int i = 0; i < n ; i++)
    {
        p[i] = ftell(f1);
        while ((c = fgetc(f1))!= '\n');

    }
    while (1)
    {
    printf("Введите номер строки, которую хотите вывести(конец вывода -1): " );
    scanf("%d", &k);
    if (k > n ) {
        printf("Неверный номер строки\n");
        }
    if (k == -1) {
        printf("Конец\n"); break;
        }
    fseek(f1, p[k - 1], SEEK_SET);
    printf("строка №%d ", k );
    while ((c = fgetc(f1)) != '\n')
    {
        printf("%c", c);
    }
    printf("\n");
    }
//3
    FILE * f2 = fopen("f2.txt", "w");
    if (!f2) 
    {
        perror("Not File");
        return 0;
    }
    long int * q = malloc(sizeof(long int) * n);
    int tmp = 0;
    fseek(f1, 0, SEEK_SET);
    long int len = 1;
    for (int i = 0; i < n; i++)
    {
        while ((c = fgetc(f1)) != '\n')
        len++;
        q[i] = len;
        len = 1;
    }
   for (int i = 0; i < n ; i++)
   {
    for (int j = i + 1; j < n; j++)
    {
        if (q[i] > q[j])
        {
            tmp = p[i];
            p[i] = p[j];
            p[j] = tmp;
        }
    }
   }
    for (int i = 0; i < n; i++)
    {
        fseek(f1, p[i], SEEK_SET);
        while ((c = fgetc(f1)) != '\n')
            fprintf(f2, "%c", c); 
        fprintf(f2, "\n");

    }
    free(q);
    free(p);
    fclose(f2);
    fclose(f1);
    return 0;
}
 
