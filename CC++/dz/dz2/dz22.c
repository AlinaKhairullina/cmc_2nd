#include <stdio.h>

typedef unsigned int uint;

/*Если в x старший байт не равен его младшему байту, поменять эти байты местами, иначе обнулить остальные (все, кроме старшего и младшего) байты в x.*/

uint change(uint x)
{
    uint  c = 0x00ffff00; //маска
    if ((x >> 24) != (x & 0x000000ff)) // если x1 != x4
        x = (x & c) | (((x >> 24) | (x << 24)) & (~c)); 
    else 
        x = (x & (~c));
    return x;
}

int main()
{
    uint n, res;
    scanf("%d", &n);
    printf("До:    ");
    for (int i = sizeof(uint) * 8 - 1; i >= 0; i--)
        {printf("%d", n >> i & 1);}
        printf("\n");
    res = change(n);
    printf("После: ");
    for (int i = sizeof(uint) * 8 - 1; i >= 0; i--)
        {printf("%d", res >> i & 1);}
        printf("\n");
    return 0;

}
