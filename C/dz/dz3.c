#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
struct list{
    char *str;
    struct list * next, *pred;
};
struct list* create_list(int n) //создание двунаправленного списка
{
    char s[255];
    struct list * L = NULL, *P = NULL, *L_pred = NULL; 
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s) ;
        if (!L)
        {
        L = malloc(sizeof(struct list));//
        L->str = malloc(sizeof(char)*(strlen(s) + 1));
        L->pred = NULL;
        L->next = NULL;
        strcpy(L->str, s);
        P = L;
        }
        else 
        {
            L_pred = P;
            P->next = malloc(sizeof(struct list));
            P = P->next;
            P->str = malloc(sizeof(char)*(strlen(s) + 1));
            strcpy(P->str, s);
            P->pred = L_pred;
            P->next = NULL;
        }
    }
    return L;
}
void print_list(struct list ** L)// 3 вывод списка на экран
{
    if (!(*L)) return;
    printf("%s ", (*L)->str);
    print_list(&(*L)->next);
}
void del_list(struct list **L)//удаление списка
{
    if (!(*L)) return;
    del_list(&(*L)->next);
    free(((*L)->str));
    free((*L));
    (*L) = NULL;
}
void del_n_elem(struct list** L) // 4
{
    int n, i;
    struct list * L1 = *L;
    printf("\nВведите число n: ");
    scanf("%d", &n);
    if (!(*L)) return;
    for ( i = 1; i < n ; i++)
    {
        if (L1->next)
        L1 = L1->next;
        else return;
    }
    struct list* p = L1;
    if (i != 1) {
        L1 = L1->pred;
        L1->next = p -> next;
        if (L1->next) L1->next->pred = L1;
        else L1->next = NULL;
        }
    else {
        if ((*L)->next) (*L) = (*L) -> next;
        else {
            free((*L)->str);
            free((*L)); 
            (*L) = NULL; 
            return;
            }
        (*L)->pred = NULL;
    }
    free(p->str);
    free(p);
}
void add_n_elem(struct list ** L) // 5
{
    int n, i;
    struct list * L1 = (*L);
    struct list * p = NULL;
    if (!(*L)) return;
    char s[255]; 
    printf("\nВведите строку для добавления: ");
    scanf("%s", s);
    printf("Введите число n: ");
    scanf("%d", &n);
    p = malloc(sizeof(struct list));
    p->str = malloc(sizeof(char)*(strlen(s) + 1));
    p->pred = NULL; p->next = NULL;
    strcpy(p->str, s);
    for (i = 1; i < n ; i++)
    {
        if (L1->next)
            L1 = L1->next;
        else return;
    }
    p->next = L1->next;
    p->pred = L1;
    if (L1 -> next) L1->next->pred = p;
    L1->next = p;
}
int main()
{
    int n;
    printf("Количество элементов в списке: ");
    scanf("%d", &n);
    struct list * L = create_list(n);
    void (*f[3])(struct list **L); 
    f[0] = print_list;
    f[1] = del_n_elem;
    f[2] = add_n_elem;
    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0 :  printf("\nИсходный список: ");
                 f[i](&L); break; 
            case 1 : f[i](&L); printf("\nПосле удаления n-го элемента список: "); 
                f[0](&L); break; 
            case 2 : f[i](&L); printf("\nПосле добавления нового слова: ");
                f[0](&L); break; 
        }
    }
    del_list(&L);
    printf("\n");
    return 0;
}