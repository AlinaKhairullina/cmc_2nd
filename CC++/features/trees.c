#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int key;
    struct tree *left, *right;
};

//создание дерева
struct tree* create(struct tree * T, int x) 
{
    if (!T) 
    {
        T = malloc(sizeof(struct tree));
        T->key = x;
        T->right = NULL;
        T->left = NULL;
    }
    else 
    {
        if (T->key < x)
        T->right=create(T->right, x);
        else
        T->left=create(T->left, x);
    }
    return T;
}

//вывод дерева
void print_tree(struct tree* T)
{
    if (T == NULL) return;
    printf("%d ", T->key);
    print_tree(T->right);
    print_tree(T->left);
}

//удаление дерева
void del_tree(struct tree **T)
{
    if ((*T) == NULL) return; 
    del_tree(&((*T)->left));
    del_tree(&((*T)->right));
    free(*T);
    *T = NULL;
}

//есть ли элемент в дереве
int elem(struct tree * T, int x)
{
    if (!T) return 0; //если дерево пустое
    if (T->key == x) return 1;
    if (T->key > x) return elem(T->left, x);
    else return elem(T->right, x);
}

//высота до определенной вершины
int height(struct tree * T, int x) 
{
    if (!T) return  -1;
    if ((T->key == x) && (T->right == NULL) && (T->left == NULL)) return 0;
    if (T->key < x)
    {
         return height(T->right, x) + 1;
    }
    else return height(T->left, x) + 1;
}

//удаление узла со значением х дерева
void del_uzel(struct tree** T, int x)
{
    if (!elem((*T), x)) return;
    if ((*T)->key > x) del_uzel(&((*T)->left), x);
    else if ((*T)->key < x) del_uzel(&((*T)->right), x);
    else if ((!(*T)->right) && (!(*T)->left))
    { 
        free(*T);
        (*T) = NULL;
        return;
    }
    else if ((!(*T)->right) && ((*T)->left))
    {
        struct tree* T1 = (*T);
        (*T) = (*T)->left;
        free(T1);
        return;
    }
    else if (((*T)->right) && (!(*T)->left))
    {
        struct tree* T1 = (*T);
        (*T) = (*T)->right;
        free(T1);
        return;
    }
    else if ((*T)->right && (*T)->left)
    {
        struct tree* T1 = (*T);
        (*T) = (*T)->right;
        while ((*T) -> left) (*T) = (*T)->left;
        (*T)->left = T1->left;
        free(T1);
        return;
    }
}

//высота дерева
int height_tree(struct tree* T)
{
    if (T == NULL) return 0;
    return height_tree(T->right) + height_tree(T->left) + 1;
}

//разница между высотами справа и слева
int odds(struct tree* T)
{
    return (height_tree(T->right) - height_tree(T->left));
}

// балансировка, поворот направо на узле T
struct tree* rotetoright(struct tree* T) /
{
    struct tree* p = T->left;
    T->left = p->right;
    p->right = T;
    return p;
}

//балансировка, поворот налево на узле T
struct tree* rotetoleft(struct tree* T)
{
    struct tree* p = T->right;
    T->right = p->left;
    p->left = T;
    return p;
}

//сбалансированное дерево
struct tree* balance(struct tree * T)
{
    while (odds(T) >= 0)// если правое поддерево больше
    {
        while (odds(T->right) < 0) //если правое поддерево правого поддерева меньше левого
        T->right= rotetoright(T->right);
        T = rotetoleft(T); 
    }
    while (odds(T) <= 0)// если левое поддерево больше 
    {
        while (odds(T->left) > 0) //если левое поддерево левого поддерева меньше правого 
        T->left = rotetoleft(T->left);
        T = rotetoright(T);
    }
    return T;
}


int main()
{
    struct tree * T = NULL;
    int n;
    while (scanf("%d", &n) != EOF)
     T = create(T, n);
    printf("\n");
    del_uzel(&T, 5);
    T = balance(T);
    //сначала печатается корень(первое число), потом - правое поддерево, затем - левое 
    printf("\nсбалансированное дерево: ");
    print_tree(T);
    del_tree(&T);
    return 0;
}
