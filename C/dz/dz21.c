#include <stdio.h>
typedef unsigned char utype;
typedef char stype;
stype rev_bit(stype value)
{
    stype new = 0;
    for (int i = sizeof(stype) * 8 - 1; i >= 0; i--)
        new += (value >> i & 1) * (1 << (7 - i)); 
    value = new;
    return value;
}
int main()
{
    stype n, n1;
    scanf("%hhd", &n);
    printf("До:    ");
    for (int i = sizeof(stype) * 8 - 1; i >= 0; i--)
        {printf("%d", n >> i & 1);}
        printf("\n");
    n1 = rev_bit(n); 
    printf("После: ");
    for (int i = sizeof(stype) * 8 - 1; i >= 0; i--)
        {printf("%d", n1 >> i & 1);} 
        printf("\n");
    return 0;
}