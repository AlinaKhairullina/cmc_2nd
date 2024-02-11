#include <stdio.h>

void qsort(int *mas, int size) {
    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];
    int tmp;
    do 
    {
        while(mas[i] < mid)
            i++;
        while(mas[j] > mid) 
            j--;
        if (i <= j) 
        {
            tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if(j > 0)
        //left
        qsort(mas, j + 1);
    if (i < size)
        //right
        qsort(&mas[i], size - i);
}
int main(int argc, char ** argv)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    qsort(a, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}