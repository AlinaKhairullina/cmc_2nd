#include <stdio.h>
#include <stdlib.h>

/*Написать функцию реверсирования однонаправленного списка*/

struct list{
    int key;
    struct list * next;
};

struct list* reverse(struct list* l)
{
    struct list* tmp = NULL, * prev = NULL;
    while (l)
    {
        tmp = l->next;
        l->next = prev;
        prev = l;
        l = tmp;        
    }
    l = prev;
    return l;
}

struct list* create(void)
{
    int x; 
    struct list * l  = NULL;
    if (scanf("%d", &x) != 1 ) return NULL;
    l = malloc(sizeof(struct list));
    l->key = x;
    l->next = create();
    return l;
}

void print_list(struct list * l)
{
    if (!l) return;
    printf("%d ", l->key);
    print_list(l->next);
}

void del_list(struct list ** l)
{
    if (!(*l)) return;
    del_list(&(*l)->next);
    free(*l);
    (*l) = NULL;
}

int main()
{
    printf("Введите список чисел: ");
    struct list * l = create();
    printf("Исходный список: ");
    print_list(l);
    printf("\n");
    l = reverse(l);
    printf("Преобразованный список:");
    print_list(l);
    printf("\n");
    del_list(&l);
    return 0;
}
