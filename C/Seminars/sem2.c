#include <stdio.h>

#define m 5

 //вывести символ в его двоичном представлении.
void print(char x)
{
    for (int i = sizeof(char)*8 - 1; i >= 0; i--)
    {
        int j;
        printf("%d", j = x >> i & 1 );
    }
}

//вывести n-ый бит в массиве charов, нумерация битов справа налево 7-0, 15-8, 23-16 и т.д.
int bitn1(const char *a, int dlina, int n)
{
    int i = n / 8 ;
    char j = a[i];
    int res;
    res = j >> (7 - n % 8) & 1;
    return  res;


} 

//вывести n-ый бит в массиве charов, нумерация битов слева направо 0-7, 8-15, 16-23 и т.д.
int bitn2(const char *a, int dlina, int n)
{
    int i = n / 8 ;
    char j = a[i];
    
    j <<= (n % 8);
    return  ((j & 0x80) >> 7);


} 

//подсчитать в массиве количество битовых областей из подряд идущих единиц, длина которых больше или равна n.
int z3(const char *a, int dlina, int n)
{
    int k = 0, res = 0;
    for (int i = 0; i < dlina * 8; i++)
    { 
        
        if (bitn2(a,  dlina, i))
        {
            k++;
        }
        else 
        {
        res += (k >= n);
        k = 0;
        }
        
    }
    return res ;
}

//определить максимальную длину областей подряд идущих единиц.
int z4(const char *a, int dlina, int n)
{
    int k = 0, res = 0, pred = 0;
    for (int i = 0; i < dlina * 8; i++)
    { 
        
        if (bitn2(a,  dlina, i))
        {
            k++;
        }
        else 
        {
            if (k > pred) 
            {res = k; pred = k;  } 
        k = 0;
        }
        
        
        
    }
    return res ;
}

int main()
{
    char a[m] = "~z~~";//исходных массив
    int n;
    scanf("%d", &n);
    for (int i = 0; i < m; i++)
    {print(a[i]); printf(" ");}
    printf("\n");
    printf("%d\n%d\n", z3(a, m, n), z4(a, m, n));
    return 0;
}
